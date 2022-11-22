# std::move_if_noexcept

20.9 异常规范与 noexcept 中覆盖了 `noexcept` 异常说明符与操作符，即本篇的基础。

同样也覆盖了 `strong exception guarantee`，其用于保证一个函数若是被异常打断，不会有内存泄漏同时程序状态也不会改变。特别是所有的构造函数都应该是强异常保证的，因此程序的状态不会在对象的构造函数失败后有所改变。

## 移动构造函数异常问题

在拷贝对象的情况下，拷贝如果由于某些原因（例如机器内存不足）失败了，被拷贝的对象不会有任何的危害，因为原始对象在创建拷贝时并不需要被改变。这样程序可以弃置失败的拷贝并继续执行。`strong exception guarantee` 是被支持的。

现在考虑移动对象的情况。一个移动的操作转移了给定对象的所有权至目标对象。如果移动操作在转移所有权之后被异常打断，那么原始对象会处于一个被修改状态。这对于原始对象是临时对象而言并不是问题，因为在其被移动之后总是会被抛弃 -- 但是对于非临时对象而言，这就破坏了原始对象。为了遵从 `strong exception guarantee`，我们需要移动资源回去给原始对象，但是如果第一次移动就失败了，就不能保证移动回去还能成功。

那么如何能给予移动构造函数 `strong exception guarantee` 呢？在移动构造函数中避免抛出异常很容易，但是其自身有可能唤起其他的构造函数是 `potentially throwing` 的。以 `std::pair` 作为移动构造函数为例，需要移动每个字对象进入新的 pair 对象。

```cpp
// Example move constructor definition for std::pair
// Take in an 'old' pair, and then move construct the new pair's 'first' and 'second' subobjects from the 'old' ones
template <typename T1, typename T2>
pair<T1,T2>::pair(pair&& old)
  : first(std::move(old.first)),
    second(std::move(old.second))
{}
```

那么现在使用两个类，`MoveClass` 与 `CopyClass`，将它们 `pair` 在一起来证明移动构造函数的 `strong exception guarantee` 问题：

```cpp
#include <iostream>
#include <utility> // std::pair, std::make_pair, std::move, std::move_if_noexcept
#include <stdexcept> // std::runtime_error

class MoveClass
{
private:
  int* m_resource{};

public:
  MoveClass() = default;

  MoveClass(int resource)
    : m_resource{ new int{ resource } }
  {}

  // 拷贝构造函数
  MoveClass(const MoveClass& that)
  {
    // 深拷贝
    if (that.m_resource != nullptr)
    {
      m_resource = new int{ *that.m_resource };
    }
  }

  // 移动构造函数
  MoveClass(MoveClass&& that) noexcept
    : m_resource{ that.m_resource }
  {
    that.m_resource = nullptr;
  }

  ~MoveClass()
  {
    std::cout << "destroying " << *this << '\n';

    delete m_resource;
  }

  friend std::ostream& operator<<(std::ostream& out, const MoveClass& moveClass)
  {
    out << "MoveClass(";

    if (moveClass.m_resource == nullptr)
    {
      out << "empty";
    }
    else
    {
      out << *moveClass.m_resource;
    }

    out << ')';

    return out;
  }
};


class CopyClass
{
public:
  bool m_throw{};

  CopyClass() = default;

  // 拷贝构造函数在 m_throw 为 'true' 时抛出异常
  CopyClass(const CopyClass& that)
    : m_throw{ that.m_throw }
  {
    if (m_throw)
    {
      throw std::runtime_error{ "abort!" };
    }
  }
};

int main()
{
  // 创建一个没有任何问题的 std::pair
  std::pair my_pair{ MoveClass{ 13 }, CopyClass{} };

  std::cout << "my_pair.first: " << my_pair.first << '\n';

  // 但是当移动 pair 至另一个 pair 时，问题出现了
  try
  {
    my_pair.second.m_throw = true; // 触发拷贝构造函数的异常

    // 下一行将抛出异常
    std::pair moved_pair{ std::move(my_pair) }; // 之后将注释掉这一行
    // std::pair moved_pair{ std::move_if_noexcept(my_pair) }; // 之后将反注释这一行

    std::cout << "moved pair exists\n"; // 永不会打印
  }
  catch (const std::exception& ex)
  {
      std::cerr << "Error found: " << ex.what() << '\n';
  }

  std::cout << "my_pair.first: " << my_pair.first << '\n';

  return 0;
}
```

打印：

```txt
destroying MoveClass(empty)
my_pair.first: MoveClass(13)
destroying MoveClass(13)
Error found: abort!
my_pair.first: MoveClass(empty)
destroying MoveClass(empty)
```

现在来探讨一下发生了些什么。第一个打印出的行展示了用于初始化 `my_pair` 的临时 `MoveClass` 对象，其在 `my_pair` 实例化声明被执行之后立刻被销毁。它为 `empty` 是因为在 `my_pair` 中的 `MoveClass` 子对象是由移动构造的，在下一行的打印中证明了 `my_pair.first` 包含了 `MoveClass` 对象的值 `13`。

有趣的事情发生在第三行。通过拷贝构造函数创建 `moved_pair` 的 `CopyClass` 子对象（它没有移动构造函数），但是拷贝构造函数抛出了异常，因为修改了 Boolean 标记。`moved_pair` 的构造由于异常的原因失败了，同时其早前构造的成员函数被删除。这个情况下 `MoveClass` 成员被销毁，打印 `destroying MoveClass(13)`，接着就看到了 `Error found: abort!` 信息被打印出来。

当尝试再次打印 `my_pair.first` 时，显示出 `MoveClass` 成员为空。因为 `moved_pair` 的初始化使用过 `std::move` 完成的，而 `MoveClass` 成员（拥有移动构造函数）被移动构造了且 `my_pair.first` 变为空指。

最后 `my_pair` 在 `main()` 结束前销毁。

## std::move_if_noexcept 来拯救

注意上述的问题本来是可以避免的，如果 `std::pair` 尝试的是拷贝而不是移动，这种情况下 `moved_pair` 将会构造失败，但是 `my_pair` 并不会被修改。

但是拷贝有性能成本，因此不想为所有对象都付出这种代价 -- 如果安全的话，理想的情况是使用移动，其次才是拷贝。

幸运的是 C++ 有两种机制，可以组合在一起使用。

首先因为 `noexcept` 函数是 no-throw/no-fail 的，它们隐式的符合 `strong exception guarantee` 标准。因此 `noexcept` 移动构造函数是被保证可以成功的。

其次是使用标准库的函数 `std::move_if_noexcept` 在移动构造函数中（或者对象时仅可移动且没有拷贝构造函数时）不会抛出异常，那么 `std::move_if_noexcept` 将与 `std::move` 完全相同（且返回被转换成右值的对象）。否则 `std::move_if_noexcept` 将返回对象的一个普通的左值引用。

关键点：如果对象拥有一个 noexcept 移动构造函数，`std::move_if_noexcept` 将返回一个可移动的右值，否则将返回可拷贝的左值。可以使用 `noexcept` 说明符作为连接 `std::move_if_noexcept`，在当强异常保证存在时，使用移动语义（否则使用拷贝语义）。

现在更新之前例子中的代码：

```cpp
//std::pair moved_pair{std::move(my_pair)}; // 现在注释掉这一行
std::pair moved_pair{std::move_if_noexcept(my_pair)}; // 并反注释这一行
```

现在运行程序再打印：

```txt
destroying MoveClass(empty)
my_pair.first: MoveClass(13)
destroying MoveClass(13)
Error found: abort!
my_pair.first: MoveClass(13)
destroying MoveClass(13)
```

可以看到在异常抛出之后，子对象 `my_pair.first` 仍然指向值 `13`。

`std::pair` 的移动构造函数不是 `noexcept`，因此 `std::move_if_noexcept` 返回 `my_pair` 为一个左值引用。这导致 `moved_pair` 通过拷贝构造函数（而不是移动构造函数）进行创建。拷贝构造函数可以安全的抛出异常，因为它不会修改原始对象。

标准库进出使用 `std::move_if_noexcept` 来优化 `noexcept` 函数。例如 `std::vector::resize` 将使用移动语义如果元素的类型是 `noexcept` 移动构造函数，否则使用拷贝语义。这就意味着 `std::vector` 通常对于拥有 `noexcept` 移动构造函数的对象来说，其操作会更快。

警告：如果一个类型同时是潜在抛出异常的移动语义，以及删除了拷贝语义（拷贝构造函数和拷贝赋值操作符不可用），那么 `std::move_if_noexcept` 则会放弃强保证同时唤起移动语义。这种条件性的放弃强保证是普遍存在于标准库的容器类中的，因为它们时常使用 `std::move_if_noexcept`。
