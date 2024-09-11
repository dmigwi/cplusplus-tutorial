#include <iostream>
#include <string>
#include <limits>
#include <algorithm>

int main()
{
    std::size_t count {};
    while(true)
    {
        std::cout << "How many names (1-10) would you like to enter? ";
        std::cin >> count;

        if (!std::cin){
            std::cin.clear();
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if ( count < 1 || count > 10)
            std::cout << "Invalid count used. Please, Try Again!\n";
        else
            break;
    }

    auto* names { new std::string [count]{}}; // dynamically allocate the array

    for(std::size_t i {0}; i < count; ++i)
    {
        std::cout << "Enter name #" << i << ": ";
        std::getline(std::cin >> std::ws,  names[i]);
    }

    auto begin { names };
    auto end { names+count };
    std::sort(begin, end);

    std::cout << "\nHere is your sorted list:\n";

    for (std::size_t k {0}; k < count; ++k)
        std::cout << "Name #" << k << ": " << names[k] << '\n';

    delete[] names;  // Delete the dynamically allocated memory
    // we don't need to set names to nullptr/0 here because it's going to go out
    // of scope immediately after this anyway.
    
    return 0;
}