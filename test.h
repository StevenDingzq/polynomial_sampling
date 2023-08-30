#include <algorithm>
#include <iostream>
#include <iterator>
#include <math.h>
#include <vector>
namespace test
{

  using namespace std;
  using Vec = vector<double>;
  using Mat = vector<vector<double>>;
  class MatUnity
  {
    public:
      Mat CreateMat(double t0, double t1);
      Vec CreateVec(double a0, double a1, double a2, double a3, double a4,
                    double a5);
      void PrintM(Mat &t);
      void PrintM(Vec &t);

      Mat AugM(Mat &a, Vec &b);
      bool Solve(Mat &a, Vec &b, Vec &x);
      bool isZero(double t);
      double CalcPosition(double t, Vec &x);
      Vec QuinticVector(double t0);
  };
}