/**
 * Auto ?
 *
 */

#include <iostream>

// Not a good example, since the return type is actually very complicated to beginners
// In fact, the return type auto is deducted by the compiler, and the actual type
// related to <type_traits> std::common_type, which is implemented by `? :` operator.
template <typename T, typename U>
auto max(T x, U y)
{
  return (x > y) ? x : y;
}

int main()
{

  std::cout << max(2, 3.5) << '\n';

  double x{3.2};
  int y{2};

  std::cout << max(x, y) << '\n';

  return 0;
}
