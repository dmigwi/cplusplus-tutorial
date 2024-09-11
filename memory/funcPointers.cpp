#include <iostream>
#include <functional>

int foo()
{
    return 7;
}

int goo(int x)
{
    return x;
}

int main()
{
    int (*fcnPtr)() { foo };
    std::cout << "Foo value returned: " << fcnPtr() << '\n';

    int (*fcnPtr1)(int) { goo };
    std::cout << "Goo value returned: " << fcnPtr1(34) << '\n';

    [[maybe_unused]] std::function<int()> funcPtr3 { foo };
    [[maybe_unused]]

    return 0;
}