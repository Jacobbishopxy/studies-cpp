#include <iostream>

struct Foo1 {
  short a{};
  short qq{};
  int b{};
  double c{};
};

struct Foo2 {
  short a{};
  int b{};
  double c{};
  short qq{};
};

int main() {
  std::cout << "The size of Foo1 is " << sizeof(Foo1) << '\n';
  std::cout << "The size of Foo2 is " << sizeof(Foo2) << '\n';

  return 0;
}