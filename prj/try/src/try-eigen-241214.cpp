#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

int main() {
  // 3x3の行列を定義
  Matrix3d m;
  m << 1, 2, 3,
       4, 5, 6,
       7, 8, 9;

  // ベクトルを定義
  Vector3d v(1, 2, 3);

  // 行列とベクトルの積
  Vector3d result = m * v;

  std::cout << result << std::endl;

  return 0;
}