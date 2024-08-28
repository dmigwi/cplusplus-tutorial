#include <iostream>
#include <vector>

int main()
{
    
    constexpr int len {3};
    std::vector<int> values; // declare a vector of length 3.

    std::cout << "Enter " << len << " integers: ";
    for (int i = 0; i < len; i++)
    {
        int input{};
        std::cin >> input;

        values.push_back(input);
    }

    int sum {0};
    int product {1};

    for (int element: values)
    {
       sum += element;
       product *= element;
    }

    std::cout << "The sum is: " << sum << '\n';
    std::cout << "The product is: " << product << '\n';

}