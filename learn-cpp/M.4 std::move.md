# std::move

一旦开始普遍的使用移动语义，会发现有时希望唤起移动语义，但是处理的对象却是左值而不是右值。考虑下面代码：

```cpp
#include <iostream>
#include <string>

template<class T>
void myswapCopy(T& a, T& b)
{
  T tmp { a };  // 唤起拷贝构造函数
  a = b;        // 唤起拷贝赋值
  b = tmp;      // 唤起拷贝赋值
}

int main()
{
  std::string x{ "abc" };
  std::string y{ "de" };

  std::cout << "x: " << x << '\n';
  std::cout << "y: " << y << '\n';

  myswapCopy(x, y);

  std::cout << "x: " << x << '\n';
  std::cout << "y: " << y << '\n';

  return 0;
}
```

打印：

```cpp
x: abc
y: de
x: de
y: abc
```

上一节讲到过拷贝性能低，而这个版本的 swap 做了三次拷贝。

C++11 中 `std::move` 作为一个标准库函数转型（使用 `static_cast`）它的参数成为右值引用，因此移动语义可以被唤起。所以可以使用 `std::move` 来转换左值成为一个想要被移动而不是拷贝的类型，`std::move` 定义于 `<utility>` 头文件。

以下是使用了 `std::move` 转换左值成为右值并唤起移动语义的例子：

```cpp
#include <iostream>
#include <string>
#include <utility> // std::move

template<class T>
void myswapMove(T& a, T& b)
{
  T tmp { std::move(a) }; // 唤起移动构造函数
  a = std::move(b);       // 唤起移动赋值
  b = std::move(tmp);     // 唤起移动赋值
}

int main()
{
  std::string x{ "abc" };
  std::string y{ "de" };

  std::cout << "x: " << x << '\n';
  std::cout << "y: " << y << '\n';

  myswapMove(x, y);

  std::cout << "x: " << x << '\n';
  std::cout << "y: " << y << '\n';

  return 0;
}
```

打印：

```txt
x: abc
y: de
x: de
y: abc
```

## 另一个例子

在填充容器的元素时，可以使用 `std::move`，例如通过左值填充 `std::vector`。

下列的例子中，首先通过拷贝语义添加一个元素给向量。接着通过移动语义再添加一个元素。

```cpp
#include <iostream>
#include <string>
#include <utility> // std::move
#include <vector>

int main()
{
  std::vector<std::string> v;

  // 这里使用 std::string，因为它是可移动的（std::string_view 不可移动）
  std::string str { "Knock" };

  std::cout << "Copying str\n";
  v.push_back(str); // 调用左值版本的 push_back，即拷贝 str 至数组元素

  std::cout << "str: " << str << '\n';
  std::cout << "vector: " << v[0] << '\n';

  std::cout << "\nMoving str\n";

  v.push_back(std::move(str)); // 调用右值版本的 push_back，即移动 str 至数组元素

  std::cout << "str: " << str << '\n'; // 这个结果是难以确定的
  std::cout << "vector:" << v[0] << ' ' << v[1] << '\n';

  return 0;
}
```

可能打印：

```txt
Copying str
str: Knock
vector: Knock

Moving str
str:
vector: Knock Knock
```

第一种情况中，传递给 `push_back()` 的是一个左值，因此它使用了拷贝语义来添加元素至向量。也正是这个原因，str 仍然还在。

第二种情况中，传递给 `push_back()` 的是一个右值（事实上是左值通过 `std::move` 转换的），因此它使用了移动语义来添加元素至向量。这更高效，因为向量元素可以窃取字符串的值而不是拷贝值。

## 被移动后的对象将变为无效，不过也可能处于不确定的状态

当从一个临时对象中移动值，无需在意被移动的对象会是什么样子，因为临时对象会被立刻销毁。但是如果是使用了 `std::move` 之后的左值对象呢？

这里有两派的学说。第一种学说认为被移动后的对象应该被重置成为默认/零值状态，该对象再也不拥有任何资源了；另一种学说认为应该怎么简单怎么来，在不便利的情况下，不需要限制清除移动后的对象。

那么标准库是怎么处理的呢？关于这个问题 C++ 标准说“除非另外指定，被移动后的对象（其类型是定义于 C++ 标准库中的）应该放置在一个有效但是未指明的状态”。

本章的例子中，在调用 `std::move` 之后再打印 `str` 的值，得出的是空字符串。然而这不是必须得，它可以打印任何有效的字符串，包括空字符串、原始字符串、或者其他有效字符串。因此，用户应该避免使用被移动过后的对象，因为其结果是根据实现制定的。

关键点：`std::move()` 提示编译器程序员不再需要改值的对象了。仅对持久对象使用 `std::move()`，并且不要对移动后对象的值做任何的假设。当值被移动后，该对象再次被赋值时可以的（使用操作符=）。

## `std::move()` 还在那里有用？

当排列数组元素时， `std::move()` 同样也非常的有用。很多排序算法（例如选择排序和冒泡排序）都是由元素之前进行交换完成的。

同样有用的地方在于从一个智能指针中移动内容至另一个智能指针。
