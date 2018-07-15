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
    bool overwrite(std::string key, T &thing);
    bool load(std::string key, T &thing);
    T& get(std::string key);
private:
    std::map<std::string, T> mMap;
}; 

} // shoe
