#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>

#include "location.h"

class Human;

class World
{
    Human* ptr2Human;
    std::vector<Location*> locations;
    World(const World&);
    World& operator=(const World&);
public:
    World(Human* ptr = 0);
    size_t size() const;
    void clear();
    void create();
    Location* getLocation(const std::string& name);
    Location* operator[](size_t index);
};

#endif // WORLD_H
