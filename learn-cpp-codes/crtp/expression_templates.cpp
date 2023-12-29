/**
 * @file:	expression_templates.cpp
 * @author:	Jacob Xie
 * @date:	2023/12/28 17:41:43 Thursday
 * @brief:	https://en.wikipedia.org/wiki/Expression_templates
 **/

#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <type_traits>

// A base class `VecExpression` represents any vector-valued expression. It is
// templated on the actual expression type `E` to be implemented, per the
// _curiously recurring template pattern_. The existence of a base class like
// `VecExpression` is not strictly necessary for expression templates to work.
// It will merely serve as a function argument type to distinguish the
// expressions from other types (note the definition of a `Vec` constructor and
// `operator+` below).

template <typename E>
class VecExpression
{
public:
  static constexpr bool is_leaf = false;

  double operator[](size_t i) const
  {
    // Delegation to the actual expression type. This avoids dynamic
    // polymorphism (a.k.a. virtual functions in C++)
    return static_cast<E const&>(*this)[i];
  }

  size_t size() const { return static_cast<E const&>(*this).size(); }
};

// The boolean `is_leaf` is there to tag `VecExpression`s that are '"leafs",
// i.e. that actually contain data. The `Vec` class is a leaf that stores the
// coordinates of a fully evaluated vector expression, and becomes a subclass of
// `VecExpression`.

class Vec : public VecExpression<Vec>
{
  std::array<double, 3> elems;

public:
  static constexpr bool is_leaf = true;

  decltype(auto) operator[](size_t i) const { return elems[i]; }

  // decltype(auto)& operator[](size_t i) { return elems[i]; }

  size_t size() const { return elems.size(); }

  // construct Vec using initializer list
  Vec(std::initializer_list<double> init)
  {
    std::copy(init.begin(), init.end(), elems.begin());
  }

  // A Vec can be constructed from any VecExpression, forcing its evaluation.
  template <typename E>
  Vec(VecExpression<E> const& expr)
  {
    for (size_t i = 0; i != expr.size(); ++i)
    {
      elems[i] = expr[i];
    }
  }
};

// The sum of tow `Vec`s is represented by a new type, `VecSum`, that is
// templated on the types of the left- and right-hand sides of the sum os that
// it can be applied to arbitrary pairs of `Vec` expressions. An overloaded
// `operator+` serves as syntactic sugar for the `VecSum` constructor. A
// subtlety intervenes in this case: in order to reference the original data
// when summing two `VecExpression`s, `VecSum` needs to store a const reference
// to each `VecExpression` if it is a leafs, otherwise it is a temporary object
// that needs to be copied to be properly saved.
template <typename E1, typename E2>
class VecSum : public VecExpression<VecSum<E1, E2>>
{
  // cref if leaf, copy otherwise
  typename std::conditional_t<E1::is_leaf, const E1&, const E1> _u;
  typename std::conditional_t<E2::is_leaf, const E2&, const E2> _v;

public:
  static constexpr bool is_leaf = false;

  VecSum(E1 const& u, E2 const& v) : _u(u), _v(v)
  {
    assert(u.size() == v.size());
  }

  decltype(auto) operator[](size_t i) const { return _u[i] + _v[i]; }
  size_t size() const { return _v.size(); }
};

template <typename E1, typename E2>
VecSum<E1, E2> operator+(VecExpression<E1> const& u, VecExpression<E2> const& v)
{
  return VecSum<E1, E2>(
      *static_cast<const E1*>(&u), *static_cast<const E2*>(&v)
  );
}

/*
With the above definitions, the expression `a + b + c` is of type

VecSum<VecSum<Vec, Vec>, Vec>

so `Vec x = a + b + c` invokes the templated `Vec` constructor
`Vec(VecExpression<E> const& expr)` with its template argument `E` being this
type (meaning `VecSum<VecSum<Vec, Vec>, Vec>`). Inside this constructor, the
loop body

elems[i] = expr[i];

is effectively expanded (following the recursive definitions of `operator+` and
`operator[]` on this type) to

elems[i] = a.elems[i] + b.elems[i] + c.elems[i];

with no temporary `Vec` objects needed and only one pass through each memory
block.
*/

int main(int argc, char** argv)
{
  Vec v0 = {23.4, 12.5, 144.56};
  Vec v1 = {67.12, 34.8, 90.34};
  Vec v2 = {34.90, 111.9, 45.12};

  // Following assignment will call the ctor of Vec which accept type of
  // `VecExpression<E> const&`. Then expand the loop body to a.elems[i] +
  // b.elems[i] + c.elems[i]
  Vec sum_of_vec_type = v0 + v1 + v2;

  for (int i = 0; i < sum_of_vec_type.size(); ++i)
    std::cout << sum_of_vec_type[i] << std::endl;

  // To avoid creating any extra storage, other than v0, v1, v2, one can do the
  // following (Tested with C++11 on GCC 5.3.0)
  auto sum = v0 + v1 + v2;
  for (int i = 0; i < sum.size(); ++i)
    std::cout << sum[i] << std::endl;

  return 0;
}
