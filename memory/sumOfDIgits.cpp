#include <iostream>
#include <limits>
#include <vector>

int sum(int digits)
{
    if (digits < 10)
        return digits;

    return sum(digits/10) + (digits % 10);
}

int getUserInput()
{
    while(true)
    {
        std::cout << "Enter an integer: ";
        int input{};
        std::cin >> input;

        if (!std::cin)
        {
            std::cout << "Invalid input. Please Try again!. ";
            std::cin.clear();
        }
        else
            return input;
            
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void printBinary(unsigned int n)
{
   if (n > 1)
    printBinary(n / 2);

    std::cout << n % 2;
}

int main()
{
    std::cout << " The sum of 357 is: " << sum(357) << '\n';
    std::cout << " The sum of 93427 is: " << sum(93427) << '\n';

    printBinary(static_cast<unsigned int>(getUserInput()));
    std::cout << '\n';
    return 0;
}