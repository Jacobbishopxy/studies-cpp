#include <chrono>
#include <iostream>

#include "arr_cp.h"
#include "arr_mv.h"

class Timer {
private:
    using Clock = std::chrono::high_resolution_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
    void reset() { m_beg = Clock::now(); }

    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};

arr_cp::DynamicArray<int> cloneArrayAndDouble(const arr_cp::DynamicArray<int>& arr)
{
    arr_cp::DynamicArray<int> dbl(arr.getLength());
    for (int i = 0; i < arr.getLength(); ++i)
        dbl[i] = arr[i] * 2;

    return dbl;
}

arr_mv::DynamicArray<int> cloneArrayAndDouble(const arr_mv::DynamicArray<int>& arr)
{
    arr_mv::DynamicArray<int> dbl(arr.getLength());
    for (int i = 0; i < arr.getLength(); ++i)
        dbl[i] = arr[i] * 2;

    return dbl;
}

int main(int argc, char const* argv[])
{
    Timer t;

    arr_cp::DynamicArray<int> arr1(10e7);

    for (int i = 0; i < arr1.getLength(); ++i)
        arr1[i] = i;

    arr1 = cloneArrayAndDouble(arr1);

    std::cout << "Copy semantics time consumed: " << t.elapsed() << std::endl;

    t.reset();

    arr_mv::DynamicArray<int> arr2(10e7);

    for (int i = 0; i < arr2.getLength(); ++i)
        arr2[i] = i;

    arr2 = cloneArrayAndDouble(arr2);

    std::cout << "Move semantics time consumed: " << t.elapsed() << std::endl;

    return 0;
}
