#include <iostream>
#include <vector>
#include <string_view>

namespace Player
{
    enum Items : unsigned int
    {
        health_portion,
        torches,
        arrows,

        max_items,
    };

    std::vector<int> itemsCount(max_items);
}

std::string_view getTypeName (Player::Items item) 
{
    switch(item)
    {
        case Player::health_portion:
            return "health portion";
        case Player::torches:
            return "torch";
        case Player::arrows:
            return "arrow";
        default:
            return "unknown!!";
    }
}


void storeItem(Player::Items item, int count, const std::string_view pluralSuffix)
{
    std::cout << "You have " << count << " " << getTypeName(item);
    std::cout << ((count > 1) ? pluralSuffix : ""); // Handle plurals status.

    Player::itemsCount[item] = count;

    std::cout <<'\n';
}

void storeItems(int h_portion, int torches, int arrows)
{
    storeItem(Player::health_portion, h_portion, "s");
    storeItem(Player::torches, torches, "es");
    storeItem(Player::arrows, arrows, "s");

    std::cout << "You have " << h_portion + torches + arrows << " total items\n";
}

int main()
{
    storeItems(1, 5, 10);
    return 0;
}