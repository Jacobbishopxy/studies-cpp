#include "constants.h"

#include <iostream>

int main(int argc, char const* argv[])
{

  std::cout << "Enter a radius: ";

  int radius{};

  std::cin >> radius;

  std::cout << "The circumference is: " << 2.0 * radius * constants::pi << '\n';

  std::cout << "The planet name is: " << constants::myName << '\n';

  return 0;
}
