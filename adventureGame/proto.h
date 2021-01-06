#ifndef PROTO_H
#define PROTO_H

#include <vector>
#include <string>

#include "location.h"
#include "thing.h"
#include "world.h"

//size_t getLocationIndexFromString(const std::string& loc, const std::vector<Location>& places);
//size_t getThingIndexFromString(const std::string& thing, const std::vector<Thing>& stuff);
bool processMeadow();
void intro();
void clearscreen();
void print_verbs();
void createWorld(std::vector<Location*>& places);
void createStuff(ListOfThings& stuff);
std::string secondWordOfCommand(const std::string& command);
void delay(int i);

const std::string Prompt = "\n===> ";
void changeDescriptionOfLocation(World& world,const string& location, const string& newDescription);
void win();


#endif // PROTO_H
