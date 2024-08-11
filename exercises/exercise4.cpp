/*
#include <cstdint> // for std::uint8_t
#include <iostream>

int main()
{
    std::cout << "How old are you?\n";

    std::uint8_t age{};
    std::cin >> age; // Treats user input a char type. i.e.  user input '1' is converted to ascii value 49.

    std::cout << "Allowed to drive a car in Texas: ";

    // Replace the magic number 16 with constexpr variable.
    // Conditional if statement ?: could shorten the code here.
    if (age >= 16) 
        std::cout << "Yes";
    else
        std::cout << "No";

    // multicharacter cannot be represented using single quotes.
    std::cout << '.\n'; 

    return 0;
}
*/


#include <iostream>
#include <string_view>

int main()
{
    constexpr int ageLimit { 16 };

    std::cout << "How old are you?\n";
    int age{};
    std::cin >> age;

    std::string_view allowed { (age >= ageLimit) ? "Yes" : "No" };
    std::cout << "Allowed to drive a car in Texas: " << allowed << ".\n";

    return 0;
}
