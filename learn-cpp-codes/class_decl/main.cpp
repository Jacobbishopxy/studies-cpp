#include <iostream>

#include "DateProClass.h"

/**
 * Non-reusable class should be declared in its usage file.
 */
class DateClass
{
  int month;
  int day;
  int year;

  public:
  void setDate(int m, int d, int y)
  {
    month = m;
    day = d;
    year = y;
  }

  void print() { std::cout << month << '/' << day << '/' << year << std::endl; }

  void copyFrom(const DateClass& d)
  {
    // same-class object's member is accessible
    // works like Rust's `pub(crate)` announcement, but totally different mechanism
    month = d.month;
    day = d.day;
    year = d.year;
  }
};

int main(int argc, char const* argv[])
{
  DateClass d;
  d.setDate(12, 23, 1989);

  d.print();

  DateProClass dp{8, 15, 2022};

  dp.print();

  return 0;
}
