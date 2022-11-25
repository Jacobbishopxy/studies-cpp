
#include <functional> // std::reference_wrapper
#include <iostream>
#include <string>
#include <vector>

class Teacher {
private:
    std::string m_name {};

public:
    Teacher(const std::string& name)
        : m_name { name }
    {
    }

    const std::string& getName() const { return m_name; }
};

using Teachers = std::vector<std::reference_wrapper<Teacher>>;

class Department {
private:
    Teachers m_teachers {};

public:
    Department(const Teachers teachers)
        : m_teachers { teachers }
    {
    }

    void add(Teacher& teacher) { m_teachers.push_back(teacher); }
};

int main(int argc, char const* argv[])
{
    Teacher jacob { "Jacob" };
    Teacher april { "April" };

    Teachers teachers {};

    {
        Department department { teachers };

        department.add(jacob);
        department.add(april);
    }

    std::cout << jacob.getName() << " still exists!\n";
    std::cout << april.getName() << " still exists!\n";

    return 0;
}
