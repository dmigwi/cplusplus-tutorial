/*
#include <iostream>

int main()
{

    int y { 10 };
    int x { 5 };
    int& ref { x };

    ref = y;

    std::cout << "x :" << x << '\n';
    std::cout << "ref :" << ref << '\n';

    return 0;
}
*/

#include <iostream>

// Function-like macro that evaluates to true if the type (or object) is equal to or smaller than
// the size of two memory addresses
#define isSmall(T) (sizeof(T) <= 2 * sizeof(void*))
#define getSize(T) (sizeof(T))

struct S
{
    double a;
    double b;
    double c;
};

int main()
{
    std::cout << std::boolalpha; // print true or false rather than 1 or 0
    std::cout << isSmall(int) << " >> " << getSize(int) << '\n'; // true
    std::cout << isSmall(double) << " >> " << getSize(double) << '\n'; // true
    std::cout << isSmall(S) << " >> " << getSize(S) <<  '\n'; // false

    return 0;
}