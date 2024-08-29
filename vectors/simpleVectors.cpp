#include <iostream>
#include <vector>

int main()
{
    
    constexpr int len {4};
    int sum {0};
    int product {1};
    std::vector<int> values(len); // declare a vector of length 3.

    std::cout << "Enter " << len << " integers: ";
    for (size_t i {0}; i < len; ++i)
    {
        std::cin >> values[i];
        sum += values[i];
        product *= values[i];
    }

    std::cout << "The sum is: " << sum << '\n';
    std::cout << "The product is: " << product << '\n';

}