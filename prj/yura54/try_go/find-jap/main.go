package main
import (
	"fmt"
	"image"
	"io"
	"os"
	"log"

	"github.com/kbinani/screenshot"
)

// go言語のlog パッケージでログファイルと標準出力にログを出すには
func main() {
    log.Println("test")
	// ログファイルを追記モード（なければ作成）で開く
	f, err := os.OpenFile("app.log", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0644)
	if err != nil {
		log.Fatal("ログファイルを開けません:", err)
	}
	defer f.Close()

	// 標準出力とログファイルの両方へ書き込む Writer を作成
	multiWriter := io.MultiWriter(os.Stdout, f)
	log.SetOutput(multiWriter)

	// 任意：日時・ファイル名・行番号を付与したい場合
	log.SetFlags(log.Ldate | log.Ltime | log.Lshortfile)

	log.Println("アプリケーションを起動しました")
	log.Printf("ポート番号: %d", 8080)
}

// go言語で次の関数を実装して
/**
 * @brief Windows11で指定されたポイントを含むスクリーン全体のスクリーンショットをとる
 * @param x 指定ポイントのX座標
 * @param y 指定ポイントのY座標
 * @return スクリーンショットのイメージ
 */
func CaptureScreenAtPoint(x, y int) image.Image {
	n := screenshot.NumActiveDisplays()
	for i := 0; i < n; i++ {
		bounds := screenshot.GetDisplayBounds(i)
		if image.Pt(x, y).In(bounds) {
			img, err := screenshot.CaptureRect(bounds)
			if err != nil {
				panic(fmt.Sprintf("スクリーンショットの取得に失敗しました: %v", err))
			}
			return img
		}
	}

	// 指定座標がどのディスプレイにも含まれない場合はプライマリ画面（0番）を取得
	bounds := screenshot.GetDisplayBounds(0)
	img, err := screenshot.CaptureRect(bounds)
	if err != nil {
		panic(fmt.Sprintf("スクリーンショットの取得に失敗しました: %v", err))
	}
	return img
}

