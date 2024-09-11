#include <iostream>
#include <cassert>
#include <limits>
#include <utility>
#include <functional>

namespace Settings
{
    using ArithmeticFunction = std::function<int(int,int)>; 

    enum MathSign 
    {
        addition,
        subtraction,
        multiply,
        division,

        max_signs,
        invalid_sign,
    };

    constexpr char signs[] {'+', '-', '*', '/'};
    static_assert(max_signs == std::size(signs));
}

// getMathsOperation returns the selected mathematical operation.
Settings::MathSign getMathsOperation()
{
    while(true)
    {
        std::cout << "Please select one of the following signs (+, -, * or /): ";
        char input{};

        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int i {0}; i < Settings::max_signs; i++)
        {
            if (Settings::signs[i] == input)
                return static_cast<Settings::MathSign>(i);
        }

        std::cout << "Invalid sign. Please Try again! ";
    }

    return Settings::invalid_sign;
}

const std::pair<int, int> getTwoIntegers()
{
    int firstInt {};
    int secondInt {};

    std::cout << "Enter two space separated integers: ";
    std::cin >> firstInt >> secondInt;

    if (!std::cin)
        std::cin.clear();
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return {firstInt, secondInt};
}

int add( int x, int y) { return x + y; }

int subtract(int x, int y) { return x - y; }

int multiply(int x, int y) { return x * y; }
 
int divide (int x, int y) { return x / y; }

Settings::ArithmeticFunction getArithmeticFunction(Settings::MathSign sign)
{
    switch(sign)
    {
        case Settings::subtraction:
            return subtract;
        case Settings::multiply:
            return multiply;
        case Settings::division:
            return divide;
        default:
            return add;
    }
}

int main()
{
    const std::pair data { getTwoIntegers() };
    const Settings::MathSign operation { getMathsOperation() };
    const auto operationFunc { getArithmeticFunction(operation) };

    std::cout << "The operation result is: " << operationFunc(data.first, data.second) << '\n';
    return 0;
}