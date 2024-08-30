#include <iostream>
#include <vector>
#include <cassert>

namespace Animals
{
    enum AnimalTypes : unsigned int
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
    
        max_animals,
    };

    const std::vector legs {2, 4, 4, 4, 2, 0, 0};
}

int main()
{
      // Ensure the number of legs is the same as the number of animals
    assert(std::size(Animals::legs) == Animals::max_animals);

    std::cout << Animals::legs[Animals::elephant];
    return 0;
}