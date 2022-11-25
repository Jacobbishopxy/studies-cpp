#include <cassert> // assert()
#include <initializer_list> // std::initializer_list
#include <iostream>

class IntArray {
private:
    int m_length {};
    int* m_data {};

public:
    IntArray() = default;

    IntArray(int length)
        : m_length { length }
        , m_data { new int[length] {} }
    {
    }

    // 委派构造函数（第二个构造函数），进行直接初始化（direct initialization）
    // 构造函数体内进行元素拷贝
    IntArray(std::initializer_list<int> list)
        : IntArray(static_cast<int>(list.size()))
    {
        int count { 0 };
        for (auto element : list) {
            m_data[count] = element;
            ++count;
        }
    }

    ~IntArray() { delete[] m_data; }

    // 避免浅拷贝
    IntArray(const IntArray&) = delete;

    // 避免浅拷贝
    IntArray& operator=(const IntArray& list) = delete;

    // 赋值操作符重载，以 `std::initializer_list<int>` 作为入参
    IntArray& operator=(std::initializer_list<int> list)
    {
        // 如果新列表的大小不一致，重新分配它
        int length { static_cast<int>(list.size()) };
        if (length != m_length) {
            delete[] m_data;
            m_length = length;
            m_data = new int[length] {};
        }

        // 从 list 初始化 array
        int count { 0 };
        for (auto ele : list) {
            m_data[count] = ele;
            ++count;
        }

        return *this;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int getLength() const { return m_length; }
};

int main(int argc, char const* argv[])
{
    IntArray array { 5, 4, 3, 2, 1 }; // initializer list
    for (int count { 0 }; count < array.getLength(); ++count)
        std::cout << array[count] << ' ';

    std::cout << '\n';

    array = { 1, 3, 5, 7, 9, 11 };

    for (int count { 0 }; count < array.getLength(); ++count)
        std::cout << array[count] << ' ';

    std::cout << '\n';

    return 0;
}
