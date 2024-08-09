#include <iostream>

int doubleInt(int val); // Forward declaration of doubleInt function

void doSomething(int /*count*/)  // Recommended google C++ style
{}

int main() {
    doSomething(4);
    std::cout << "Executed doSomething!. Enter a number: ";

    int x { };
    std::cin >> x;
    std::cout << "The double of "<< x << " is " << doubleInt(x) << '\n';

    return 0;
}

int doubleInt(int val) {
    return val * 2;
}