#include "test.h"
namespace test
{
  Mat MatUnity::CreateMat(double t0, double t1)
  {
    Mat T;
    Vec tt0 = QuinticVector(t0);
    Vec tt1 = QuinticVector(t1);
    T = {
        {tt0[0], tt0[1], tt0[2], tt0[3], tt0[4], tt0[5]},
        {0, tt0[0], 2 * tt0[1], 3 * tt0[2], 4 * tt0[3], 5 * tt0[4]},
        {0, 0, 2 * tt0[0], 6 * tt0[1], 12 * tt0[2], 20 * tt0[3]},
        {tt1[0], tt1[1], tt1[2], tt1[3], tt1[4], tt1[5]},
        {0, tt1[0], 2 * tt1[1], 3 * tt1[2], 4 * tt1[3], 5 * tt1[4]},
        {0, 0, 2 * tt1[0], 6 * tt1[1], 12 * tt1[2], 20 * tt1[3]},
    };
    cout << "a 矩阵： \n";
    PrintM(T);
    return T;
  }

  Vec MatUnity::CreateVec(double a0, double a1, double a2, double a3, double a4,
                          double a5)
  {
    Vec x{a0, a1, a2, a3, a4, a5};

    return x;
  }
  void MatUnity::PrintM(Mat &t)
  {
    for (int i = 0; i < t.size(); ++i) {
      for (int j = 0; j < t[0].size(); ++j) {
        cout << t[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
    return;
  }
  void MatUnity::PrintM(Vec &t)
  {
    copy(t.begin(), t.end(), ostream_iterator<double>(cout, " "));

    cout << endl;
  }
  bool MatUnity::isZero(double x)
  {
    return fabs(x) < 1e-10;
  }

  Mat MatUnity::AugM(Mat &a, Vec &b)
  {
    Mat T;
    T = a;
    for (int i = 0; i < a.size(); ++i) {
      T[i].emplace_back(b[i]);
    }
    return T;
  }
  // 求解线性方程组（ax = b)
  bool MatUnity::Solve(Mat &a, Vec &b, Vec &x)
  {
    if (a.size() != b.size()) {
      cout << "a or b 维度不一样\n";
      return false;
    }
    if (a.size() == 0 || a.size() != a[0].size()) {
      cout << "a 不是方阵，解不唯一.\n";
      return false;
    }
    // 0 增广矩阵
    Mat T = AugM(a, b);
    cout << "增广矩阵：\n";
    PrintM(T);
    int r = T.size();
    int c = T[0].size();   // c = 1+ r
    // 1 消元
    for (int i = 0; i < c - 1; ++i) {   // column
      // 找到第一个不为0的元素
      int k = 0;
      for (k = i; k < r; ++k) {
        if (!isZero(T[k][i])) {
          break;
        }
      }
      if (k < r) {   // 说明第i列有不为0的元素，在第k行
        // 交换第i行和第k行
        swap(T[i], T[k]);
        if (i != k) {
          PrintM(T);
        }
        // 把除了第i列 第i行的其他第i列元素消除为0
        if (isZero(T[i][i])) {
          cout << "cal error\n";
          return false;
        }
        double bei;
        for (int j = i + 1; j < r; ++j) {
          bei = T[j][i] / T[i][i];
          for (int z = i; z < c; ++z) {
            T[j][z] -= bei * T[i][z];
          }
        }
      } else {
        cout << "出现a的主元是0!\n";
        return false;
      }
    }
    cout << "上三角： \n";
    PrintM(T);
    for (int i = r - 1; i >= 0; --i) {
      double p = T[i][c - 1];
      for (int j = i + 1; j < c - 1; ++j) {
        p -= x[j] * T[i][j];
      }
      if (isZero(T[i][i])) {
        cout << "出现a的主元是0!!\n";
        return false;
      }
      x[i] = p / T[i][i];
    }
    cout << "解x :\n";
    PrintM(x);
    return true;
  }
  Vec MatUnity::QuinticVector(double t0)
  {
    Vec tt0 = {1,
               t0,
               t0 * t0,
               t0 * t0 * t0,
               t0 * t0 * t0 * t0,
               t0 * t0 * t0 * t0 * t0};
    return tt0;
  }
  double MatUnity::CalcPosition(double t, Vec &x)
  {
    Vec tt0 = QuinticVector(t);
    if (x.size() != tt0.size()) {
      cout << "error";
      return 0.0;
    }
    double res = 0.0;
    for (int i = 0; i < x.size(); ++i) {
      res += tt0[i] * x[i];
    }
    return res;
  }
}