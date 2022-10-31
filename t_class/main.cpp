#include <iostream>

class DateClass {
  int month;
  int day;
  int year;

public:
  void setDate(int m, int d, int y) {
    month = m;
    day = d;
    year = y;
  }

  void print() { std::cout << month << '/' << day << '/' << year << std::endl; }

  void copyFrom(const DateClass& d) {
    // 基于类的访问控制，与 Rust 的 pub(crate) 类似
    month = d.month;
    day = d.day;
    year = d.year;
  }
};

class DateProClass {
  int month;
  int day;
  int year;

public:
  DateProClass(int m, int d, int y) {
    month = m;
    day = d;
    year = y;
  }
};

int main(int argc, char const* argv[]) {
  DateClass d;
  d.setDate(12, 23, 1989);

  d.print();

  return 0;
}
