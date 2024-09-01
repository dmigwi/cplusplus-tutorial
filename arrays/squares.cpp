#include <iostream>
#include <limits>

int getUserInput()
{
    int input{};
    std::cin >> input;

    if (!std::cin){
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

int main()
{
    constexpr int squares[] {0, 1, 4, 9};
    int userInput {};
    bool isPerfectSquare;

    while(true) {
        isPerfectSquare = false;

        std::cout << "Enter a single digit integer, or -1 to quit: ";
        userInput = getUserInput();

        if (userInput == -1)
            break;

        for(int elem : squares)
        {
            if (elem == userInput){
                isPerfectSquare = true;
                break;
            }
        }

        if (isPerfectSquare)
            std::cout << userInput << " is a perfect square\n";
        else   
            std::cout << userInput << " is not a perfect square\n";
    }
    
    std::cout << "Bye\n";

    return 0;
}