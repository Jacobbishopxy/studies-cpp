#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

class MyString
{
  private:
  std::string m_s;

  public:
  MyString(std::string_view s);

  std::string operator()(int start, int end);

  friend std::ostream& operator<<(std::ostream& out, const MyString& s);

  std::string_view substr(int start, int end) const;
};

MyString::MyString(std::string_view s) : m_s{s}
{
}

std::string MyString::operator()(int start, int len)
{
  assert(start >= 0);
  assert(start + len <= static_cast<int>(m_s.length()));
  return m_s.substr(start, len);
}

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
  out << s.m_s;

  return out;
}

std::string_view MyString::substr(int start, int len) const
{
  assert(start >= 0);
  assert(start + len <= static_cast<int>(m_s.length()));
  return std::string_view{m_s}.substr(start, len);
}

int main(int argc, char const* argv[])
{
  MyString s{"Hello, world!"};
  std::cout << s(7, 5) << std::endl;

  std::cout << s.substr(7, 5) << std::endl;

  return 0;
}
