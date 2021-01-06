#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <vector>
#include "world.h"
#include "location.h"
#include "thing.h"
#include "listofthings.h"
#include "animal.h"

class Human
{
    static const int MaxCarryWeight = 17;
    Location* location;
    ListOfThings inventory;
    int commandCount;
    World& world;
    Human(const Human&);
    void operator=(const Human&);
public:
    Human(World& theWorld);
    void getInventory() const;
    int getInventoryWeight() const;
    std::string getCommand() const;
    int getLives() const;
    bool processCommand();
    bool hasA(const std::string& item) const;
    bool hasA_LitLantern() const;
    bool hasA_LoadedGun() const;
    Thing* getPtr2ThingInInventory(const std::string& thing) const;
    Thing* getPtr2ThingInLocation(const std::string& thing);
    bool getThing(const std::string& item);
    bool dropThing(const std::string& item);
    void moveTo(const std::string& newLocation, bool lightIsOn = true);
    bool processMeadow(const std::string& command);
    bool processLake(const std::string& command);
    bool processTree(const std::string& command);
    bool processTreetop(const std::string& command);
    bool processBoulder(const std::string& command);
    bool processHole(const std::string& command);
    bool processTunnel(const std::string& command);
    bool processChamber(const std::string& command);
    bool processShaft(const std::string& command);
    bool processRoom(const std::string& command);
    void print_inventory() const;
    bool shoot(const std::string& animal);
    void miscEvents();
    void lightMatch();
    void lightMatches();
    void lightLantern();
    bool feed(const std::string& animal);
};

#endif
