#include <iostream>
#include <string_view>
#include <array>

struct Item
{
    std::string_view    name{};
    int                 gold {};
};

template <std::size_t N>
void printArray(const std::array<Item, N>& arr)
{
    for(const Item& data : arr)
        std::cout << "A " << data.name << " costs " << data.gold << " gold. \n";
}

int main()
{
    constexpr std::array<Item, 4> arr {{
            {"sword" ,5},
            {"dagger" ,3},
            {"club" ,2},
            {"spear" ,7},
        }};

    // constexpr std::array arr {
    //         Item{"sword" ,5},
    //         Item{"dagger" ,3},
    //         Item{"club" ,2},
    //         Item{"spear" ,7},
        // };

    printArray(arr);

    return 0;
}