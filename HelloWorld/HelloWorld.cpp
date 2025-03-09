#include <iostream>

void doNothing(int&) 
{}

int main()
{
    std::cout << " Here comes the Jumbo! :)" << std::endl;

    int x;
    doNothing(x);

    std::cout << "The value of x is: " << x << std::endl;

    return 0;
}