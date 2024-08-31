#include <iostream>
#include <string_view>
#include <string>
#include <array>

namespace Animal
{
    enum Type
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,

        max_animals,
    };

    struct Data
    {
        std::string_view name{};
        int num_of_legs{};
        std::string_view sound{};
    };

    constexpr std::array<Data, max_animals> animalsData {{
        {"chicken", 2, "cluck"},
        {"dog", 4, "woof"},
        {"cat", 4, "meow"},
        {"elephant", 4, "pawoo"},
        {"duck", 2, "quack"},
        {"snake", 0, "hissss"},
    }};
};

// Overloaded operator>> allows the std::cin to resolve tha animal name text
// into its respective animal type enum.
std::istream& operator>> (std::istream& in, Animal::Type& animalType)
{
    std::string rawInput{};
    std::getline(in >> std::ws, rawInput);

    for (std::size_t index {0}; index < Animal::max_animals; ++index)
        {
            if (Animal::animalsData[index].name == rawInput)
            {
                animalType = static_cast<Animal::Type>(index);
                return in;
            } 
        }

    in.setstate(std::ios_base::failbit); // signal failure in reading the correct color.
    animalType = Animal::max_animals;
    return in;
}

void printAnimal(const Animal::Data& animal)
{
    std::cout << "A " << animal.name << " has " 
                << animal.num_of_legs << " legs and says " 
                << animal.sound << ".\n";
}

int main()
{
    std::cout << "Enter an animal name: ";

    Animal::Type input{};
    std::cin >> input;

    if (!std::cin || input == Animal::max_animals)
        std::cout << "That animal couldn't be found.\n";
    else
        printAnimal(Animal::animalsData[input]);

    std::cout << "\nHere is the data for the rest of the animals:\n";

    for (std::size_t index {0}; index < Animal::max_animals; ++index)
    {
        if (index != input)
            printAnimal(Animal::animalsData[index]);
    }
}