package main

import (
	"log"
	"image"
	"image/color"
	"image/draw"
	"image/png"
	"math"
	"os"
	"github.com/kbinani/screenshot"
)

var (
    targetImg = "target.png"
    fromX = 0
    fromY = 0
    targetX = 0
    targetY = 0
)

// メインディスプレイ（座標 (0,0) を含む画面）の領域を取得する関数
func getMainDisplayBounds() image.Rectangle {
	n := screenshot.NumActiveDisplays()
	for i := 0; i < n; i++ {
		bounds := screenshot.GetDisplayBounds(i)
		// (0, 0) の点が含まれている画面がメインディスプレイ
		if (image.Point{X: 0, Y: 0}).In(bounds) {
			return bounds
		}
	}
	// 万が一見つからなければ 0 番目を返す
	return screenshot.GetDisplayBounds(0)
}

func main() {
    // ログの設定
    log.SetFlags(log.LstdFlags | log.Lshortfile)
        
    // 引数の処理
    argc := len(os.Args)
    for i := 0; i < argc; i++ {
        arg := os.Args[i]
        log.Println("debug", arg)
        if arg == "-t" && i < argc - 1 {
           log.Println("debug")
           targetImg = os.Args[i + 1]
           i++
        }
    }
    log.Println("targetImg ", targetImg)


	// 1. 探したいターゲット画像を読み込む
	targetFile, err := os.Open("target.png")
	if err != nil {
		log.Println("target.png の読み込みエラー:", err)
		return
	}
	defer targetFile.Close()

	targetImg, _, err := image.Decode(targetFile)
	if err != nil {
		log.Println("ターゲット画像のデコードエラー:", err)
		return
	}

	// 2. 画面のスクリーンショットを取得 (メインディスプレイ)
	bounds := getMainDisplayBounds() 
	screenImg, err := screenshot.CaptureRect(bounds)
	if err != nil {
		panic(err)
	}

	// 3. 画面内からターゲット画像を探索
	foundX, foundY, minDiff := findTemplate(screenImg, targetImg)

	// ピクセル差分が閾値以下であれば「発見」と判定
	// (値が小さいほど似ている。0は完全一致)
	threshold := 10.0 
	if minDiff <= threshold {
		log.Printf("画像を発見しました！\n位置 (X, Y): (%d, %d)\n平均色差: %.2f\n", foundX, foundY, minDiff)
    	targetW, targetH := targetImg.Bounds().Dx(), targetImg.Bounds().Dy()

        resultRect := image.Rect(foundX, foundY, foundX+targetW, foundY+targetH)
        red := color.RGBA{255, 0, 0, 255}
        drawRect(screenImg, resultRect, red)
	} else {
		log.Printf("対象の画像が見つかりませんでした。\n位置 (X, Y): (%d, %d)(最小色差: %.2f)\n", foundX, foundY, minDiff)
    	targetW, targetH := targetImg.Bounds().Dx(), targetImg.Bounds().Dy()

        resultRect := image.Rect(foundX, foundY, foundX+targetW, foundY+targetH)
        blue := color.RGBA{0, 0, 255, 255}
        drawRect(screenImg, resultRect, blue)
	}
    // スクリーンショットを保存
    outputFileName := "screenshot.png"
    screenshotFile, err := os.Create(outputFileName)
    if err != nil {
        log.Println("ファイルの作成に失敗:", err)
        return
    }
    defer screenshotFile.Close()

    err = png.Encode(screenshotFile, screenImg)
    if err != nil {
        log.Println("PNGへの保存に失敗：", err)
        return
    }
    log.Println("スクリーンショットを保存：", outputFileName)    }

// 画面画像(src) の中から ターゲット画像(target) に最も近い位置を探索する
func findTemplate(src, target image.Image) (bestX, bestY int, minDiff float64) {
	srcBounds := src.Bounds()
	targetBounds := target.Bounds()

	srcW, srcH := srcBounds.Dx(), srcBounds.Dy()
	targetW, targetH := targetBounds.Dx(), targetBounds.Dy()

	minDiff = math.MaxFloat64

	// 中央ピクセルチェック用の許容色差（例: RGBのユークリッド距離で 30.0）
	// この値より中央ピクセルの色が離れている場合は計算をスキップする
	const centerCheckThreshold = 30.0

	for x := 0; x <= srcW-targetW; x++ {
		for y := 0; y <= srcH-targetH; y++ {

			// 中央ピクセルチェックを含めた色差計算
			diff := calcImageDiff(src, target, x, y, centerCheckThreshold)
			if diff < minDiff {
				minDiff = diff
				bestX = x
				bestY = y
			}

			// 完全一致した場合は即終了
			if minDiff == 0 {
				return bestX, bestY, minDiff
			}
		}
	}

	return bestX, bestY, minDiff
}

// 特定の座標(offsetX, offsetY)における1ピクセルあたりの平均RGB色差を計算
func calcImageDiff(src, target image.Image, offsetX, offsetY int, threshold float64) float64 {
	targetBounds := target.Bounds()
	targetW, targetH := targetBounds.Dx(), targetBounds.Dy()

	// -------------------------------------------------------------
	// 【追加】1. 中央ピクセルの色差チェック（アーリーリターン）
	// -------------------------------------------------------------
	centerX := targetW / 2
	centerY := targetH / 2
//
//	r1, g1, b1, _ := src.At(offsetX+centerX, offsetY+centerY).RGBA()
//	r2, g2, b2, _ := target.At(centerX, centerY).RGBA()
//
//	rd := float64(r1>>8) - float64(r2>>8)
//	gd := float64(g1>>8) - float64(g2>>8)
//	bd := float64(b1>>8) - float64(b2>>8)
//
//	centerDiff := math.Sqrt(rd*rd + gd*gd + bd*bd)
    centerDiff := calcDiffRGB(src, offsetX+centerX, offsetY+centerY,
                              target, centerX,centerY) 
	// 中央ピクセルの差が許容量（threshold）を超えていれば即座にスキップ
	if centerDiff > threshold {
		return math.MaxFloat64
	}

	// -------------------------------------------------------------
	// 2. 全ピクセルの色差計算（中央チェックを通過した場合のみ実行）
	// -------------------------------------------------------------
	var totalDiff float64
	pixelCount := 0
	step := 1

	for tx := 0; tx < targetW; tx += step {
		for ty := 0; ty < targetH; ty += step {

			r1, g1, b1, _ := src.At(offsetX+tx, offsetY+ty).RGBA()
			r2, g2, b2, _ := target.At(tx, ty).RGBA()

			rd := float64(r1>>8) - float64(r2>>8)
			gd := float64(g1>>8) - float64(g2>>8)
			bd := float64(b1>>8) - float64(b2>>8)

			pixelDiff := math.Sqrt(rd*rd + gd*gd + bd*bd)
			totalDiff += pixelDiff
			pixelCount++
		}
	}

	return totalDiff / float64(pixelCount)
}
func calcDiffRGB(src image.Image, srcX, srcY int,
                 target image.Image, targetX, targetY int) float64 {
	r1, g1, b1, _ := src.At(srcX, srcY).RGBA()
	r2, g2, b2, _ := target.At(targetX, targetY).RGBA()

	rd := float64(r1>>8) - float64(r2>>8)
	gd := float64(g1>>8) - float64(g2>>8)
	bd := float64(b1>>8) - float64(b2>>8)

	return math.Sqrt(rd*rd + gd*gd + bd*bd)
}
// src 画像上に、指定された矩形 (r) を指定された色 (c) の枠線で描画する関数
func drawRect(src draw.Image, r image.Rectangle, c color.Color) {
	// 上辺
	for x := r.Min.X; x < r.Max.X; x++ {
		src.Set(x, r.Min.Y, c)
		src.Set(x, r.Min.Y+1, c) // 線を太く
	}
	// 下辺
	for x := r.Min.X; x < r.Max.X; x++ {
		src.Set(x, r.Max.Y-1, c)
		src.Set(x, r.Max.Y-2, c)
	}
	// 左辺
	for y := r.Min.Y; y < r.Max.Y; y++ {
		src.Set(r.Min.X, y, c)
		src.Set(r.Min.X+1, y, c)
	}
	// 右辺
	for y := r.Min.Y; y < r.Max.Y; y++ {
		src.Set(r.Max.X-1, y, c)
		src.Set(r.Max.X-2, y, c)
	}
}
//	// 2. 探索結果の矩形を定義
//	targetW := targetImg.Bounds().Dx()
//	targetH := targetImg.Bounds().Dy()
//	resultRect := image.Rect(bestX, bestY, bestX+targetW, bestY+targetH)
//	// 3. 四角形を描画 (赤色、不透明)
//	red := color.RGBA{255, 0, 0, 255}
//	drawRect(outputImg, resultRect, red)
//
