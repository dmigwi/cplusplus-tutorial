#include <iostream>

// Programs fails with segmentation fault error due stack overflow after it
// tried allocating approx. 40 MBs to the limited size stack.
int main()
{
    int stack[10'000'000];
    std::cout << "hi" << stack[0]; // we'll use stack[0] here so the compiler won't optimize the array away

    return 0;
}