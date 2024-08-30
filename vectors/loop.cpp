#include <iostream>
#include <string>
#include <string_view>
#include <vector>

const std::string getUserInput()
{
    std::cout << "Enter a name: ";
    std::string name {};
    std::getline(std::cin >> std::ws, name);
    return name;
}

template <typename T>
bool isValueInArray(const std::vector<T>& arr, const T& searchName )
{
     for (const T& word : arr){
        if (word.compare(searchName) == 0){
            return true;
        }
    }
    return false;
}

int main()
{
    const std::vector<std::string_view> words{ "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly" };
    const std::string_view name { getUserInput() };

    if (isValueInArray<std::string_view>(words, name))
        std::cout << name << " was found.\n";
    else
        std::cout << name << " was not found.\n";

    return 0;
}