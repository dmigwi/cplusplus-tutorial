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

bool isValueInArray(const std::vector<std::string_view>& arr, const std::string_view searchName )
{
     for (const std::string_view word : arr){
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

    if (isValueInArray(words, name))
        std::cout << name << " was found.\n";
    else
        std::cout << name << " was not found.\n";

    return 0;
}