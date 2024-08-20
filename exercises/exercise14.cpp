#include <iostream>
#include <string_view>
#include <optional>

enum class Animal
{
    pig, chicken, goat, cat, dog, duck,
};

constexpr std::optional<std::string_view> getAnimalName(Animal animal)
{
    switch(animal)
    {
        case Animal::pig:
            return "pig";
        case Animal::chicken:
            return "chicken";
        case Animal::dog:
            return "dog";
        case Animal::duck:
            return "duck";
        case Animal::goat:
            return "goat";
        case Animal::cat:
            return "cat";
        default:
            return std::nullopt;
    }
}

constexpr std::optional<int> printNumberOfLegs(Animal animal)
{
    switch(animal)
    {
        case Animal::duck:
        case Animal::chicken:
            return 2;
        case Animal::dog:
        case Animal::pig:
        case Animal::goat:
        case Animal::cat:
            return 4;
        default:
            return std::nullopt;
    }
}

void printDetails(Animal animal)
{
    std::string_view animalName { getAnimalName(animal).value_or("missing") };
    int animalLegs { printNumberOfLegs(animal).value_or(0) };

    std::cout << "A " << animalName << " has " << animalLegs << " legs." << '\n';
}

int main()
{
    Animal cat { Animal::cat };
    Animal chicken { Animal::chicken };

    printDetails(cat);
    printDetails(chicken);

    return 0;
}