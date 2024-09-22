#include <iostream>
#include <string_view>
#include <array>
#include <algorithm>

struct Student
{
    std::string_view name{};
    int points{};
};

int main()
{
    constexpr std::array<Student, 8> arr {
    { { "Albert", 3 },
        { "Ben", 5 },
        { "Christine", 2 },
        { "Dan", 8 }, // Dan has the most points (8).
        { "Enchilada", 4 },
        { "Francis", 1 },
        { "Greg", 3 },
        { "Hagrid", 5 } }
    };

    constexpr auto isBest {
        [] (const Student& a, const Student& b) { return (a.points < b.points); }
    };

   const Student* bestPerformed { 
        std::max_element(arr.begin(), arr.end(), isBest)
   };
   std::cout << bestPerformed->name << " is the best student.\n";

    return 0;
}