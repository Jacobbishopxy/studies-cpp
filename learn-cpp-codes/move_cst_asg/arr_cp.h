#pragma once

#include <iostream>

namespace arr_cp
{

template <typename T>
class DynamicArray
{
  private:
  T* m_array;
  int m_length;

  public:
  DynamicArray(int length)
      : m_array(new T[length]), m_length(length)
  {
  }

  ~DynamicArray() { delete[] m_array; }

  // copy constructor
  DynamicArray(const DynamicArray& arr)
      : m_length(arr.m_length)
  {
    m_array = new T[m_length];
    for (int i = 0; i < m_length; ++i)
      m_array[i] = arr.m_array[i];
  }

  // copy assignment
  DynamicArray& operator=(const DynamicArray& arr)
  {
    if (&arr == this)
      return *this;

    delete[] m_array;

    m_length = arr.m_length;
    m_array = new T[m_length];

    for (int i = 0; i < m_length; ++i)
      m_array[i] = arr.m_array[i];

    return *this;
  }

  int getLength() const { return m_length; }
  T& operator[](int index) { return m_array[index]; }
  const T& operator[](int index) const { return m_array[index]; }
};

} // namespace arr_cp
