#include <string>
using namespace std;

#include "world.h"

World::World(Human* ptr) : ptr2Human(ptr), locations(0)
{ }

size_t World::size() const
{
    return locations.size();
}

void World::clear()
{
    locations.clear();
}

void World::create()
{
    locations.push_back(new Meadow);
    locations.push_back(new Tree);
    locations.push_back(new Treetop);
    locations.push_back(new Lake);
    locations.push_back(new Boulder);
    locations.push_back(new Hole);
    locations.push_back(new Tunnel);
    locations.push_back(new Chamber);
    locations.push_back(new Shaft);
    locations.push_back(new Shaft);
    locations.push_back(new Room);
}

Location* World::getLocation(const string& name)
{
    for (size_t i = 0; i < locations.size(); i++)
    {
        if (locations[i]->get_id() == name) return locations[i];
    }
    return 0;
}

Location* World::operator[](size_t index)
{
    return locations[index];
}
