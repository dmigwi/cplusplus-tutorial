#include <iostream>

int main()
{
    int* ptr { };

     std::cout << *ptr << '\n'; // undefined behavior

    {
        int x{ 5 };
        ptr = &x; // assign the pointer to an object that will be destroyed (not possible with a reference)
    } // ptr is now dangling and pointing to invalid object

    if (ptr) // condition evaluates to true because ptr is not nullptr
        std::cout << *ptr << '\n'; // undefined behavior

    return 0;
}