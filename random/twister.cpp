#include <iostream>
#include <random> // for std::mt19937
// #include <chrono> // for std::chrono

int main()
{
	// std::mt19937 mt{}; // Instantiate a 32-bit Mersenne Twister

    // Seed our Mersenne Twister using steady_clock
	// std::mt19937 mt{ static_cast<std::mt19937::result_type>(
	// 	std::chrono::steady_clock::now().time_since_epoch().count()
	// ) };
    
    // std::mt19937 mt{ std::random_device{}() };

    std::random_device rd{};
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // get 8 integers of random numbers from std::random_device for our seed
	std::mt19937 mt{ ss }; // initialize our Mersenne Twister with the std::seed_seq

    // Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 624; ++count)
	{
		std::cout << die6(mt); // generate a random number

		// If we've printed 5 numbers, start a new row
		// if (count % 10 == 0)
		// 	std::cout << '\n';
	}

	return 0;
}