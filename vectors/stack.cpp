#include <iostream>
#include <vector>

void printArray(const std::vector<int>& stack)
{
    std::cout << "\t(Stack:";

    if (stack.empty())
        std::cout << "empty";

    for (auto element : stack)
		std::cout << element << ' ';

	// \t is a tab character, to help align the text
	// std::cout << "\tCapacity: " << stack.capacity() << "  Length " << stack.size() << "\n";

    std::cout << ")\n";
}

int main() {
    std::vector<int> v {};
    printArray(v);

    v.push_back(1);
    printArray(v);

    v.push_back(2);
    printArray(v);

    v.push_back(3);
    printArray(v);

    v.pop_back();
    printArray(v);

    v.push_back(4);
    printArray(v);

    v.pop_back();
    printArray(v);

    v.pop_back();
    printArray(v);

    v.pop_back();
    printArray(v);

    return 0;
}