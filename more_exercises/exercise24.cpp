#include <iostream>
#include <utility>
#include <vector>

using Index = unsigned int;

template <typename T>
constexpr std::pair<Index, Index> getLimits(const std::vector<T>& arr)
{
    Index max_index {0};
    Index min_index {0};
    
    std::cout << "With array ( ";

    for (Index index{0}; index < arr.size(); index++) 
    {
        std::cout << arr[index];

        if (index != arr.size()-1)
            std::cout << ", ";

        if (arr[index] < arr[min_index])
            min_index = index;

        if (arr[index] > arr[max_index])
            max_index = index;
    }

    std::cout << " )\n";
  return {min_index, max_index};
}

template <typename T>
void printLimits(const std::vector<T>& arr)
{
    for (T element : arr)
        std::cout << element << " ";
    std::cout << '\n';
    
    std::pair limits { getLimits(arr) };

    std::cout << "The min element has index " <<  limits.first;
    std::cout << " and value " << arr[limits.first] << '\n';

    std::cout << "The max element has index " <<  limits.second;
    std::cout << " and value " << arr[limits.second] << "\n\n";
}

int main()
{
    std::vector<int> v1 { };
    std::cout << "Enter numbers to add (use -1 to stop): ";

    while (true)
    {
        int input{};
        std::cin >> input;
        if (input == -1)
            break;

        if (!std::cin) // if the previous extraction failed
        {
            std::cin.clear(); // put us back in 'normal' operation mode
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // and remove the bad input
            continue;
        }

        v1.push_back(input);
    }

    if (v1.size() == 0)
        std::cout << "The provided array has no elements";
    else
        printLimits(v1);

    return 0;
}
