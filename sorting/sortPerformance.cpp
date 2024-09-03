#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <string_view>

#include "Timer.h"

namespace Settings
{
    constexpr std::size_t length {100'000};
}

const std::array<int, Settings::length> inline generateAndShuffleArray()
{
    std::array<int, Settings::length> rawArr {};
    // Populate the array with numbers from 1 to 100 with difference of 1 between them.
    std::iota(rawArr.begin(), rawArr.end(), 1);

    std::random_device rd{};

    std::seed_seq ss{
        static_cast<std::seed_seq::result_type>(
            Timer::Clock::now().time_since_epoch().count()
        ),
        rd(), rd(), rd(), rd(), rd(), rd(), rd(),
    };

    // Randomly shuffle the array using the merssiene twister PNG algorithm. 
    std::shuffle(rawArr.begin(), rawArr.end(), std::mt19937{ss});

    return rawArr;
}

// Test the standard library sort perfomance;
template<std::size_t N>
double libSort(std::array<int, N>& listToSort)
{
    Timer tt{}; // Start the timer.

    std::sort(listToSort.begin(), listToSort.end());

    return tt.elapsed(); // return the time it took to complete the sort.
}

// Test the custom selection sort perfomance;
template<std::size_t N>
double selectionSort(std::array<int, N>& listToSort)
{
    Timer tt{}; // Start the timer.

    for (std::size_t i {0}; i < Settings::length-1; ++i)
    {
        std::size_t minIndex {i};
        for (std::size_t j { i+1 }; j < Settings::length; ++j)
        {
            if (listToSort[minIndex] > listToSort[j])
                minIndex = j;
        }
        std::swap(listToSort[i], listToSort[minIndex]);
    }

    return tt.elapsed(); // return the time it took to complete the sort.
}

// Test the custom bubble sort perfomance;
template<std::size_t N>
double bubbleSort(std::array<int, N>& listToSort)
{
    Timer tt{}; // Start the timer.

    // Step through each element of the array (except the last,
    // which will already be sorted by the time we get to it)
    for (std::size_t i {0}; i < Settings::length-1; ++i)
    {
        // It takes into consideration that every iteration sorts one element
        // which not be sorted again. The last element has no pair to compare against.
        for (std::size_t j {0}; j < (Settings::length - i -1); ++j){
            // Comparison sign can be adjusted to sort in ascending or descending order.
            if (listToSort[j] > listToSort[j+1])
                std::swap(listToSort[j], listToSort[j+1]);
        }
    }

    return tt.elapsed(); // return the time it took to complete the sort.
}

template<std::size_t N>
constexpr std::string_view isSorted(std::array<int, N>& listArr)
{
    if (std::is_sorted(listArr.begin(), listArr.end()))
        return  "sorted";
    else 
        return  "Un-sorted";
}



int main()
{
    // Standard lib sort performance testing
    std::array libArr { generateAndShuffleArray() };
    std::cout << "Sorting by standard sort lib took " << libSort(libArr) 
                << " sec and is " << isSorted(libArr) << '\n';

    // Selection Sort performance testing
    std::array selectionSortArr { generateAndShuffleArray() };
    std::cout << "Sorting by SelectionSort took " << selectionSort(selectionSortArr) 
                << " sec and is " << isSorted(selectionSortArr) << '\n';

    // BubbleSort performance testing.
    std::array bubbleSortArr { generateAndShuffleArray() };
    std::cout << "Sorting by BubbleSort took " << bubbleSort(bubbleSortArr) 
                << " sec and is " << isSorted(bubbleSortArr) << '\n';

    return 0;
}

// Sort 100,000 integers on my Mac, outputs:
/*
    Sorting by standard sort lib took 0.00567511 sec is sorted
    Sorting by SelectionSort took 30.4601 sec is sorted
    Sorting by BubbleSort took 79.538 sec is sorted
*/
