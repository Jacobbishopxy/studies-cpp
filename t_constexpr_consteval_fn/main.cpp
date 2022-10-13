#include <iostream>

consteval auto compileTime(auto value)
{
  return value;
}

constexpr int greater(int x, int y)
{
  return (x > y ? x : y);
}

int main(int argc, char const *argv[])
{
  std::cout << greater(5, 6) << '\n';
  std::cout << compileTime(greater(5, 6)) << '\n';

  int x{5};
  std::cout << greater(x, 6) << '\n';

  return 0;
}
