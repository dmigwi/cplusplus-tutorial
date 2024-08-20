#include <iostream>

int main()
{
    enum class Color
    {
        red,
        black,
        blue,
    };

    Color shirt { Color::red };

    if (shirt == Color::black)
        std::cout << "Shirt has color black";
    else if (shirt == Color::red)
        std::cout << "Shirt has color red";


    // The shirt isn't implicitly converted to a int so it has to be implicitly cast.
    std::cout << static_cast<int>(shirt) << '\n';
}