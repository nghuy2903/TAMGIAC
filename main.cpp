#include <bits/stdc++.h>

using namespace std;

class DIEM{
    private:
        double hoanhDo, tungDo;
      public:
      DIEM(double x, double y);
        double getX();
        double getY();
};

class TAMGIAC{
    private:
      int n; // Số lượng các điểm có trong không gian
      DIEM* ds; // Mảng chứa n điểm
    public:
      TAMGIAC(int m);
      ~TAMGIAC();
      void findMaxPerimeterTri(); // Tìm chu vi lớn nhất và in tam giác đó ra
      double maxPerimeterTri(DIEM a, DIEM b, DIEM c); // Tính chu vi của tam giác

};

int main(){

    return 0;
}