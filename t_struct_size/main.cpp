#include <iostream>

// struct size are difference according to compiler's padding behavior

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

// struct template and its deduction guide

template <typename T, typename U> struct Pair {
  T first{};
  U second{};
};

template <typename T, typename U> Pair(T, U) -> Pair<T, U>;

int main() {
  // sizes are different
  std::cout << "The size of Foo1 is " << sizeof(Foo1) << '\n';
  std::cout << "The size of Foo2 is " << sizeof(Foo2) << '\n';

  // usage of explicit type declaration and implicit type deduction (by using deduction guide)
  Pair<int, int> p1{1, 2};
  Pair p2{1, 2};

  return 0;
}
