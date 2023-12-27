/**
 * CRTP examples
 *
 * reference: http://www.vishalchovatiya.com/crtp-c-examples/
 *
 * additional reading about template: http://www.vishalchovatiya.com/c-template-a-quick-uptodate-look/
 */
#include <atomic>
#include <cassert>
#include <cstdio>
#include <exception>
#include <iostream>
#include <memory>
#include <numbers>

/**
 * 1. Static polymorphism
 *
 * compile-time polymorphism
 *
 * alternative `std::variant` + `std::visit`
 */

// a) base class exposes an interface `name()`
template <typename Derived>
struct Base
{
  void name()
  {
    (static_cast<Derived*>(this))->impl();
  }
};

// b) derived classes implement such interface `impl()`
struct D1 : public Base<D1>
{
  void impl()
  {
    std::puts("D1::impl()");
  }
};

struct D2 : public Base<D2>
{
  void impl()
  {
    std::puts("D2::impl()");
  }
};

// c) use it in template function
template <typename d_type>
void which_d(Base<d_type>& d)
{
  d.name();
}

void test1()
{
  D1 d1;
  // d1.name();

  D2 d2;
  // d2.name();

  which_d(d1);
  which_d(d2);
}

/**
 * 2. Limiting object count
 *
 * limit the arbitrary type with an arbitrary number of instances
 */

// a) base struct
template <typename ToBeLimited, uint32_t maxInstance>
struct LimitNoOfInstances
{
  static std::atomic<uint32_t> cnt;

  LimitNoOfInstances()
  {
    if (cnt >= maxInstance)
      throw std::logic_error("Too many instances");
    ++cnt;
  }

  ~LimitNoOfInstances()
  {
    --cnt;
  }
};

// b) derived struct
struct One : LimitNoOfInstances<One, 1>
{
};
struct Two : LimitNoOfInstances<Two, 2>
{
};

// c) initialize `cnt`
template <typename T, uint32_t maxNoOfInstance>
std::atomic<uint32_t> LimitNoOfInstances<T, maxNoOfInstance>::cnt(0);

void test2()
{
  Two _2_0, _2_1;

  try
  {
    One _1_0, _1_1;
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
}

/**
 * 3. Avoid code duplication
 *
 * provides common utilities solely based on derived class member function
 */

// a)
template <typename T>
class Container
{
  T& actual()
  {
    return *static_cast<T*>(this);
  }

  T const& actual() const
  {
    return *static_cast<T const*>(this);
  }

public:
  decltype(auto) front()
  {
    return *actual().begin();
  }

  decltype(auto) back()
  {
    return *std::prev(actual().end());
  }

  decltype(auto) size() const
  {
    return std::distance(actual().begin(), actual().end());
  }

  decltype(auto) operator[](size_t i)
  {
    return *std::next(actual().begin(), i);
  }
};

// b)
template <typename T>
class DynArray : public Container<DynArray<T>>
{
  size_t m_size;
  std::unique_ptr<T[]> m_data;

public:
  DynArray(size_t s)
      : m_size{s}, m_data{std::make_unique<T[]>(s)}
  {
  }

  T* begin()
  {
    return m_data.get();
  }

  const T* begin() const
  {
    return m_data.get();
  }

  T* end()
  {
    return m_data.get() + m_size;
  }

  const T* end() const
  {
    return m_data.get() + m_size;
  }
};

void test3()
{
  DynArray<int> arr(10);
  arr.front() = 2;
  arr[2] = 5;
  assert(arr.size() == 10);
}

/**
 * 4. Polymorphic method chaining
 */

// a)
template <typename ConcretePrinter>
class Printer
{
  std::ostream& m_stream;

public:
  Printer(std::ostream& s)
      : m_stream{s}
  {
  }

  ConcretePrinter& print(auto&& t)
  {
    m_stream << t;
    return static_cast<ConcretePrinter&>(*this);
  }

  ConcretePrinter& println(auto&& t)
  {
    m_stream << t << std::endl;
    return static_cast<ConcretePrinter&>(*this);
  }
};

// b)
struct ColorPrinter : Printer<ColorPrinter>
{
  enum Color
  {
    red,
    blue,
    green
  };

  ColorPrinter(std::ostream& s)
      : Printer{s}
  {
  }

  ColorPrinter& SetConsoleColor(Color c)
  {
    // ...
    return *this;
  }
};

void test4()
{
  ColorPrinter(std::cout)
      .print("Hello")
      .SetConsoleColor(ColorPrinter::Color::red)
      .println("Printer");
}

/**
 * 5. Enabling polymorphic copy construction
 */

// a)
template <typename Specific>
struct Animal
{
  std::unique_ptr<Animal> clone()
  {
    return std::make_unique<Specific>(static_cast<Specific&>(*this));
  }

protected: // forcing Animal class to be inherited
  Animal() = default;
  Animal(const Animal&) = default;
};

// b)
struct Dog : Animal<Dog>
{
  Dog() = default;
  Dog(const Dog&)
  {
    std::cout << "copied dog" << std::endl;
  }
};

struct Cat : Animal<Cat>
{
  Cat() = default;
  Cat(const Cat&)
  {
    std::cout << "copied cat" << std::endl;
  }
};

// c)
template <typename Specific>
void who_am_i(Animal<Specific>* who)
{
  auto duplicate_who = who->clone();
}

void test5()
{
  Dog d1;

  Dog d2(d1);

  Cat c1;

  who_am_i(&d2);
  who_am_i(&c1);
}

int main()
{
  // test1();
  // test2();
  // test3();
  // test4();
  test5();

  return 0;
}
