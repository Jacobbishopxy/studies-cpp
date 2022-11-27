#ifndef DATE_PRO_H
#define DATE_PRO_H

/**
 * - Trivial Constructors & Destructors should be declared in .h file.
 * - Accessors functions (getters & setters are trivial) should be declared in .h file.
 */
class DateProClass
{
  int m_month;
  int m_day;
  int m_year;

  public:
  // prefer initializer list
  DateProClass(int m, int d, int y) : m_month{m}, m_day{d}, m_year{y} {}

  // constructor declaration
  DateProClass(int y) : m_month{1}, m_day{1}, m_year{y} {}

  int getMonth() { return m_month; }
  void setMonth(int m) { m_month = m; }

  int getDay() { return m_day; }
  void setDay(int d) { m_day = d; }

  int getYear() { return m_year; }
  void setYear(int y) { m_year = y; }

  // assume this is a non-trivial member function
  void print();
};

#endif
