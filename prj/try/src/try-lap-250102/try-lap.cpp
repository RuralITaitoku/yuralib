#include <opencv2/opencv.hpp>

using namespace cv;

#define DP(x) std::cout << __FILE__ << ":" << __LINE__ <<":" << x  << std::endl;
#define DPM(x) std::cout << __FILE__ << ":" << __LINE__ << std::endl << x  << std::endl;




void pathfinding(int number, int base, int depth, cv::Mat& rowsol) {
    if (base <= 0) {
        return;
    }
    int next_number = number / base;
    DP("depth=" << depth << ", " << (number % base));
    rowsol.at<int>(depth - 1, 0) = (number % base);
    pathfinding(next_number, base - 1, depth - 1, rowsol);
}

int factorial(int n) {
    int result = 1;
    for (;n > 0; n--) {
        result *= n;
    }
    return result;
}

void debug(cv::Mat &m) {

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            std::cout << std::setw(4) << m.at<int>(i, j) << std::endl;
        }
    }
}
void debug(cv::Mat& m, cv::Mat& rowsol) {

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if (j == rowsol.at<int>(i, 0)) {
                std::cout << "\033[41m\033[37m" << std::setw(4) << m.at<float64_t>(i, j) << "\033[0m";
            } else {
                std::cout << std::setw(4) << m.at<float64_t>(i, j);
            }
        }
        std::cout << std::endl;
    }
}

int main() {

    DP("test");

    std::vector<float64_t> data = 
            {
                1, 2, 3, 1,
                4, 5, 6, 1,
                7, 9, 1, 1,
                1, 1, 1, 1
            };
    cv::Mat cost = cv::Mat(4, 4, CV_64FC1, data.data());
    cv::Mat rowsol = cv::Mat(4, 1, CV_32SC1);
    cv::Mat colsol = cv::Mat(1, 4, CV_32SC1);
    int f = factorial(rowsol.rows);
    DP("f=" << f);
    colsol = -1;
    DPM(colsol);
    float64_t min = std::numeric_limits<float64_t>::max();
    cv::Mat min_rowsol;
    for (;f > 0; f--) {
        DP("f=" << f);
        int base = cost.cols;
        int depth = base;
        pathfinding(f, base, depth, rowsol);
        colsol = -1;
        for (int i = rowsol.rows - 1; i >= 0; i--) {
            int no = rowsol.at<int>(i, 0);
            int count = no;
            for (int j = 0; j < colsol.cols; j++) {
                int v = colsol.at<int>(0, j);
                if (v < 0) {
                    if (count == 0) {
                        colsol.at<int>(0, j) = i;
                        rowsol.at<int>(i, 0) = j; 
                        break;
                    }
                    count --;
                }
            }
        }
        float64_t sum = 0.0;
        for (int i = 0; i < rowsol.rows; i++) {
            int j = rowsol.at<int>(i, 0);
            sum += cost.at<double>(i, j);
        }
        if (sum < min) {
            min = sum;
            min_rowsol = rowsol.clone();
        }
        DP("sum = " << sum);
        DPM(colsol);
        DPM(rowsol);
    }
    DP("min = " << min);
    DPM(min_rowsol);
    debug(cost, min_rowsol);
    return 0;
}