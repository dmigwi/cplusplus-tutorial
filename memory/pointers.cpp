#include <iostream>

enum class Type
{
    tInt,
    tFloat,
    tCString,
};

void printValue(void* ptr, Type type)
{
    switch (type)
    {
        case Type::tInt:
            std::cout << *static_cast<int*>(ptr) << '\n'; // cast and perform indirection
            break;
        case Type::tFloat:
            std::cout << *static_cast<float*>(ptr) << '\n';
            break;
        case Type::tCString:
            // Only casting is performed here as subsequent indirection results to
            // only the first char bieng printed instead of the whole word.
            std::cout << static_cast<char *>(ptr) << '\n';
            break;
        default:
            std::cerr << "printValue(): invalid type provided\n";
            assert(false && " type not found");
    }
}

int main()
{
    int* ptr { new (std::nothrow) int {} };
    if (!ptr)
    {
        std::cerr << "Failed to allocate memory \n";
        return -1;
    }

    *ptr = 7;

    std::cout << " The value of ptr is :" << *ptr << '\n';

    // deallocate the memory after use.
    delete ptr;
    ptr = nullptr;

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>.
    constexpr int length {5};
    auto* array { new int[length] {9, 7, 5, 3, 1 }};

    // Accessing array
    for (int i {0}; i < length; i++)
        std::cout << " >>> " << array[i] << '\n';
    
    delete[] array;

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    int** nums { new int*[length] };
    for (int j {0}; j < length; j++)
        nums[j] = new int [j];
    
    // Deleting array
    for (int k {0}; k < length; k++)
        delete[] nums[k]; // Delete nested arrays first.
    delete[] nums; // Delete main array.

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    int nValue {5};
    float fValue {7.5f};
    char szValue[]{ "Mollie" };

    printValue(&nValue, Type::tInt);
    printValue(&fValue, Type::tFloat);
    printValue(szValue, Type::tCString);

    return 0;
}