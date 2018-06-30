/*
 * random.hpp
 * 
 * A wrapper for the stl random number functions
 * Josh Chandler
*/

#pragma once

#include <random>
#include <chrono>


namespace shoe {

class Random {
    public:
    Random(unsigned seed = std::chrono::system_clock::now().time_since_epoch().count())
    : m_engine(seed)
    {}

    ~Random() = default;

    int int_(int low, int high);
    double double_(double low, double high);

    private:
    std::mt19937 m_engine;
};

} // shoe