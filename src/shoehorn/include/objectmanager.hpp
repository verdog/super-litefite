/*
 * Object Manager
 * manages objects of various types
 * basically just gives them a name.
 * 
 * Josh Chandler
*/

#pragma once

#include <map>
#include <string>
#include <iostream>

namespace shoe {
    
template <typename T>
class ObjectManager {
public:
    bool overwrite(const std::string &key, T &thing);
    bool insert(const std::string &key, T &thing);
    T& get(const std::string &key);
protected:
    std::map<std::string, T> mMap;
}; 
    
template <typename T>
bool ObjectManager<T>::overwrite(const std::string &key, T &thing) {
    mMap[key] = thing;
    return true;
}

template <typename T>
bool ObjectManager<T>::insert(const std::string &key, T &thing) {
    // return true on successful insert
    return mMap.insert(std::pair<std::string, T>(key, thing)).second;
}

template <typename T>
T& ObjectManager<T>::get(const std::string &key) {
    try {
        return mMap.at(key);
    } catch ( ... ) {
        std::cerr << "Error: could not retrieve object with key " << key << " from object manager.\n";
        throw "Error: could not retrieve object";
    }
}

} // shoe
