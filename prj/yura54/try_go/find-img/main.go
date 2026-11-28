package main

import (
	"flag"
	"fmt"
	"image"
	"image/png"
	"math"
	"os"

	"github.com/kbinani/screenshot"
)

type MatchResult struct {
	Found bool
	X     int
	Y     int
	Score float64 // 0.0 に近いほど一致度が高い（平均ピクセル差 0.0〜1.0）
}

func main() {
	displayIdx := flag.Int("d", 0, "target display index (0-based)")
	flag.Usage = func() {
		fmt.Fprintf(os.Stderr, "Usage: %s [-d display number] target_image_path\n", os.Args[0])
		flag.PrintDefaults()
	}
	flag.Parse()

	if flag.NArg() != 1 {
		flag.Usage()
		os.Exit(1)
	}
	targetPath := flag.Arg(0)

	numDisplays := screenshot.NumActiveDisplays()
	if numDisplays == 0 {
		fmt.Fprintln(os.Stderr, "Error: no active displays found")
		os.Exit(1)
	}
	if *displayIdx < 0 || *displayIdx >= numDisplays {
		fmt.Fprintf(os.Stderr, "Error: display -d %d is out of range (active displays: 0..%d)\n", *displayIdx, numDisplays-1)
		os.Exit(1)
	}

	targetImg, err := loadImage(targetPath)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error loading target image: %v\n", err)
		os.Exit(1)
	}

	bounds := screenshot.GetDisplayBounds(*displayIdx)
	screenImg, err := screenshot.CaptureRect(bounds)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error capturing display %d: %v\n", *displayIdx, err)
		os.Exit(1)
	}

	// 許容誤差（0.02 = 約2%以内の色差を許容。完全一致のみにしたい場合は 0.0 にする）
	const maxAllowedDiff = 0.02

	result := findSubImage(screenImg, targetImg, maxAllowedDiff)
	if result.Found {
		// ディスプレイ全体の座標系に変換して表示
		absX := bounds.Min.X + result.X
		absY := bounds.Min.Y + result.Y
		fmt.Printf("Found target image on display %d at (%d, %d) [diff: %.4f]\n", *displayIdx, absX, absY, result.Score)
	} else {
		fmt.Printf("Target image not found on display %d\n", *displayIdx)
	}
}

func loadImage(path string) (image.Image, error) {
	f, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer f.Close()

	img, _, err := image.Decode(f)
	if err != nil {
		return nil, err
	}
	return img, nil
}

// findSubImage は screen 内に target と一致する領域があるか探索する
func findSubImage(screen image.Image, target image.Image, threshold float64) MatchResult {
	sBounds := screen.Bounds()
	tBounds := target.Bounds()

	sW, sH := sBounds.Dx(), sBounds.Dy()
	tW, tH := tBounds.Dx(), tBounds.Dy()

	if tW <= 0 || tH <= 0 || tW > sW || tH > sH {
		return MatchResult{Found: false}
	}

	best := MatchResult{
		Found: false,
		Score: math.MaxFloat64,
	}

	// 探索範囲（左上が (x, y) のとき、右下は (x+tW, y+tH)）
	for y := 0; y <= sH-tH; y++ {
		for x := 0; x <= sW-tW; x++ {
			diff := calcRegionDiff(screen, sBounds.Min.X+x, sBounds.Min.Y+y, target, tBounds.Min.X, tBounds.Min.Y, tW, tH, best.Score)
			if diff < best.Score {
				best.Score = diff
				best.X = x
				best.Y = y
			}
			// 完全一致が見つかったら即終了
			if best.Score == 0 {
				best.Found = true
				return best
			}
		}
	}

	if best.Score <= threshold {
		best.Found = true
	}
	return best
}

// calcRegionDiff は指定位置の RGB 平均絶対差（0.0〜1.0）を計算する
// 途中で bestScore を超えた場合は早期打ち切りして高速化する
func calcRegionDiff(
	screen image.Image, sx, sy int,
	target image.Image, tx, ty int,
	w, h int,
	cutoff float64,
) float64 {
	var totalDiff float64
	totalSamples := float64(w * h * 3)
	limitSum := cutoff * totalSamples

	for dy := 0; dy < h; dy++ {
		for dx := 0; dx < w; dx++ {
			sr, sg, sb, _ := screen.At(sx+dx, sy+dy).RGBA()
			tr, tg, tb, _ := target.At(tx+dx, ty+dy).RGBA()

			totalDiff += math.Abs(float64(sr)-float64(tr)) / 65535.0
			totalDiff += math.Abs(float64(sg)-float64(tg)) / 65535.0
			totalDiff += math.Abs(float64(sb)-float64(tb)) / 65535.0

			if totalDiff > limitSum {
				return math.MaxFloat64
			}
		}
	}

	return totalDiff / totalSamples
}

// デバッグ用にスクリーンショットを保存したい場合に使えるヘルパー
func savePNG(path string, img image.Image) error {
	f, err := os.Create(path)
	if err != nil {
		return err
	}
	defer f.Close()
	return png.Encode(f, img)
}
