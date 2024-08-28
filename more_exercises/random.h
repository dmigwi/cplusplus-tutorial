#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <random>
#include <chrono>

namespace Random {

    // generate creates a self-seeding generator. 
    inline std::mt19937 generate()
    {
        std::random_device rd{};
        std::seed_seq ss{
            static_cast<std::seed_seq::result_type>(
                std::chrono::steady_clock::now().time_since_epoch().count()
                ),
                rd(), rd(), rd(), rd(), rd(),
        };

        return std::mt19937{ss};
    }

    inline std::mt19937 mt { generate() };

    template <typename T>
    inline T get (T min, T max) // Max and Min value must have the same type
    {
        return std::uniform_int_distribution<T>{ min, max } (mt);
    }

}

#endif