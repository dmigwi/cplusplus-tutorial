#include <string>
#include <string_view>
#include <iostream>

std::string getNames(std::string_view desc)
{
    std::cout << "Enter the names of person " << desc << ": ";
    std::string name {};
    std::getline(std::cin >> std::ws, name);
    return name;
}

int getAge(std::string_view name)
{
    std::cout << "Enter the age of " << name << ": ";
    int age {};
    std::cin >> age;
    return age;
}

int main() 
{
    std::string names { getNames("") };
    int age { getAge(names) };
    int letters { static_cast<int>(names.length()) };
    std::cout << "Your age + length of name is: " << age + letters << '\n';

    std::string names1 { getNames("#1") };
    int age1 { getAge(names1) };

    std::string names2 { getNames("#2") };
    int age2 { getAge(names2) };

    if( age1 > age2)
        std::cout << names1 << "(age "<< age1 <<") is older than "<< names2 <<" (age "<< age2 << ").\n";
    else
        std::cout << names2 << "(age "<< age2 <<") is older than "<< names1 <<" (age "<< age1 << ").\n";


    return 0;
}