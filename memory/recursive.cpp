#include <iostream>

int iterativeFunc(int value)
{
    int product {1};
    for (int i{1}; i <= value; ++i)
        product *= i;

    return product;
}

int recursiveFunc(int value)
{
    if (value <= 1)
        return 1;

    return  recursiveFunc(value-1) * value;
}

int main()
{
    std::cout << "The Iterative 7! (factorial) is: " << iterativeFunc(7) << '\n';
    std::cout << "The Recursive 7! (factorial) is: " << recursiveFunc(7) << '\n';
    return 0;
}