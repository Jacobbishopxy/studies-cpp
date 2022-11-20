# R-value references

第 9 章中介绍了值分类的概念，即表达式的属性帮助判定一个表达式解析为值，函数，还是对象。同样也介绍了左值与右值。

C++11 添加了被称为右值引用的一种新的引用，其被设计用来初始化右值（仅）。左值引用的创建时通过单个 & 符号，右值引用的创建则是使用双 & 符号：

```cpp
int x{ 5 };
int &lref{ x };   // 左值引用初始化使用左值 x
int &&rref{ 5 };  // 右值引用初始化使用右值 5
```

右值引用不可以通过左值进行初始化。

| R-value reference       | Can be initialized with | Can modify |
| ----------------------- | ----------------------- | ---------- |
| Modifiable l-values     | No                      | No         |
| Non-modifiable l-values | No                      | No         |
| R-values                | Yes                     | Yes        |

| R-value reference to const | Can be initialized with | Can modify |
| -------------------------- | ----------------------- | ---------- |
| Modifiable l-values        | No                      | No         |
| Non-modifiable l-values    | No                      | No         |
| R-values                   | Yes                     | No         |

右值引用有两个属性非常有用。首先右值引用延长了对象的寿命，从初始化的寿命延长到了右值引用（左值引用给 const 对象也可以做到）。其次，非 const 右值引用允许用户修改右值！

```cpp
#include <iostream>

class Fraction
{
private:
  int m_numerator;
  int m_denominator;

public:
  Fraction(int numerator = 0, int denominator = 1) :
    m_numerator{ numerator }, m_denominator{ denominator }
  {
  }

  friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
  {
    out << f1.m_numerator << '/' << f1.m_denominator;
    return out;
  }
};

int main()
{
  auto &&rref{ Fraction{ 3, 5 } }; // 临时 Fraction 的右值引用

  // f1 的操作符<< 绑定临时值，没有进行拷贝
  std::cout << rref << '\n';

  return 0;
} // rref（以及临时 Fraction）离开作用域
```

打印：

```txt
3/5
```

作为一个匿名对象，`Fraction{ 3, 5 }` 通常会在其定义的表达式完成时离开作用域。然而因为通过了右值引用来初始化它，其生命周期被延长到了作用域的结束。因此可以使用右值引用来打印 Fraction 的值。

现在来看一个不那么直觉的例子：

```cpp
#include <iostream>

int main()
{
  int &&rref{ 5 }; // 因为对字面值进行右值引用初始化，临时值 5 在这里被创建
  rref = 10;
  std::cout << rref << '\n';

  return 0;
}
```

打印：

```txt
10
```

虽然通过右值引用来初始化一个字面值接着在修改该值的整个过程看起来很奇怪，但是当右值引用初始化字面值时，一个临时对象从字面值上被构造，因此引用是对临时对象的引用，而不是字面值。

右值引用通常不会像上述展示的方法那样使用。

## 右值引用作为函数入参

右值引用常用与函数入参。这对于函数重载时，希望左值与右值入参产生不同的行为而言非常的有用。

```cpp
#include <iostream>

void fun(const int &lref) // 左值入参选择该函数
{
  std::cout << "l-value reference to const\n";
}

void fun(int &&rref)      // 右值入参选择该函数
{
  std::cout << "r-value reference\n";
}

int main()
{
  int x{ 5 };
  fun(x); // 左值入参调用左值版本的函数
  fun(5); // 右值入参调用右值版本的函数

  return 0;
}
```

打印：

```txt
l-value reference to const
r-value reference
```

为什么需要这样呢？下一节将会进行详细讲解。无需多言，它是移动语义中的一个重要部分。

一个有趣的点：

```cpp
int &&ref{ 5 };
fun(ref);
```

实际上调用的是左值版本的函数！尽管变量 ref 的类型是*整数的右值引用*，它自身实际上是一个左值（因为是命名的变量）。迷惑的来源来自于使用了右值在两个不同的上下文中。可以这么理解：命名对象是左值；匿名对象是右值。那么对于命名对象或是匿名对象的类型而言是独立于其是否为左值或者右值的。或者用另一种方式说，即右值引用被任何东西调用了，这个迷惑变不存在了。

## 返回一个右值引用

用户应该永远不要返回一个右值引用，同样的理由也永远不要返回一个左值引用。大多数情况下，当引用对象离开函数作用域时，返回得到的总会是悬垂引用。
