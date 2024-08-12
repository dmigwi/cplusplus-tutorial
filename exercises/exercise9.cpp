#include "constants.h"
#include <iostream>

int accumulate(int num) 
{
    // Total is initialized once and maintained for the life of the program due
    // to the static lifetime allocated to it.
    static int total{0};
    total += num;
    return total;
}

int main()
{
	std::cout << "How many students are in your class? ";
	int students{};
	std::cin >> students;


	if (students > Constants::maxClassSize)
		std::cout << "There are too many students in this class\n";
	else
		std::cout << "This class isn't too large\n";

    std::cout << accumulate(4) << '\n'; // prints 4
    std::cout << accumulate(3) << '\n'; // prints 7
    std::cout << accumulate(2) << '\n'; // prints 9
    std::cout << accumulate(1) << '\n'; // prints 10

	return 0;
}