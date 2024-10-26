#ifndef RANDOM_15PUZZLE
#define RANDOM_15PUZZLE

#include <random>
#include <chrono>

namespace RandomMT
{
    // generate creates a self-seeding generator.
    inline std::mt19937 generate()
    {
        std::random_device rd {};
        std::seed_seq ss {
            static_cast<std::mt19937::result_type>(
                std::chrono::steady_clock::now().time_since_epoch().count()
            ),
            rd(), rd(), rd(), rd(), rd(), rd(), rd(),
        };
        return std::mt19937 {ss};
    }

    inline std::mt19937 mt { generate()};

    template <typename T>
    inline T get (T min, T max) // Max and Min value must have the same type
    {
        return std::uniform_int_distribution<T>{ min, max } (mt);
    }
};

#endif