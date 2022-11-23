# std::unique_ptr

本章开始时讨论了指针在某些情况下是如何导致 bugs 与内存泄漏的。例如当一个函数提前退出或抛出异常，都会使得指针不能被正确的删除。

```cpp
#include <iostream>

void someFunction()
{
    auto* ptr{ new Resource() };

    int x{};
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if (x == 0)
        throw 0; // 函数提前返回，ptr 将不被删除

    // 这里是 ptr 的一些操作

    delete ptr;
}
```

现在我们已经覆盖了移动语义的基础，可以回到智能指针类的主题了。作为提醒，一个智能指针是一个管理动态分配对象的类。尽管智能指针可以提供一些额外功能，其定义的特性就是管理动态分配的资源，并确保动态分配的对象可以在合适的时间（通常是智能指针离开作用域时）被正确的清理掉。

正因如此，智能指针应该永远不动态分配它们自身（否则就要承担无法正确释放的风险，意味着其所持的对象不能被释放，从而导致内存泄漏）。总是将分配智能指针在栈上（作为本地变量或者类的组合成员），当函数或者包含其的对象结束时，保证智能指针可以正确的离开作用域，以确保其所拥有的对象能被正确的释放。

C++11 标准库带来了 4 种智能指针类：`std::auto_ptr`（在 C++17 中移除）, `std::unique_ptr`， `std::shared_ptr` 以及 `std::weak_ptr`。其中 `std::unique_ptr` 是现今使用的最广泛的智能指针类，因此我们首先学习它。之后的章节中再覆盖 `std::shared_ptr` 以及 `std::weak_ptr`。

`std::unique_ptr` 是 C++11 用来替代 `std::auto_ptr` 的。它用于管理任何动态分配的且不被多个对象共享的对象。也就是说 `std::unique_ptr` 应该完全管理其持有的对象，而不是与其他类共享所有权。`std::unique_ptr` 定义在 `<memory>` 头文件。

```cpp
#include <iostream>
#include <memory> // std::unique_ptr

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
  // 分配 Resource 对象，并让其被 std::unique_ptr 所有
  std::unique_ptr<Resource> res{ new Resource() };

  return 0;
} // res 离开作用域，被分配的 Resource 被销毁
```

因为 `std::unique_ptr` 分配在栈上，它可以确保最终离开作用域，当其离开时，它将删除其管理的 Resource。

不同于 `std::auto_ptr`，`std::unique_ptr` 正确的实现了移动语义。

```cpp
#include <iostream>
#include <memory> // std::unique_ptr
#include <utility> // std::move

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
  std::unique_ptr<Resource> res1{ new Resource{} }; // Resource 在这里被创建
  std::unique_ptr<Resource> res2{}; // 开始为空指针

  std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
  std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

  // res2 = res1; // 不能编译：拷贝赋值被禁用了
  res2 = std::move(res1); // res2 行使所有权，res1 被设为空值

  std::cout << "Ownership transferred\n";

  std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
  std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

  return 0;
} // 当 res2 离开作用域，Resource 在此处被销毁
```

打印：

```txt
Resource acquired
res1 is not null
res2 is null
Ownership transferred
res1 is null
res2 is not null
Resource destroyed
```

## 访问被管理的对象

`std::unique_ptr` 拥有一个重载的操作符\*与操作符->，可用于返回被管理的资源。操作符\*返回被管理资源的引用，操作符->返回一个指针。

牢记 `std::unique_ptr` 不总是管理一个对象 -- 有可能是因为它在被创建的时候就是空的（使用默认构造函数或者传递空指针作为参数），也有可能是其管理的资源被移动到了另一个 `std::unique_ptr`。所以在使用这些操作符之前，应该检查 `std::unique_ptr` 是否真正拥有资源。幸运的是，`std::unique_ptr` 有一个隐式转型成 bool 值的方法，即其在管理资源时返回 true。

```cpp
#include <iostream>
#include <memory> // std::unique_ptr

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
  friend std::ostream& operator<<(std::ostream& out, const Resource &res)
  {
  out << "I am a resource";
  return out;
  }
};

int main()
{
  std::unique_ptr<Resource> res{ new Resource{} };

  if (res) // 使用隐式转型成为 bool 来确保 res 包含一个 Resource
    std::cout << *res << '\n'; // 打印 res 所有的 Resource

  return 0;
}
```

```txt
Resource acquired
I am a resource
Resource destroyed
```

## std::unique_ptr 与数组

不同于 `std::auto_ptr`，`std::unique_ptr` 聪明的知道是否使用标量删除还是数组删除，因此 `std::unique_ptr` 可以同时使用标量对象与数组。

然而相比于使用 `std::unique_ptr` 加上固定的数组，动态数组或是 C-style 字符串，使用 `std::array` 或 `std::vector`（或 `std::string`）会是一个更优的选项，

最佳实践：推荐直接使用 `std::array`，`std::vector` 或 `std::string`，而不是 `std::unique_ptr` 加固定数组，动态数组或 C-style 字符串。

## std::make_unique

C++14 增加了一个额外名为 `std::make_unique` 的函数。该模板函数构造一个模板类型的对象并通过传入函数的参数初始化该对象。

```cpp
#include <memory> // std::unique_ptr 与 std::make_unique
#include <iostream>

class Fraction
{
private:
  int m_numerator{ 0 };
  int m_denominator{ 1 };

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
  // 创建单个动态分配的 Fraction，可以使用自动类型推导
  auto f1{ std::make_unique<Fraction>(3, 5) };
  std::cout << *f1 << '\n';

  // 创建一个动态分配数组的 Fraction
  auto f2{ std::make_unique<Fraction[]>(4) };
  std::cout << f2[0] << '\n';

  return 0;
}
```

打印：

```txt
3/5
0/1
```

`std::make_unique` 的使用是可选的，但是比起直接创建 `std::unique_ptr` 更推荐使用它。这是因为 `std::make_unique` 的使用更加简单，同样只需要更少的类型（使用自动类型推导）。更重要的是，它解析了异常安全的问题，即 C++ 函数入参的顺序问题。

最佳实践：使用 `std::make_unique` 而不是直接通过 new 来创建 `std::unique_ptr`。

## 异常安全问题的更多细节

对于上述的“异常安全问题”，这里是一个问题的描述。

考虑以下这个表达式：

```cpp
some_function(std::unique_ptr<T>(new T), function_that_can_throw_exception());
```

编译器给予了很大的灵活性，按照如何处理这个调用。它可以创建一个新的 `T`，接着调用 `function_that_can_throw_exception()`，然后创建 `std::unique_ptr` 管理动态分配的 `T`。如果 `function_that_can_throw_exception()` 抛出了异常，那么之前分配的 `T` 将不会被释放，因为作用释放的智能指针并没有被创建。这就导致了内存泄漏。

`std::make_unique` 并不会收到上述问题影响，因为对象 `T` 的创建以及 `std::unique_ptr` 的创建，发生在 `std::make_unique` 函数内部，这就没有了执行顺序的问题。

## 从一个函数中返回 std::unique_ptr

`std::make_unique` 可以安全的被一个函数返回值：

```cpp
#include <memory> // std::unique_ptr

std::unique_ptr<Resource> createResource()
{
     return std::make_unique<Resource>();
}

int main()
{
    auto ptr{ createResource() };

    // 做些事

    return 0;
}
```

上述代码中，`createResource()` 值返回一个 `std::unique_ptr`。如果该值没有被赋予给任何变量，那么临时返回值将离开作用域，之后 `Resource` 将被清理。如果被赋值了（如上的 `main()` 中），C++14 或更早前，移动语义将会转移返回值的 `Resource` 到被赋值的变量（上述例子为 `ptr`），而 C++17 或之后，返回会被省略。这就使得通过 `std::unique_ptr` 返回一个资源比起返回裸指针更为安全！

通常而言，不应该返回指针（永远不）或者引用（除非有特殊的编译原因）的 `std::unique_ptr` 。

## 传递 std::unique_ptr 至函数

如果希望函数获取指针内容的所有权，值传递 `std::unique_ptr`。注意因为拷贝语义被禁用了，需要使用 `std::move` 来传递值。

```cpp
#include <iostream>
#include <memory> // std::unique_ptr
#include <utility> // std::move

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
  friend std::ostream& operator<<(std::ostream& out, const Resource &res)
  {
    out << "I am a resource";
    return out;
  }
};

void takeOwnership(std::unique_ptr<Resource> res)
{
  if (res)
    std::cout << *res << '\n';
} // Resource 在此销毁

int main()
{
  auto ptr{ std::make_unique<Resource>() };

  // takeOwnership(ptr); // 无效，需要使用移动语义
  takeOwnership(std::move(ptr)); // 有效：使用了移动语义

  std::cout << "Ending program\n";

  return 0;
}
```

打印：

```txt
Resource acquired
I am a resource
Resource destroyed
Ending program
```

注意这个例子中，`Resource` 的所有权被 `takeOwnership()` 转移了，因此 `Resource` 在 `takeOwnership()` 的结尾被销毁，而不是在 `main()` 的结尾销毁。

然而大多数时候并不希望函数获取资源的所有权。尽管可以传递 `std::unique_ptr` 的引用（即允许函数使用对象而不行使所有权），但是应该仅在调用函数可能会修改被管理的对象时才这样使用。

相对而言，传递资源自身（通过指针或引用，取决于 null 是否为有效参数）更好一些。这允许函数保留对调用者如何管理资源的不可知性。从 `std::unique_ptr` 获取一个裸指针，可以使用 `get()` 成员函数：

```cpp
#include <memory> // std::unique_ptr
#include <iostream>

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }

  friend std::ostream& operator<<(std::ostream& out, const Resource &res)
  {
    out << "I am a resource";
    return out;
  }
};

// 函数仅使用 resource，所以接受 resource 的指针，而不是整个 std::unique_ptr<Resource> 的引用
void useResource(Resource* res)
{
  if (res)
    std::cout << *res << '\n';
  else
    std::cout << "No resource\n";
}

int main()
{
  auto ptr{ std::make_unique<Resource>() };

  useResource(ptr.get()); // 注意：这里使用了 get() 来获取 Resource 的指针

  std::cout << "Ending program\n";

  return 0;
} // Resource 在此销毁
```

打印：

```txt
Resource acquired
I am a resource
Ending program
Resource destroyed
```

## std::unique_ptr 与类

当然用户也可以使用 `std::unique_ptr` 作为类组合的成员。这样便不再需要担心确保类的析构函数删除动态内存，因为 `std::unique_ptr` 将在类对象被销毁时一同销毁。

然而，如果类对象并没有正确的销毁（例如其动态分配没有正确的释放），那么 `std::unique_ptr` 成员也不会被销毁，那么 `std::unique_ptr` 所管理的对象也不会被释放。

## 错误使用 std::unique_ptr

有两种误用 `std::unique_ptr` 的方式，它们都可以被简单的避免。首先不要让多个类管理同一个资源。例如：

```cpp
Resource* res{ new Resource() };
std::unique_ptr<Resource> res1{ res };
std::unique_ptr<Resource> res2{ res };
```

虽然这在语法上合法，但是最后就是 `res1` 和 `res2` 都会尝试删除 `Resource`，这就导致了未定义行为。

其次不要手动删除 `std::unique_ptr` 所管理的资源：

```cpp
Resource* res{ new Resource() };
std::unique_ptr<Resource> res1{ res };
delete res;
```

如果这么做了，之后的 `std::unique_ptr` 将会删除已被删除的资源，同样导致未定义行为。

注意，`std::make_unique()` 同时避免了上述两种误用。
