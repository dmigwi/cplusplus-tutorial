#include <iostream>
#include <vector>
#include <limits>

template <typename T>
void printArray(const std::vector<T>& arr, T val) {
    int foundIndex {-1};

    for (size_t i{0}; i < arr.size(); ++i)
    {
        std::cout << arr[i] << ' ';
        if (val == arr[i])
            foundIndex = static_cast<int>(i);
    }

    if (foundIndex == -1)
        std::cout << "\n The number " << val << " was not found\n";
    else
        std::cout << "\n The number " << val << " has index " << foundIndex << '\n';   
}

template <typename T>
T getUserInput()
{
    T input {};
    const T minLimit {0};
    const T maxLimit {10};

    do
    {
        std::cout << "Enter a number between 1 and 9: ";
        std::cin >> input;

        if (!std::cin)
            std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (input < minLimit || input > maxLimit);
    return input;
}


int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
    printArray(arr, getUserInput<int>());

    std::vector arr2{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };
    printArray(arr2, getUserInput<double>());

    return 0;
}