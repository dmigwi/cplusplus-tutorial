#include <cstdint> // for fast and least types
#include <cstddef> // for std::size_t
#include <iostream>

void print(int x)
{
	std::cout << x << '\n';
}

int main()
{
	std::cout << "least 8:  " << sizeof(std::int_least8_t) * 8 << " bits\n";
	std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
	std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
	std::cout << '\n';
	std::cout << "fast 8:  " << sizeof(std::int_fast8_t) * 8 << " bits\n";
	std::cout << "fast 16: " << sizeof(std::int_fast16_t) * 8 << " bits\n";
	std::cout << "fast 32: " << sizeof(std::int_fast32_t) * 8 << " bits\n";

    std::cout << sizeof(std::size_t) << '\n';

    std::cout << "float :" << std::numeric_limits<float>::is_iec559 << '\n';
    std::cout << "double :" << std::numeric_limits<double>::is_iec559 << '\n';
    std::cout << "long double :" << std::numeric_limits<long double>::is_iec559 << '\n';

    std::cout << "Input a keyboard character: ";

    char ch{};
    std::cin >> ch; // ch = 'a', "bcd" is left queued.
    std::cout << "You entered: " << ch << '\n';
    std::cin.clear();
    std::cin.ignore(INT_MAX,'\n');

    // Note: The following cin doesn't ask the user for input, it grabs queued input!
    std::cin >> ch; // ch = 'b', "cd" is left queued.
    std::cout << "You entered: " << ch << '\n';
    std::cin.clear();
    std::cin.ignore(INT_MAX,'\n');

    print(static_cast<int>(5.5));

	return 0;
}