# Introduction to smart pointers and move semantics

考虑一个函数动态分配一个值：

```cpp
void someFunction()
{
    Resource* ptr = new Resource(); // Resource 是一个结构体或类

    // 这里对 ptr 进行一些操作

    delete ptr;
}
```

尽管上述代码看起来非常直接，它也非常容易忘记释放 ptr。即使记得在函数末尾 delete ptr，但还是有很多可能导致函数提前退出而 ptr 没有被 delete。例如：

```cpp
#include <iostream>

void someFunction()
{
    Resource* ptr = new Resource();

    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if (x == 0)
        return; // 函数提前返回，而 ptr 将不被删除！

    // 这里对 ptr 进行一些操作

    delete ptr;
}
```

或是通过一个抛出异常：

```cpp
#include <iostream>

void someFunction()
{
    Resource* ptr = new Resource();

    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if (x == 0)
        throw 0; // 函数提前退出，而 ptr 将不被删除！

    // 这里对 ptr 进行一些操作

    delete ptr;
}
```

## 智能指针来拯救

对于类而言其最好的一个地方就在于所包含的析构函数可以自动在该类对象离开作用域时自动执行。因此如果在构造函数中分配（或请求）内存，那么可以在析构函数中释放，并且可以保证在类的对象销毁时（无论是离开作用域还是显式删除，等等）内存能被释放。

那么这可以帮助我们管理以及清理指针吗？是的，可以！

```cpp
#include <iostream>

template <typename T>
class Auto_ptr1
{
  T* m_ptr;
public:
  // 通过构造函数传入一个指针
  Auto_ptr1(T* ptr=nullptr)
    :m_ptr(ptr)
  {
  }

  // 析构函数确保 m_ptr 被释放
  ~Auto_ptr1()
  {
    delete m_ptr;
  }

  // 重载解引用与操作符->，使得 Auto_ptr1 类似于 m_ptr
  T& operator*() const { return *m_ptr; }
  T* operator->() const { return m_ptr; }
};

// 简易例子用于证明上述模板代码有效
class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
  Auto_ptr1<Resource> res(new Resource()); // 注意这里分配内存

  // ... 不需要显式的 delete

  // 同样注意 Resource 在尖括号中不需要 * 符号，因为其功能已被模板所支持

  return 0;
} // res 在这里离开作用域，销毁 Resource 并释放内存
```

打印：

```txt
Resource acquired
Resource destroyed
```

首先动态创建了一个 Resource，将其作为参数传递给模版化的 Auto_ptr1 类。从这个时候开始，Auto_ptr1 变量 res 拥有了 Resource 对象（Auto_ptr1 与 m_ptr 拥有组合关系）。由于 res 声明为一个本地变量且处于作用域中，当作用域介绍时即离开作用域，随之被销毁（不需要担心忘记释放它）。正因其为一个类，当被销毁时，Auto_ptr1 析构函数被调用，并保证其所持有的 Resource 指针被删除！

只要 Auto_ptr1 被定义为本地变量，那么 Resource 将会被保证在作用域结束后被销毁，无论函数是如何终止的（即便是提前终止）。

这样的类被称为智能指针。**智能指针**是一种组合类设计用来管理动态分配内存以及确保当其对象离开作用域时内存被删除。

现在回到上面的 `someFunction()` 例子，展示智能指针是如何解决的：

```cpp
#include <iostream>

template <typename T>
class Auto_ptr1
{
  T* m_ptr;
public:
  Auto_ptr1(T* ptr=nullptr)
    :m_ptr(ptr)
  {
  }

  ~Auto_ptr1()
  {
    delete m_ptr;
  }

  T& operator*() const { return *m_ptr; }
  T* operator->() const { return m_ptr; }
};

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
  void sayHi() { std::cout << "Hi!\n"; }
};

void someFunction()
{
  Auto_ptr1<Resource> ptr(new Resource()); // ptr 现在拥有 Resource

  int x;
  std::cout << "Enter an integer: ";
  std::cin >> x;

  if (x == 0)
      return; // 函数提前返回

  // ptr 的一些操作
  ptr->sayHi();
}

int main()
{
  someFunction();

  return 0;
}
```

如果用户输入非零整数，打印：

```txt
Resource acquired
Hi!
Resource destroyed
```

如果用户输入零，打印：

```txt
Resource acquired
Resource destroyed
```

## 一个致命缺陷

Auto_ptr1 类拥有一个致命缺陷潜伏在一些自动生成的代码之后。

```cpp
#include <iostream>

// 与之前相同
template <typename T>
class Auto_ptr1
{
  T* m_ptr;
public:
  Auto_ptr1(T* ptr=nullptr)
    :m_ptr(ptr)
  {
  }

  ~Auto_ptr1()
  {
    delete m_ptr;
  }

  T& operator*() const { return *m_ptr; }
  T* operator->() const { return m_ptr; }
};

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
  Auto_ptr1<Resource> res1(new Resource());
  Auto_ptr1<Resource> res2(res1); // 作为选择，不初始化 res2 接着赋值 res2 = res1;

  return 0;
}
```

打印：

```txt
Resource acquired
Resource destroyed
Resource destroyed
```

很有可能程序在这点会崩溃。可以看出问题了吗？因为用户并没有提供一个拷贝构造函数或是赋值操作符，C++ 则帮忙提供了浅拷贝的函数。因此当通过 res1 初始化 res2 时，两个 Auto_ptr1 变量都指向了同一个 Resource。当 res2 离开作用域，资源被删除，使得 res1 成为了悬垂指针。当 res1 要删除（已被删除了）她的 Resource 时，程序崩溃！

运行以下函数也会发生类似的问题：

```cpp
void passByValue(Auto_ptr1<Resource> res)
{
}

int main()
{
  Auto_ptr1<Resource> res1(new Resource());
  passByValue(res1);

  return 0;
}
```

这个程序中，res1 会被值拷贝进入 passByValue 的参数 res 中，导致了重复的 Resource 指针。崩溃！

那么这并不好，应该怎么进行修复呢？

一种方法是显式定义并删除拷贝构造函数以及赋值操作符，有此来第一时间阻止任何拷贝的发生。

但是该如何从一个函数中返回 Auto_ptr1 给调用者呢？

```cpp
??? generateResource()
{
  Resource* r{ new Resource() };
  return Auto_ptr1(r);
}
```

不可以返回 Auto_ptr1 的引用，因为本地 Auto_ptr1 会在函数结束后销毁，调用者将会得到一个悬垂引用。可以返回一个指针 r 像是 `Resource*`，但是之后有可能忘记删除它，这也是使用智能指针最好的地方。值返回 Auto_ptr1 作为一种选择是有意义的 -- 但是会得到浅拷贝，重复指针，以及崩溃。

另一种选项就是重写拷贝构造函数以及赋值操作符来进行深拷贝。这种方式下至少可以避免了相同对象的重复指针。但是拷贝是昂贵的（可能并不值得或甚至不可能），因此不希望做不必要的拷贝。另外赋值或者初始化一个裸指针并不能拷贝其指向的对象，所以为什么期望智能指针可以有所不同呢？

## 移动语义

那么如果不是拷贝构造函数以及赋值操作符拷贝指针（拷贝语义），而是从原始对象转移/移动指针的所有权到目标对象呢？这就是移动语音背后的核心观点。**移动语义 move semantics**意味着类会转移对象的所有权而不是进行拷贝。

```cpp
#include <iostream>

template <typename T>
class Auto_ptr2
{
  T* m_ptr;
public:
  Auto_ptr2(T* ptr=nullptr)
    :m_ptr(ptr)
  {
  }

  ~Auto_ptr2()
  {
    delete m_ptr;
  }

  // 拷贝构造函数实现移动语义
  Auto_ptr2(Auto_ptr2& a) // 注意：非 const
  {
    m_ptr = a.m_ptr;    // 转移裸指针，从来源到本地对象
    a.m_ptr = nullptr;  // 确保来源不再拥有该指针
  }

  // 赋值操作符实现移动语义
  Auto_ptr2& operator=(Auto_ptr2& a) // 注意：非 const
  {
    if (&a == this)
      return *this;

    delete m_ptr;       // 确保首先释放已有的任何指针
    m_ptr = a.m_ptr;    // 接着转移裸指针，从来源到本地对象
    a.m_ptr = nullptr;  // 确保来源不再拥有该指针
    return *this;
  }

  T& operator*() const { return *m_ptr; }
  T* operator->() const { return m_ptr; }
  bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
  Auto_ptr2<Resource> res1(new Resource());
  Auto_ptr2<Resource> res2; // 开始于 nullptr

  std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
  std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

  res2 = res1; // res2 假定拥有所有权，res1 设置为 null

  std::cout << "Ownership transferred\n";

  std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
  std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

  return 0;
}
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

注意重载的操作符= 转移了 m_ptr 的所有权，从 res1 到 res2！因此不再会有重复拷贝的指针，所有东西都变得非常的整洁。
