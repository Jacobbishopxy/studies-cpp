#include <iostream>

#include "DateProClass.h"

// Implementation of a non-trivial member function
void DateProClass::print() { std::cout << m_month << '/' << m_day << '/' << m_year << std::endl; };
