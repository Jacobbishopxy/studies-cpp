#include <iostream>

consteval auto compileTime(auto value) { return value; }

constexpr int greater(int x, int y) { return (x > y ? x : y); }

// decltype(t + u) 类型推导
// -> 返回类型后置
template <typename T, typename U>
auto add0(T t, U u) -> decltype(t + u) {
  return t + u;
}

// 可省略类型推导
template <typename T, typename U>
auto add1(T t, U u) {
  return t + u;
}

// C++20 的 concepts，省略模板
auto add2(auto t, auto u) { return t + u; }

int main(int argc, char const *argv[]) {
  std::cout << "1. " << greater(5, 6) << '\n';
  std::cout << "2. " << compileTime(greater(5, 6)) << '\n';

  int a{5};
  std::cout << "3. " << greater(a, 6) << '\n';

  double x{1.2};
  int y{1};

  std::cout << add0(x, y) << std::endl;
  std::cout << add1(y, y) << std::endl;
  std::cout << add2(x, y) << std::endl;

  return 0;
}
