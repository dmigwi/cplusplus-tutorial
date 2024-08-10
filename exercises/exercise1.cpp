#include <iostream>

double getUserInput()
{
    std::cout << "Enter a double value: ";
    double x {};
    std::cin >> x;
    return x;
}

int main() 
{

    double val1 { getUserInput() };
    double val2 ( getUserInput() );

    std::cout << "Enter +, -, *, or /: ";
    char ch {};
    std::cin >> ch;

    std::cout << val1 << ch << val2 << " is ";

    if (ch == '+')
        std::cout << val1 + val2 << '\n';
    else if (ch == '-')
        std::cout << val1 - val2 << '\n';
    else if (ch == '*')
        std::cout << val1 * val2 << '\n';
    else
        std::cout << val1 / val2 << '\n';

}