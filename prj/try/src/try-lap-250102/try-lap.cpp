#include <opencv2/opencv.hpp>
#include "task.hpp"
#include "lap.h"
#include "rng.hpp"


#define DP(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl;

using namespace cv;

void pathfinding_body(int number, int base, int depth, cv::Mat& rowsol) {
    if (base <= 0) {
        return;
    }
    int next_number = number / base;
    // DP("depth=" << depth << ", " << (number % base));
    rowsol.at<int>(depth - 1, 0) = (number % base);
    pathfinding_body(next_number, base - 1, depth - 1, rowsol);
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
                std::cout << "\033[41m\033[37m" << std::setw(4) << m.at<double>(i, j) << "\033[0m";
            } else {
                std::cout << std::setw(4) << m.at<double>(i, j);
            }
        }
        std::cout << std::endl;
    }
}

void debug(std::vector<std::vector<double>>& m, std::vector<int>& rowsol) {

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++) {
            if (j == rowsol[i]) {
                std::cout << "\033[41m\033[37m" << std::setw(4) << m[i][j] << "\033[0m";
            } else {
                std::cout << std::setw(4) << m[i][j];
            }
        }
        std::cout << std::endl;
    }
}


int get_test(std::vector<std::vector<double>>& costMatrix) {
    costMatrix =  {
         {3,3,3,7},
         {8,4,3,4},
         {1,4,1,2},    
         {2,5,4,2}    
    };
    return 0;
}

int get_rand_test(int dim, int seed, std::vector<std::vector<double>>& ret) {

    LinearCongruentialGenerator rng(seed);

    std::vector<std::vector<double>> result(dim, std::vector<double>(dim));
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            result[i][j] = rng.next(0, 99);
        }
    }


    ret = result;
    return 0;
}


int test_lap_org() {


    std::vector<std::vector<double>> costMatrix;
    get_test(costMatrix);
    // get_rand_test(dim, 0, costMatrix);

    int dim = costMatrix.size();        // Set the dimension of matrix to 10, dim is the problem size

    std::vector<int> rowsol(dim);         // An array to store column indexes assigned to row in solution  
    std::vector<int> colsol(dim);         // An array to store column indexes assigned to row in solution  

    std::vector<double> u(dim);             // u          - dual variables, row reduction numbers
    std::vector<double> v(dim);             // v          - dual variables, column reduction numbers
DP("");
    double totalCost = lap(costMatrix, rowsol, colsol, u, v);

    DP("最小コスト" << totalCost);
    debug(costMatrix, rowsol);

    return 0;
}



int main() {

    DP("test");

    test_lap_org();

    return 0;
}

