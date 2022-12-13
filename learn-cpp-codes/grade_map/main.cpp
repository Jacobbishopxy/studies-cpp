#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

struct StudentGrade
{
  std::string name{};
  char grade{};
};

class GradeMap
{
  private:
  std::vector<StudentGrade> m_map{};

  public:
  char& operator[](std::string_view name);
};

char& GradeMap::operator[](std::string_view name)
{
  auto found{
      std::find_if(m_map.begin(), m_map.end(), [&](const auto& student)
                   { return (student.name == name); })};

  if (found != m_map.end())
  {
    return found->grade;
  }

  m_map.push_back({std::string{name}});

  return m_map.back().grade;
}

int main(int argc, char const* argv[])
{
  GradeMap grades{};

  grades["Joe"] = 'A';
  grades["Frank"] = 'B';

  std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
  std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
  std::cout << "Mia has a grade of " << grades["Mia"] << '\n';

  return 0;
}
