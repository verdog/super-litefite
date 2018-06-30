/*
 * random.cpp
 * 
 * A wrapper for the stl rnadom number functions
 * Josh Chandler
*/

#include "include/random.hpp"

namespace shoe {

// generate an int. range is inclusive [ ].
int Random::int_(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(m_engine);
}

// generate a double. range is half open [ ).
double Random::double_(double low, double high) {
    std::uniform_real_distribution<double> dist(low, high);
    return dist(m_engine);
}

}