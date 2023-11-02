#include <bits/stdc++.h>
using namespace std;

const double PI = 3.14;


class Point {
    private:
      double abscissa, ordinate; // Tung độ - Hoành độ
    public:
      Point(double x, double y);
      /* Trả về tung độ */
      double getX();

      /* Trả về hoành độ */
      double getY();

      /* Kiểm tra tam giác hợp lệ */
      bool isTriangle(Point a, Point b);

      /* Đối qua trục Ox */
      Point* setReflectionAcrossOx();
      friend Point* setReflectionAcrossOx(Point *p);

      /* Đối qua trục Oy */
      Point* setReflectionAcrossOy();
      friend Point* setReflectionAcrossOy(Point *p);

      /*
      Trả về khóa tương ứng với loại tam giác:
      Key | Value
      1   | Tam giác đều
      2   | Tam giác cân
      3   | Tam giác vuông
      4   | Tam giác vuông cân
      5   | Tam giác thường
      */
      int mapKeyForTriangle(Point m, Point n);

      /* Hiển thị loại tam giác */
      void isClassifyTriangle(Point m, Point n);
      
      /* Kiểm tra đỉnh thuộc phần tư thứ mấy */
      int isQuadrant();

      /* Tính độ dài của cạnh */
      double calculateSides(Point other);
      friend double calculateSides(Point p, Point other);

      /* Tính diện tích tam giác thông qua Heron*/
      double calculateAreaHeron(Point m, Point n);

      /* Tính diện tích tam giác thông qua tọa độ các đỉnh*/
      double calculateAreaPoint(Point m, Point n);

      /*Tính chu vi tam giác*/
      double setPerimeterPoint(Point m, Point n);

      /* Sắp xếp 3 cạnh tăng dần */
      void sort(Point m, Point n); 

      /* Sắp xếp tập điểm theo hoành độ tăng dần (sử dụng giải thuật quickSort)*/
      friend int partitionHoare(Point *listPoint, int l, int r);
      void sortGroupPoint(Point *listPoint, int l, int r); 

      /* Tính các giá trị khác */
      void setCalculateOther(Point m, Point n);
};

Point::Point(double x = 0, double y = 0){
  abscissa = x;
  ordinate = y;
}

double Point::getX(){
  return abscissa;
}

double Point::getY(){
  return ordinate;
}

bool Point::isTriangle(Point a, Point b){
  if(abscissa == a.abscissa && a.abscissa == b.abscissa) return false;
  if(ordinate == a.ordinate && a.ordinate == b.ordinate) return false;
  else return true;
}

Point* Point::setReflectionAcrossOx(){
  if(abscissa!=0) abscissa = -abscissa;
  return this;
}
/*
Point* setReflectionAcrossOx(Point *p){
  if(p->abscissa != 0) 
    p->abscissa = -p->abscissa;
  return p;
}
*/

Point* Point::setReflectionAcrossOy(){
  if(ordinate!=0) ordinate = -ordinate;
  return this;
}
/*
Point* setReflectionAcrossOy(Point *p){
  if(p->ordinate != 0) 
    p->ordinate = -p->ordinate;
  return p;
}
*/

int Point::mapKeyForTriangle(Point m, Point n) {
  double a = this->calculateSides(m);
  double b = this->calculateSides(n);
  double c = n.calculateSides(m);

  if(a == b && b == c && c == a)  
    return 1;
  if(a == b || a == c || b == c) {
    return 2;
  }
  if(a * a + b * b == c * c || a * a + c * c == b * b || c * c + b * b == a * a) {
    if(a == b || a == c || b == c) {
      return 4;
    }
    return 3;
  }
  return 5;
}

void Point::isClassifyTriangle(Point m, Point n) {
  int key = mapKeyForTriangle(m, n);
  switch (key)
  {
    case 1:
      cout << "Tam giac deu\n";
      break;
    case 2:
      cout << "Tam giac can\n";
      break;
    case 3:
      cout << "Tam giac vuong\n";
      break;
    case 4:
      cout << "Tam giac vuong can\n";
      break;
    default:
      cout << "Tam giac thuong\n";
      break;
  }
}

int Point::isQuadrant() {
  if(abscissa > 0 && ordinate > 0) 
    return 1; // Goc phan tu thu I
  if(abscissa < 0 && ordinate > 0) 
    return 2; // Goc phan tu thu II
  if(abscissa < 0 && ordinate < 0) 
    return 3; // Goc phan tu thu III
  if(abscissa > 0 && ordinate < 0) 
    return 4; // Goc phan tu thu IV
}

double Point::calculateAreaHeron(Point m, Point n) {
  double a = this->calculateSides(m);
  double b = this->calculateSides(n);
  double c = n.calculateSides(m);

  double p = (a + b + c) / 2; // Nửa chu vi
  return sqrt(p * (p - a) * (p - b) * (p - c));
}

double Point::calculateAreaPoint(Point m, Point n) {
  double x1 = this->abscissa, y1 = this->ordinate;
  double x2 = m.abscissa, y2 = m.ordinate;
  double x3 = n.abscissa, y3 = n.ordinate;

  return 0.5 * abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
}

double Point::calculateSides(Point other){
  return sqrt((pow(abs(other.abscissa - this->abscissa), 2)) + 
  (pow(abs(other.ordinate - this->ordinate), 2)));
}
/*
double calculateSides(Point p, Point other) {
  return sqrt((pow(abs(other.abscissa - p.abscissa), 2)) + 
    (pow(abs(other.ordinate - p.ordinate), 2)));
}
*/

void Point::sort(Point m, Point n){
  double a = this->calculateSides(m);
  double b = this->calculateSides(n);
  double c = n.calculateSides(m);

  double maxSide = max({a, b, c});
  double minSide = min({a, b, c});
  double middleSide = 0;
  if(a > minSide && a < maxSide)
    middleSide = a;
  else if(b > minSide && b < maxSide)
    middleSide = b;
  else 
    middleSide = c;

  cout << minSide << middleSide << maxSide;
}

int partitionHoare(Point *listPoint, int l, int r) {
    int i = l - 1, j = r + 1;
    double pivot = listPoint[r].abscissa; // Chọn phần tử cuối cùng làm chốt
    while (true)
    {
        do
            ++i;
        while (listPoint[i].abscissa < pivot);
        do
            --j;
        while (listPoint[j].abscissa > pivot);

        if (i < j)
            swap(listPoint[i], listPoint[j]);
        else
            return j;
    }
}

void Point::sortGroupPoint(Point *listPoint, int l, int r){
  if(l >= r)
    return;
  int m = partitionHoare(listPoint, l, r);
  sortGroupPoint(listPoint, l, m - 1);
  sortGroupPoint(listPoint, m, r);
}

void Point::setCalculateOther(Point m, Point n) {
  double a = this->calculateSides(m);
  double b = this->calculateSides(n);
  double c = n.calculateSides(m);

  double cosA = (pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c);
  double cosB = (pow(a, 2) + pow(c, 2) - pow(b, 2)) / (2 * a * c);
  double cosC = (pow(b, 2) + pow(a, 2) - pow(c, 2)) / (2 * a * b);

  /*Degree = Radian * (180 / PI)*/
  double angleA = acos(cosA) * (180 / PI);
  double angleB = acos(cosB) * (180 / PI);
  double angleC = acos(cosC) * (180 / PI);

  /* Ha = (2*S)/a */
  // C1: double S = calculateAreaHeron(m, n);
  // C2: 
  double S = calculateAreaPoint(m, n);
  double Ha = (2 * S) / a;
  double Hb = (2 * S) / b;
  double Hc = (2 * S) / c;

  cout << "Cac goc lan luot la: " << angleA << ","  << angleB << ","  << angleC << "(degree)\n"; 
  cout << "Cac duong cao lan luot la: " << Ha << ","  << Ha << ","  << Hc << "(m)\n"; 
}

class Triangle {
  private:
    int n; // Số lượng các điểm có trong không gian
    Point* ds; // Mảng chứa n điểm
  public:
    Triangle(int m);
    ~Triangle();
    /*
    Xét 3 điểm liền kề là 1 tam giác
    Nếu số điểm là số lẻ thì tam giác cuối cùng lấy chung điểm của tam giác trước
      VD: nếu số điểm là 5 thì 3 điểm đầu là 1 tam giác, điểm 3-4-5 là 1 tam giác
    */
    void findMaxPerimeterTri(); // Tìm chu vi lớn nhất và in tam giác đó ra      
    void findMaxAreaTri(); // Tìm chu vi tam giác lớn nhất và in ra
    void findIdenticalTri(); // Tìm 2 tam giác bằng nhau

};

int main(){
  Point a(1,1);
  Point b(-1,3);
  Point c(1,3);
  
  cout << a.calculateAreaPoint(b,c);


  return 0;
}