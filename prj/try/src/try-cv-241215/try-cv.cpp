#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

    // すべてのカメラを列挙する
    for (int i = 0; ; i++) {
        VideoCapture cap(i);
        if (!cap.isOpened()) {
            break;
        }

        // デバイスの情報を取得 (例: 幅、高さ、フレームレート)
        double width = cap.get(CAP_PROP_FRAME_WIDTH);
        double height = cap.get(CAP_PROP_FRAME_HEIGHT);
        double fps = cap.get(CAP_PROP_FPS);

        std::cout << "Device " << i << ":" << std::endl;
        std::cout << "  Width: " << width << std::endl;
        std::cout << "  Height: " << height << std::endl;
        std::cout << "  FPS: " << fps << std::endl;


        cap.release();
    }



    // カメラを開く
    VideoCapture cap(0); // 0は通常最初のカメラを表す

    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return -1;
    }
 // カメラのプロパティを取得する
    double width = cap.get(CAP_PROP_FRAME_WIDTH);
    double height = cap.get(CAP_PROP_FRAME_HEIGHT);
    double fps = cap.get(CAP_PROP_FPS);


    while (true) {
        Mat frame;

        // カメラから1フレームを取得
        cap >> frame;

        // 取得したフレームを表示
        if (frame.rows > 0 && frame.cols > 0){
            imshow("Frame", frame);
        }

        // 'q'キーを押すと終了
        char c = (char)waitKey(25);
        if (c == 'q') {
            // 任意のフレームで保存 (ここではすべてのフレームを保存)
            Mat a = frame.clone();
            imwrite("a.png", a);
            break;
        }
    }

    // キャプチャをリリース
    cap.release();
    destroyAllWindows();

    return 0;
}