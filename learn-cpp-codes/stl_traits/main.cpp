#include <iostream>

template <typename T>
struct MyIter {
    typedef T value_type; // associated type, used as a function return type
    T* ptr;

    MyIter(T* p = 0)
        : ptr(p)
    {
    }

    T& operator*() const { return *ptr; }
};

/**
 * 1. partial template function
 */

#if 0

template <typename I>
typename I::value_type func(I ite)
{
    std::cout << "class version" << std::endl;

    return *ite;
}

template <typename I>
I func(I* ite)
{
    std::cout << "pointer version" << std::endl;

    return *ite;
}

template <typename I>
I func(const I* ite)
{
    std::cout << "const pointer version" << std::endl;

    return *ite;
}

#endif

/**
 * 2. middleware
 */

template <typename T>
struct iterator_traits {
    typedef typename T::value_type value_type;
};

// partial template #1
template <typename T>
struct iterator_traits<T*> {
    typedef T value_type;
};

// partial template #2
template <typename T>
struct iterator_traits<const T*> {
    typedef T value_type;
};

template <typename I>
typename iterator_traits<I>::value_type func(I ite)
{
    std::cout << "normal version" << std::endl;

    return *ite;
}

int main()
{
    using namespace std;

    MyIter<int> ite(new int(8));
    cout << func(ite) << endl;

    int* p = new int(52);
    cout << func(p) << endl;

    const int k = 3;
    cout << func(&k) << endl;

    return 0;
}
