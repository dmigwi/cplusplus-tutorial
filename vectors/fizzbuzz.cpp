#include <iostream>
#include <string_view>
#include <vector>
#include <limits>

int getInput() {
    int input {};
    do {
        std::cout << "Enter a value between 10 and 150: ";
        std::cin >> input;

        if (!std::cin){
            std::cin.clear();
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (input < 10  || input > 150);

    return input;
}

int main() {
    using namespace std::literals::string_view_literals;
    const std::vector placeHolders {
        "fizz"sv, "buzz"sv, "pop"sv, "bang"sv, "jazz"sv, "pow"sv, "boom"sv,
        };
    
    const std::vector primeNo { 3, 5, 7, 11, 13, 17, 19 };

    int maxValue { getInput() };

    for (int num {1}; num <= maxValue; ++num) {
        bool isDivisible { false };

        for (size_t k {0}; k < primeNo.size(); ++k) {
            if ( num % primeNo[k] == 0) {
                isDivisible = true;
                // Print the factors placeholders
                std::cout << placeHolders[k] ;
            }
        }

        if (!isDivisible) {
            std::cout << num; // print the actual number if no factors were found.
        }

        std::cout << '\n';
    }

    return 0;
}