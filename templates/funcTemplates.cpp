#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

// This function template can handle many types, so its implementation is generic
template <typename T>
void print(T x)
{
    std::cout << x; // print T however it normally prints
}

// This function only needs to consider how to print a bool, so it can specialize how it handles
// printing of a bool
void print(bool x)
{
    std::cout << std::boolalpha << x; // print bool as true or false, not 1 or 0
}

int main()
{
    // instantiates and calls function max<int>(int, int)
    std::cout << " max value is : " << max<int>(1, 2) << '\n';
    std::cout << " max value is : " << max<int>(3, 4) << '\n';
    std::cout << " max value is : " << max<float>(13, 9) << '\n';
    std::cout << " max value is : " << max<double>(8, 12) << '\n';

    print<bool>(true); // calls print<bool>(bool) -- prints 1
    std::cout << '\n';

    print<>(true);     // deduces print<bool>(bool) (non-template functions not considered) -- prints 1
    std::cout << '\n';

    print(true);       // calls print(bool) -- prints true
    std::cout << '\n';
    return 0;
}