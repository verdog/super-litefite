/*
 * Object Manager
 * manages objects of various types
 * basically just gives them a name.
 * 
 * Josh Chandler
*/

#include <map>
#include <string>
#include <iostream>

#include "include/objectmanager.hpp"

namespace shoe {
    
template <typename T>
bool ObjectManager<T>::overwrite(std::string key, T &thing) {
    mMap[key] = thing;
    return true;
}

template <typename T>
bool ObjectManager<T>::load(std::string key, T &thing) {
    // return true on successful insert
    return mMap.insert(std::pair<std::string, T>(key, thing)).second;
}

template <typename T>
T& ObjectManager<T>::get(std::string key) {
    try {
        return &mMap.at(key);
    } catch ( ... ) {
        std::cerr << "Error: could not retrieve object from object manager.\n";
        return nullptr;
    }
}

} // shoe
