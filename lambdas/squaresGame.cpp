#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

#include "Random.h"

namespace Settings
{
    constexpr int minLimit {2};
    constexpr int maxLimit {4};
}

int getUserInput(const char* promptText)
{
    int input{};
    bool isValid {false};

    while(!isValid)
    {
        isValid = true; // Confirm that a valid read operation took place.
        std::cout << promptText;
        std::cin >> input;


        if (!std::cin)
        {
            std::cin.clear();
            isValid = false; // Confirm the value read was invalid
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return input;
}

int main()
{
    int startNumber { getUserInput("Start where? ") };
    int howMany { getUserInput("How many? ") };
    int multiplier { Random::get(Settings::minLimit, Settings::maxLimit) };

    std::vector<int> nums (static_cast<std::size_t>(howMany)); 
    std::generate(nums.begin(), nums.end(), 
            [=]() mutable {
                int i = startNumber * startNumber * multiplier;
                ++startNumber;
                return i;
            }
        );
    
    std::cout << "I generated " << howMany << " square numbers."
                << " Do you know what each number is after multiplying it by "
                << multiplier <<"?\n";

    while (nums.size() > 0)
    {
        int search { getUserInput("> ") };
        auto found { std::find(nums.begin(), nums.end(), search)};

        if (found != nums.end())
        {
            nums.erase(found);
            std::cout << "Nice! " << nums.size() << " number(s) left.\n";
        }
        else{
            std::cout << search << " is wrong! Try " << nums[0] << " next time.\n";
            break;
        }
    }

    if (nums.size() == 0)
    {
        std::cout << "Nice! You found all numbers, good job!\n";
    }
    
    return 0;
}