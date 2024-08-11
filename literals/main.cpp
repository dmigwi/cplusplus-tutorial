#include <string>
#include <iostream>

int main()
{
    std::string name {"Alex"}; // Initialize name with string lieral "Alex"
    std::cout << "His name is: " << name << '\n';

    name = "Jay";                // It resized the string size stored accordingly
    std::cout << name << '\n';

    std::cout << "Enter your full name: ";
    // std::string name{};
    // std::cin >> name; // this won't work as expected since std::cin breaks on whitespace
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter your favorite color: ";
    std::string color{};
    // std::cin >> color;
    std::getline(std::cin >> std::ws, color);

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';
    return 0;
}