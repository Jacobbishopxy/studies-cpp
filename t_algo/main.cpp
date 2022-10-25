#include <algorithm>
#include <array>
#include <iostream>
// #include <ranges>

void doubleNumber(int& i) { i *= 2; }

int main(int argc, char const* argv[]) {

  std::array arr{1, 2, 3, 4};

  // std::ranges::for_each(arr, doubleNumber); // Since C++20, we don't have to use begin() and end().
  std::for_each(arr.begin(), arr.end(), doubleNumber);

  for (auto& i : arr) {
    std::cout << i << ' ';
  }

  std::cout << '\n';

  return 0;
}
