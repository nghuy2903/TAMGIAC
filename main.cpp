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
      Point* setReflectionAcrossOx(); // Đối qua trục Ox
      Point* setReflectionAcrossOy(); // Đối qua trục Ox
      void isClassifyTriangle();// Kiểm tra tam giác gì
      int isQuadrant(); // Kiểm tra đỉnh thuộc phần tư thứ mấy
      double setCalculateSides(); // Tính giá trị của cạnh
      void quickSort(); // Sắp xếp cạnh tăng dần
      void setCalculateOther(); // Tính các giá trị khác
};

Point::Point(double x = 0, double y = 0){
  Abscissa = x;
  Ordinate = y;
}

double Point::getX(){
  return Abscissa;
}

double Point::getY(){
  return Ordinate;
}

bool Point::isTriangle(Point a, Point b){
  if(Abscissa == a.Abscissa && a.Abscissa == b.Abscissa) return false;
  if(Ordinate == a.Ordinate && a.Ordinate == b.Ordinate) return false;
  else return true;
}

Point* Point::setReflectionAcrossOx(){
  if(Abscissa!=0) Abscissa = -Abscissa;
  return this;
}

Point* Point::setReflectionAcrossOy(){
  if(Ordinate!=0) Ordinate = -Ordinate;
  return this;
}

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