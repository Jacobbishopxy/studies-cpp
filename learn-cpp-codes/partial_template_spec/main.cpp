#include <cstring>
#include <iostream>

// 模板类
template <typename T>
class Storage {
private:
    T m_value;

public:
    Storage(T value)
        : m_value { value }
    {
    }

    ~Storage() { }

    void print() const { std::cout << m_value << std::endl; }
};

// 偏特化的模板类，指针用
template <typename T>
class Storage<T*> {
private:
    T* m_value;

public:
    // 重载，拷贝单独一个值，而非一个数组
    Storage(T* value)
        : m_value { new T { *value } }
    {
    }

    ~Storage() { delete m_value; }

    void print() const { std::cout << *m_value << std::endl; }
};

// 全特化的构造函数，char* 用
template <>
Storage<char*>::Storage(char* value)
{
    // 为了了解 string 的长度
    int length { 0 };
    while (value[length] != '\0')
        ++length;
    ++length; // +1 用于解释空终止符

    // 分配内存用于存储 string 值
    m_value = new char[length];

    // 拷贝实际的 string 值到刚分配的 m_value 内存
    for (int count = 0; count < length; ++count)
        m_value[count] = value[count];
}

// 全特化的析构函数，char* 用
template <>
Storage<char*>::~Storage()
{
    delete[] m_value;
}

// 全特化的 print 函数，char* 用
// 如果没有这个函数打印 Storage<char*>，则会调用
// Storage<T*>::print()，即只打印第一个字符
template <>
void Storage<char*>::print() const
{
    std::cout << m_value;
}

int main(int argc, char const* argv[])
{
    // 声明一个非指针 Storage 来证明可以工作
    Storage<int> myint { 5 };
    myint.print();

    // 声明一个指针 Storage 来证明可以工作
    int x { 7 };
    Storage<int*> myintptr { &x };

    // 如果 myintptr 对 x 实施的是指针赋值，那么修改 x 也会修改 myintptr
    x = 9;
    myintptr.print();

    // 动态分配一个临时 string
    char* name { new char[40] { "Alex" } };

    // 存储名称
    Storage<char*> myname { name };

    // 删除临时 string
    delete[] name;

    // 打印名称来证明构造时进行了拷贝
    myname.print();
    return 0;
}
