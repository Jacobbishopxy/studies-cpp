#include <iostream>
#include <string_view>
#include <type_traits>

class Base {
public:
    // 该版本的 getThis() 返回一个指向 Base 类的指针
    virtual Base* getThis()
    {
        std::cout << "called Base::getThis()\n";
        return this;
    }
    void printType() { std::cout << "returned a Base\n"; }
};

class Derived : public Base {
public:
    // 通常的重写函数必须返回与基类函数相同类型的对象
    // 然而，因为 Derived 是从 Base 派生而来，因此返回 Derived* 而不是 Base*
    Derived* getThis() override
    {
        std::cout << "called Derived::getThis()\n";
        return this;
    }
    void printType() { std::cout << "returned a Derived\n"; }
};

/**
 * 总结：
 *
 * 1. 派生类中的 getThis 可以作为基类中的 getThis 签名的子类型，因此可以覆盖；
 * 2. Base*-> 上的调用始终要满足 Base 的签名（静态）；
 * 3. 协变逆变（静态，编译时）跟程序运行行为（动态，运行时）没关系
 */
int main()
{
    Derived d {};
    Base* b { &d };

    // 调用 Derived::getThis()，返回 Derived*，调用 Derived::printType
    d.getThis()->printType();

    // 调用 Derived::getThis()，返回 Base*，调用 Base::printType
    // 注1：返回 Base* 是因为在编译期表现的类型是 Base*
    // 注2：Base*->上的调用始终要满足Base的签名
    b->getThis()->printType();

    static_assert(std::is_same_v<Base*, decltype(b->getThis())>);

    return 0;
}
