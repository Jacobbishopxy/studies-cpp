#include <algorithm>
#include <array>
#include <chrono>  // std::chrono
#include <cstddef> // std::size_t
#include <iostream>
#include <numeric> // std::iota

const int g_arrayElements{10000};

class Timer
{
  private:
  using Clock = std::chrono::steady_clock;
  using Second = std::chrono::duration<double, std::ratio<1>>;

  std::chrono::time_point<Clock> m_beg{Clock::now()};

  public:
  void reset() { m_beg = Clock::now(); }

  double elapsed() const
  {
    return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
  }
};

void sortArray(std::array<int, g_arrayElements>& array)
{
  //
  for (std::size_t startIndex{0}; startIndex < (g_arrayElements - 1);
       ++startIndex)
  {
    std::size_t smallestIndex{startIndex};

    for (std::size_t currentIndex{startIndex + 1};
         currentIndex < g_arrayElements; ++currentIndex)
    {
      if (array[currentIndex] < array[smallestIndex])
      {
        smallestIndex = currentIndex;
      }
    }

    std::swap(array[startIndex], array[smallestIndex]);
  }
}

int main(int argc, char const* argv[])
{

  std::array<int, g_arrayElements> array;
  std::iota(array.rbegin(), array.rend(), 1);

  Timer t;

  sortArray(array);

  std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";

  t.reset();

  std::sort(array.begin(), array.end());

  std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";

  return 0;
}
