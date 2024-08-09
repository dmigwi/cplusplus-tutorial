#include <iostream>

int main()
{
    [[maybe_unused]] double pi { 3.1459 };
    [[maybe_unused]] double gravity { 9.8 };
    [[maybe_unused]] double phi { 1.61803 };

    std::cout << pi << '\n';
    std::cout << phi << '\n';

    std::cout << "Enter two numbers separated by space: ";

    int x {};
    int y {};

    std::cin >> x >> y;
    std::cout << "You have entered: x=" << x << " and y=" << y;

    return 0;
}