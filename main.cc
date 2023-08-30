#include "test.h"
#include <chrono>
#include <iomanip>
using namespace test;
int main()
{
  MatUnity helper;
  Mat a;
  a = helper.CreateMat(0, 3);   // 根据采样时间3创建a矩阵
  Vec b;
  // 设置起点和终点的状态（横向偏移，横向速度，横向加速度）
  b = helper.CreateVec(50, 0, 0, -50, 0, 0);
  Vec x(6);
  auto start = std::chrono::steady_clock::now();
  bool valid = helper.Solve(a, b, x);
  auto end = std::chrono::steady_clock::now();
  auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  double dt = dur.count();
  cout << std::setprecision(3) << std::scientific << "求解时长：" << dt
       << "微秒" << endl;
  if (!valid) {
    cout << "FAIL!\n";
    return 0;
  }
  double sample = 2;
  cout << "时间为：[" << sample << "] 横向位置: ["
       << helper.CalcPosition(sample, x) << "]" << endl;

  return 0;
}