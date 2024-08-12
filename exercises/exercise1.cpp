#include <iostream>

double getUserInput()
{
    std::cout << "Enter a double value: ";
    double x {};
    std::cin >> x;
    return x;
}

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main() 
{

    // register cleanup() to be called automatically when std::exit() is called
    std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now

    double val1 { getUserInput() };
    double val2 ( getUserInput() );

    std::cout << "Enter +, -, * or /: ";
    char ch {};
    std::cin >> ch;

    std::cout << val1 << ch << val2 << " is ";

    switch(ch) {
        case '+':
            val1 += val2;
            break;

        case '-':
            val1 -= val2;
            break;

        case '*':
            val1 *= val2;
            break;

        default:
            val1 /= val2;
    }

    std::cout << val1 << '\n';
}