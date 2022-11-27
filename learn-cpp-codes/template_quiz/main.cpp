
#include <iostream>
#include <string>
#include <string_view>

template <typename T>
class Pair1
{
  private:
  T m_p1;
  T m_p2;

  public:
  Pair1(const T& p1, const T& p2)
      : m_p1{p1}, m_p2{p2}
  {
  }

  T& first() { return m_p1; }
  T& second() { return m_p2; }

  const T& first() const { return m_p1; }
  const T& second() const { return m_p2; }
};

template <typename T, typename S>
class Pair
{
  private:
  T m_p1;
  S m_p2;

  public:
  Pair(const T& p1, const S& p2)
      : m_p1{p1}, m_p2{p2}
  {
  }

  T& first() { return m_p1; }
  S& second() { return m_p2; }

  const T& first() const { return m_p1; }
  const S& second() const { return m_p2; }
};

template <typename T>
class StringValuePair
{
  private:
  std::string m_p1;
  T m_p2;

  public:
  StringValuePair(const std::string_view p1, const T& p2)
      : m_p1{p1}, m_p2{p2}
  {
  }

  std::string& first() { return m_p1; }
  T& second() { return m_p2; }

  const std::string& first() const { return m_p1; }
  const T& second() const { return m_p2; }
};

int main()
{
  // quiz #1
  {
    Pair1<int> p1{5, 8};
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2{2.3, 4.5};
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
  }

  // quiz #2
  {
    Pair<int, double> p1{5, 6.7};
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair<double, int> p2{2.3, 4};
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
  }

  // quiz #3
  {
    StringValuePair<int> svp{"Hello", 5};
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
  }

  return 0;
}
