#include <bits/stdc++.h>
using namespace std;

const double PI = 3.14;

class Point {
    private:
      double abscissa, ordinate; // Hoành độ - Tung độ
    public:
      Point(double x, double y);
      /* Trả về tung độ */
      double getX();

      /* Trả về hoành độ */
      double getY();

      /* Kiểm tra tam giác hợp lệ */
      bool isTriangle(Point a, Point b);

      /* Đối qua trục Ox */
      Point setReflectionAcrossOx() const;
      // friend Point* setReflectionAcrossOx(Point *p);

      /* Đối qua trục Oy */
      Point setReflectionAcrossOy() const;
      // friend Point* setReflectionAcrossOy(Point *p);

      /*
      Trả về khóa tương ứng với loại tam giác:
      Key | Value
      1   | Tam giác đều
      2   | Tam giác cân
      3   | Tam giác vuông
      4   | Tam giác thường
      */
      int mapKeyForTriangle(Point m, Point n);

      /* Hiển thị loại tam giác */
      void isClassifyTriangle(Point m, Point n);
      
      /* Kiểm tra đỉnh thuộc phần tư thứ mấy */
      int isQuadrant();
      void printQuadrant();

      /* Tính độ dài của cạnh */
      double calculateSides(Point other);
      friend double calculateSides(Point p, Point other);

      /* Tính diện tích tam giác thông qua Heron*/
      double calculateAreaHeron(Point m, Point n);

      /* Tính diện tích tam giác thông qua tọa độ các đỉnh*/
      double calculateAreaPoint(Point m, Point n);

      /*Tính chu vi tam giác*/
      double calculatePerimeterPoint(Point m, Point n);

      /* Sắp xếp 3 cạnh tăng dần */
      void sort(Point m, Point n); 

      /* Tính các giá trị khác */
      void setCalculateOther(Point m, Point n);

      /* */
      void output(Point b, Point c);

      friend class Triangle;
};


class Triangle {
  private:
    int n; // Số lượng các điểm có trong không gian
    Point* arr; // Mảng chứa n điểm
  public:
    Triangle(int m);
    ~Triangle();

    /* Lấy số lượng các điểm có trong không gian */
    int getNumberPoint();

    /* Lấy mảng chứa n điểm */
    Point* getGroupPoint();

    /*
    Xét 3 điểm liền kề là 1 tam giác
    Nếu số điểm là số lẻ thì tam giác cuối cùng lấy chung điểm của tam giác trước
    VD: nếu số điểm là 5 thì 3 điểm đầu là 1 tam giác, điểm 3-4-5 là 1 tam giác
    */  

    void findMaxAreaTri(); // Tìm diện tích tam giác lớn nhất và in ra

    /* Sắp xếp tập điểm theo hoành độ tăng dần (sử dụng giải thuật quickSort)*/
    friend int partitionLomuto(Point *listPoint, int l, int r);
    void sortGroupPoint(Point *listPoint, int l, int r); 

    /* Nhập tập n điểm */
    void input();

    /* Hàm xuất */
    void output();
};


Point::Point(double x = 0, double y = 0) {
  abscissa = x;
  ordinate = y;
}

double Point::getX() {
  return abscissa;
}

double Point::getY() {
  return ordinate;
}

bool Point::isTriangle(Point a, Point b){
    // Kiểm tra xem ba điểm không cùng nằm trên một đường thẳng (không có điểm nào trùng nhau)
    if (a.abscissa == b.abscissa && b.abscissa == this->abscissa) 
      return false;
    if (a.ordinate == b.ordinate && b.ordinate == this->ordinate) 
      return false;

    double sideAB = a.calculateSides(b);
    double sideAC = a.calculateSides(*this);
    double sideBC = b.calculateSides(*this);

    // Kiểm tra ba cạnh có thoả mãn bất đẳng thức tam giác
    if (sideAB + sideAC > sideBC &&
        sideAC + sideBC > sideAB && 
        sideAB + sideBC > sideAC) {
        return true;  // Có thể tạo thành một tam giác
    } else {
        return false; // Không thể tạo thành một tam giác
    }
}

Point Point::setReflectionAcrossOx() const {
  Point res = *this;
  if(res.ordinate != 0) 
    res.ordinate = -res.ordinate;
  return res;
}

/*
Point* setReflectionAcrossOx(Point *p){
  if(p->abscissa != 0) 
    p->abscissa = -p->abscissa;
  return p;
}
*/

Point Point::setReflectionAcrossOy() const {
  Point res = *this;
  if(res.abscissa != 0) 
    res.abscissa = -res.abscissa;
  return res;
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

  if(a == b && b == c && a == c)  
    return 1;
  if(a == b || a == c || b == c) {
    return 2;
  }
  if(a * a + b * b == c * c || a * a + c * c == b * b || c * c + b * b == a * a) {
    return 3;
  }
  return 4;
}

void Point::isClassifyTriangle(Point m, Point n) {
  int key = mapKeyForTriangle(m, n);
  cout << key;
  switch (key)
  {
    case 1:
      cout << "Tam giac deu";
      break;
    case 2:
      cout << "Tam giac can";
      break;
    case 3:
      cout << "Tam giac vuong";
      break;
    default:
      cout << "Tam giac thuong";
      break;
  }
}

int Point::isQuadrant() {
  if (abscissa == 0 && ordinate == 0) {
    return 0; 
  } else if (abscissa > 0) {
    return (ordinate > 0) ? 1 : 4; 
  } else {
    return (ordinate > 0) ? 2 : 3;
  }
}

void Point::printQuadrant() {
  string res;
  if(this->isQuadrant() == 1) 
    res = "thuoc goc phan tu thu I\n";
  else if(this->isQuadrant() == 2) 
    res = "thuoc goc phan tu thu II\n";
  else if(this->isQuadrant() == 3) 
    res = "thuoc goc phan tu thu III\n";
  else if(this->isQuadrant() == 4) 
    res = "thuoc goc phan tu thu IV\n";
  else 
    res = "thuoc goc toa do\n";

  cout << "Dinh (" << this->getX() << "," << this->getY() << ") " << res;
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

double Point::calculatePerimeterPoint(Point m, Point n){
  double x = this->calculateSides(m);
  double y = this->calculateSides(n);
  double z = m.calculateSides(n);
  return x+y+z;
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

  cout << minSide << ", " << middleSide << ", " << maxSide;
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

  cout << "\nCac goc lan luot la: " << angleA << ", "  << angleB << ", "  << angleC << "(do)"; 
  cout << "\nCac duong cao lan luot la: " << Ha << ", "  << Ha << ", "  << Hc; 
}

void Point::output(Point b, Point c) {
  
  cout << "Ba diem da cho (" 
  << this->getX() << "," << this->getY() << ")"
  << " (" << b.getX() << "," << b.getY() << ")"
  << " (" << c.getX() << "," << c.getY() << ") ";

  if(this->isTriangle(b, c)) {

    cout << "tao thanh ";
    this->isClassifyTriangle(b,c);

    cout << "\nDien tich: " << this->calculateAreaPoint(b,c);

    cout << "\nChu vi: " << this->calculatePerimeterPoint(b,c);

    cout << "\nDo dai lan luot 3 canh: "
    << this->calculateSides(b) << ", " 
    << this->calculateSides(c) << ", " 
    << b.calculateSides(c);

    cout << "\nSap xep tang dan 3 canh: ";
    this->sort(b, c);

    this->setCalculateOther(b, c);
  }else {
    cout << "khong tao thanh tam giac";
  }

  Point ax = this->setReflectionAcrossOx();
  Point bx = b.setReflectionAcrossOx();
  Point cx = c.setReflectionAcrossOx();
  Point ay = this->setReflectionAcrossOy();
  Point by = b.setReflectionAcrossOy();
  Point cy = c.setReflectionAcrossOy();

  cout << "\nDoi xung qua Ox:" 
  << " (" << ax.getX() << "," << ax.getY() << ")"
  << " (" << bx.getX() << "," << bx.getY() << ")"
  << " (" << cx.getX() << "," << cx.getY() << ")";

  cout << "\nDoi xung qua Oy:" 
  << " (" << ay.getX() << "," << ay.getY() << ")"
  << " (" << by.getX() << "," << by.getY() << ")"
  << " (" << cy.getX() << "," << cy.getY() << ")\n";

  this->printQuadrant();
  b.printQuadrant();
  c.printQuadrant();
}

Triangle::Triangle(int m = 0) {
  n = m;
  arr = new Point[n];
}

Triangle::~Triangle() {
  n = 0;
  delete [] arr;
}

int Triangle::getNumberPoint() {
  return n;
}

Point* Triangle::getGroupPoint() {
  return this->arr;
}

void Triangle::input() {
  cin >> n;
  arr = new Point[n];
  for(int i = 0; i < n; i++) {
    double x, y; 
    cin >> x >> y;
    arr[i].abscissa = x;
    arr[i].ordinate = y;
  }
}

void Triangle::output() {
  for(int i = 0; i < n; i++) {
    cout << "(" << arr[i].getX() << "," << arr[i].getY() << ")\n";
  }
}

void Triangle::findMaxAreaTri() {
    double maxPetre = 0;
    Point maxTri[3]; // Lưu tam giác có diện tích lớn nhất
    for (int i = 0; i < n - 2; i++) {
      int j = i + 1, k = j + 1;
      double area = arr[i].calculatePerimeterPoint(arr[j], arr[k]);

      if(area > maxPetre) {
        maxPetre = area;
        maxTri[0] = arr[i];
        maxTri[1] = arr[j];
        maxTri[2] = arr[k];
      }
    }
    if (maxPetre) 
      cout << "Tam giac co dien tich lon nhat la: (" 
      << maxTri[0].getX() << "," << maxTri[0].getY() << ") (" 
      << maxTri[1].getX() << "," << maxTri[1].getY() << ") (" 
      << maxTri[2].getX() << "," << maxTri[2].getY() << ")" << endl;
    else 
      cout << "Khong ton tai tam giac nao!" << endl;
}

int partitionLomuto(Point *listPoint, int l, int r) {
    double pivot = listPoint[r].getX(); // Chọn phần tử cuối cùng làm chốt
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (listPoint[j].getX() <= pivot) {
            ++i;
            swap(listPoint[i], listPoint[j]);
        }
    }
    ++i;
    swap(listPoint[i], listPoint[r]); // Đưa pivot về giữa
    return i;
}

void Triangle::sortGroupPoint(Point *listPoint, int l, int r) {
    if (l >= r)
        return;
    int m = partitionLomuto(listPoint, l, r);
    sortGroupPoint(listPoint, l, m - 1);
    sortGroupPoint(listPoint, m + 1, r);
}

int main() {
  /* /////////////////////// THAO TÁC NHẬP DỮ LIỆU /////////////////////// */
  double x1, y1;
  double x2, y2;
  double x3, y3;

  cin >> x1 >> y1;
  cin >> x2 >> y2;
  cin >> x3 >> y3;

  Point a(x1, y1), b(x2, y2), c(x3, y3);

  Triangle triangle;
  triangle.input();

  /* /////////////////////// THAO TÁC XUẤT DỮ LIỆU /////////////////////// */

  a.output(b, c);

  cout << "\nTap diem ban dau la: \n";
  triangle.output();

  triangle.findMaxAreaTri();
  triangle.sortGroupPoint(triangle.getGroupPoint(), 0, triangle.getNumberPoint() - 1);
  cout << "Sap xep tap diem theo hoanh do tang dan la: \n";

  triangle.output();

  return 0;
}