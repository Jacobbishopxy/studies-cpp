# std::shared_ptr

不同于 `std::unique_ptr` 设计用来各自拥有并管理资源，`std::shared_ptr` 意为解决需要若干智能指针共同拥有同一个资源。

这就意味着可以有若干个 `std::shared_ptr` 指向同一个资源。在其内部持续追踪总共有多少个 `std::shared_ptr` 正在共享资源。只要至少有一个 `std::shared_ptr` 指向资源，那么该资源就不会被释放。一旦最后一个 `std::shared_ptr` 离开了作用域（或者重新赋值指向其它资源），那么资源则被释放。

与 `std::unique_ptr` 一样，`std::shared_ptr` 定义于 `<memory>` 头文件。

```cpp
#include <iostream>
#include <memory> // std::shared_ptr

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
  // 分配 Resource 对象，且使其被 std::shared_ptr 所有
  Resource* res { new Resource };
  std::shared_ptr<Resource> ptr1{ res };
  {
    std::shared_ptr<Resource> ptr2 { ptr1 }; // 使另一个 std::shared_ptr 指向同样的东西

    std::cout << "Killing one shared pointer\n";
  } // ptr2 离开作用域，但是无事发生

  std::cout << "Killing another shared pointer\n";

  return 0;
} // ptr1 在此离开作用域，被分配的 Resource 被销毁
```

打印：

```txt
Resource acquired
Killing one shared pointer
Killing another shared pointer
Resource destroyed
```

上述代码中创建了一个动态 `Resource` 对象，并设置一个名为 `ptr1` 的 `std::shared_ptr` 来管理它。在嵌套的代码块中使用了拷贝构造函数来创建第二个 `std::shared_ptr`（`ptr2`）指向同样的 `Resource`。当 `ptr2` 离开作用域，`Resource` 没有被释放，因为 `ptr1` 仍然指向 `Resource`。当 `ptr1` 离开作用域，`ptr1` 发现没有任何 `std::shared_ptr` 在管理 `Resource`，所以 `Resource` 被释放了。

注意第二个共享指针是由第一个共享指针创建而来的。这很重要。考虑下面类似的代码：

```cpp
#include <iostream>
#include <memory> // std::shared_ptr

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
  Resource* res { new Resource };
  std::shared_ptr<Resource> ptr1 { res };
  {
    std::shared_ptr<Resource> ptr2 { res }; // 直接从 res 创建 ptr2（而不是从 ptr1）

    std::cout << "Killing one shared pointer\n";
  } // ptr2 离开嘞作用域，被分配的 Resource 被销毁

  std::cout << "Killing another shared pointer\n";

  return 0;
} // ptr1 在此离开作用域，被分配的 Resource 再次被销毁
```

打印：

```txt
Resource acquired
Killing one shared pointer
Resource destroyed
Killing another shared pointer
Resource destroyed
```

接着程序崩溃。

上述两份代码唯一的区别在于第二份代码中创建了两个独立的 `std::shared_ptr`。结果就是尽管它们都指向了 `Resource`，它们并不知晓对方。当 `ptr2` 离开作用域，它认为它是 `Resource` 的唯一拥有者，接着被释放。当 `ptr1` 离开作用域时考虑同样的事情，尝试再次删除 `Resource`。

最佳实践：如果需要多个 `std::shared_ptr` 指向给定资源，拷贝现有的 `std::shared_ptr` 即可。

## std::make_shared

类似于在 C++14 中使用 `std::make_unique()` 创建 `std::unique_ptr`，`std::make_shared()` 可以用于创建 `std::shared_ptr`（C++11 可用）。

```cpp
#include <iostream>
#include <memory> // std::shared_ptr

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
  // 分配一个 Resource 对象，且使其被 std::shared_ptr 所有
  auto ptr1 { std::make_shared<Resource>() };
  {
    auto ptr2 { ptr1 }; // 使用拷贝 ptr1 创建 ptr2

    std::cout << "Killing one shared pointer\n";
  } // ptr2 在此离开作用域，无事发生

  std::cout << "Killing another shared pointer\n";

  return 0;
} // ptr1 离开作用域，分配的 Resource 被销毁
```

## 深挖 std::shared_ptr

不同于 `std::unique_ptr` 内部使用单个指针，`std::shared_ptr` 内部使用两个指针。一个指向了其所管理的资源，另一个指向一个“控制块”，即一个动态分配的对象用于追踪一些东西，包含了有多少个 `std::shared_ptr` 指向了资源。当一个通过 `std::shared_ptr` 构造函数创建的 `std::shared_ptr`，被管理对象（通常为传入的）的内存和控制块（由构造函数创造的）是分开的内存分配。然而当使用 `std::make_shared()`，这可以被优化成一个单独的内存分配，这带来了更好的性能。

这同时解释了为什么独立创建两个 `std::shared_ptr` 指向同一个资源会带来麻烦。每个 `std::shared_ptr` 将拥有一个指针指向资源。然而每个 `std::shared_ptr` 将独立分配其自己的控制块，即表示它是唯一拥有该资源的指针。因此当 `std::shared_ptr` 离开作用域，释放资源，并不会察觉还有其他的 `std::shared_ptr` 同样也尝试管理该资源。

然而当 `std::shared_ptr` 是由拷贝赋值克隆，数据在控制块中可以被恰当的更新来表明现在有额外一个 `std::shared_ptr` 协同管理该资源。

## std::shared_ptr 的事故

`std::shared_ptr` 有着与 `std::unique_ptr` 相同的挑战 -- 如果 `std::shared_ptr` 没有被正确的销毁（要么是因为它是动态分配的且永远没有删除，要么它是某个动态分配且永远没有删除的对象中的一部分），那么其管理的资源也不会被释放。`std::unique_ptr` 仅需要担心一个智能指针是否被正确的销毁；而 `std::shared_ptr` 需要担心所有的智能指针。如果有任何一个管理资源的 `std::shared_ptr` 没有被正确的销毁，那么资源将不能被正确的释放。

## std::shared_ptr 与数组

C++17 或更早，`std::shared_ptr` 并不能正确的管理数组，同时也不允许用来管理 C-style 数组。C++20 开始 `std::shared_ptr` 支持数组。
