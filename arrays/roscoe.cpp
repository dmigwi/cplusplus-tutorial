#include <array>
#include <iostream>
#include <string>
#include <string_view>
#include <limits>

#include "random.h"

namespace Portion
{
    enum Type
    {
        healing,
        mana,
        speed,
        invinsibility,

        max_items,
    };

    constexpr std::array costs { 20, 30, 12, 50 };
    constexpr std::array types { healing, mana, speed, invinsibility };
    constexpr std::array<std::string_view,max_items> names { "healing", "mana", "speed", "invinsiblity" };

    inline int minCost() {
        int min = costs[0];
        for(const auto& v: costs)
           min = (v < min) ? v : min;
        return min;
    }

    static_assert(costs.size() == max_items);
    static_assert(names.size() == max_items);
    static_assert(types.size() == max_items);
}

class Customer
{
    public:
        explicit Customer(const std::string_view name, int gold = Random::get<int>(s_minValue, s_maxValue))
            : m_name {name}, m_ownedGold {gold}
            {}
        
        bool buyItem(Portion::Type itemType)
        {
            // check if adequate balance exists.
            if (m_ownedGold >= Portion::costs[itemType])
            {
                // add a new entry of the purchased items.
                m_boughtItems[itemType]++;
                m_ownedGold -= Portion::costs[itemType];
                return true;
            }
            return false;
        }

        constexpr int ownedGold() const { return m_ownedGold; }
        constexpr std::string_view name() const { return m_name; }
        int boughtItems(Portion::Type item) const { return m_boughtItems[item]; }

    private:
        static constexpr int s_minValue {85};
        static constexpr int s_maxValue {120};

        std::string_view m_name {};
        int m_ownedGold {};
        std::array<int, Portion::max_items> m_boughtItems{};
};

Customer getCustomerInfo()
{
   std::cout << "Welcome to Roscoe's potion emporium!\n"
                << "Enter your name: ";

    std::string name{};
    std::getline(std::cin >> std::ws, name);

    Customer customer {name};
    std::cout << "Hello, " <<  name << ", you have "
                << customer.ownedGold() << " gold.\n";

    return customer;
}

void printTodaysSelection()
{
    std::cout << "\nHere is our selection for today:\n";
    for (const auto& elem: Portion::types)
        std::cout << elem << ") " << Portion::names[elem] << " costs "
                << Portion::costs[elem] << '\n';
}

bool purchasePortion(Customer* const customer)
{
    std::cout << "Enter the number of the portion you'd like to buy, or 'q' to quit: ";
    char input {};

    while(true) 
    {
        std::cin >> input;
         if (!std::cin){
            std::cin.clear();
        }
       
        if (input == 'q') 
            return true; // Is true on user shutdown request.
        else if (!std::cin.eof() && std::cin.peek() != '\n')
            input = {};  // If extraneous chars, delete current input read.

        // Clear any left-over characters left in the buffer.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (input >= '0' && input < ('0' + Portion::max_items)) // valid input detected.
        {
            // Converts ASCII to its respective integer when extracting Item Type.
            Portion::Type portion { static_cast<Portion::Type>(input - '0') };

            if (customer->buyItem(portion)) // is purchase successful?
                std::cout << "You purchased a potion of "<< Portion::names[portion];
            else
                std::cout << "Not enough gold left. Try another purchase";
        
            std::cout << ". You have " << customer->ownedGold() << " gold left.\n";
            break;
        }
        else
            std::cout << "That is an invalid input. Try again: ";
    }
    return false;
}

void printGameSummary(Customer* const customer)
{
    std::cout << "\nYour inventory contains:\n";
    for(const auto& elem : Portion::types)
        std::cout << customer->boughtItems(elem) << "x portion of " << Portion::names[elem] << '\n';

    std::cout << "You escaped with " << customer->ownedGold() <<" gold remaining.\n"
                <<"Thanks for shopping at Roscoe's potion emporium!\n";
}

int main()
{
    Customer customer { getCustomerInfo() };
    const int minimumCost {Portion::minCost()};
    bool isShutdown { false };

    while(customer.ownedGold() >= minimumCost && !isShutdown)
    {
        printTodaysSelection();
        isShutdown = purchasePortion(&customer);
    }
    printGameSummary(&customer);
}