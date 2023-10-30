#include <bits/stdc++.h>

using namespace std;

class Point{
    private:
      double Abscissa , Ordinate; // Tung do - Hoanh do
    public:
      Point(double x, double y);
      double getX();
      double getY();
      bool isTriangle(Point a, Point b); // Kiểm tra tam giac
      void setReflectionAcrossOx(); // Đối qua trục Ox
      void isClassifyTriangle();// Kiểm tra tam giác gì
      int isQuadrant(); // Kiểm tra đỉnh thuộc phần tư thứ mấy
      double setCalculateSides(); // Tính giá trị của cạnh
      void quickSort(); // Sắp xếp cạnh tăng dần
      void setCalculateOther(); // Tính các giá trị khác
};

class Triangle{
  private:
    int n; // Số lượng các điểm có trong không gian
    Point* ds; // Mảng chứa n điểm
  public:
    Triangle(int m);
    ~Triangle();
    void findMaxPerimeterTri(); // Tìm chu vi lớn nhất và in tam giác đó ra      double maxPerimeterTri(Point a, Point b, Point c); // Tính chu vi của tam giác

};

int main(){

  return 0;
}