#include <iostream>

void printChars(const char data[])
{
    for(;*data != '\0'; ++data)     // ++data is same as data = (data+1).
        std::cout << *data << ' ';
    std::cout << '\n';
}

void printReverseChars(const char data[], int length)
{
    for( int c = length-2; c>= 0; --c)  // removed null terminator from length.
        std::cout << data[c] << ' ';    // data[c] is same as *(data + c)
    std::cout << '\n';
}

int main()
{
    const char arr[] { "Hello World" };
    printChars(arr);

    printReverseChars(arr, std::size(arr));
    return 0;
}