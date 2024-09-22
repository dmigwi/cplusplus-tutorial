#include <iostream>
#include <cstdarg>

double findAverage(int count, ...)
{
    int sum {};

    std::va_list list;
    va_start(list, count); // initialize va_list using va_start.

    for (int arg{0}; arg < count; ++arg)
        sum += va_arg(list, int); // extract the arguments

    va_end(list); // cleanup

    return static_cast<double>(sum)/count;
}

int main()
{
    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';
    return 0;
}