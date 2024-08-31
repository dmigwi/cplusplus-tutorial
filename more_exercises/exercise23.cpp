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

std::string_view getTypeName (Player::Items item, int count=0) 
{
    // Handle plurals status using the condition if else.
    switch(item)
    {
        case Player::health_portion:
            return  (count > 1) ? "health portions" : "health portion";
        case Player::torches:
            return  (count > 1) ? "torches" : "torch";
        case Player::arrows:
            return  (count > 1) ? "arrows" : "arrow";
        default:
            return "unknown!!";
    }
}


void storeItem(Player::Items item, int count)
{
    std::cout << "You have " << count << " " << getTypeName(item, count) << '\n';
    Player::itemsCount[item] = count;
}

void storeItems(int h_portion, int torches, int arrows)
{
    storeItem(Player::health_portion, h_portion);
    storeItem(Player::torches, torches);
    storeItem(Player::arrows, arrows);

    std::cout << "You have " << h_portion + torches + arrows << " total items\n";
}

int main()
{
    storeItems(1, 5, 10);
    return 0;
}