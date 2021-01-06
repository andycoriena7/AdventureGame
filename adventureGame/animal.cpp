#include <string>
using namespace std;

#include "animal.h"

Animal::Animal(const string& i, const string& desc, const string& dead_desc, int wt, Thing* ptr)
    : Thing(i,desc,wt,ptr),alive(true),dead_description(dead_desc),hungry(false)
{ }

void Animal::kill()
{
    alive = false;
    description = dead_description;
}

bool Animal::isAlive() const
{
    return alive;
}

bool Animal::isHungry() const
{
    return hungry;
}

void Animal::setHunger(bool hunger)
{
    hungry = hunger;
}

void Animal::feed()
{
    hungry = false;
}

Eel::Eel(Thing* ptr)
    : Animal("eel","a slippery eel","a dead eel",2,ptr)
{
}

string Eel::eats() const
{
    return "fish";
}

Fish::Fish(Thing* ptr)
    : Animal("fish","a skinny fish","a dead fish",2,ptr)
{
}

string Fish::eats() const
{
    return "eel";
}

Spider::Spider(Thing* ptr)
    : Animal("spider","a black widow spider","a dead spider",1,ptr)
{
}

string Spider::eats() const
{
    return "fly";
}

Fly::Fly(Thing* ptr)
    : Animal("fly","a buzzing fly","a dead fly",1,ptr)
{}

string Fly::eats() const
{
    return "nothing";
}

Frog::Frog(Thing* ptr)
    : Animal("frog","a tree frog","a dead frog",2,ptr)
{}

string Frog::eats() const
{
    return "nothing";
}

Bear::Bear(Thing* ptr)
    : Animal("bear","a mean hungry bear","a dead bear",4,ptr)
{
}

string Bear::eats() const
{
    return "eel";
}


Rat::Rat(Thing* ptr)
    : Animal("rat","a skinny rat with sharp teeth","a dead rat",2,ptr)
{
}

string Rat::eats() const
{
    return "cheese";
}

Minotaur::Minotaur(Thing* ptr)
    : Animal("minotaur","an giant albino minotaur","a dead minotaur",4,ptr)
{
}
string Minotaur::eats() const
{
    return "human";
}

Serpent::Serpent(Thing* ptr)
    : Animal("serpent","a slimy serpent with red eyes and long fangs clinging to the side of the shaft","a dead serpent",3,ptr)
{
}
string Serpent::eats() const
{
    return "rat";
}

Bat::Bat(Thing* ptr)
    : Animal("bat","a vicious vampire bat flying around you","a dead bat",2,ptr)
{
}

string Bat::eats() const
{
    return "spider";
}

Ghost::Ghost(Thing* ptr)
    : Animal("ghost","a slightly-bored ghost","a dead ghost",2,ptr)
{
}

string Ghost::eats() const
{
    return "human";
}
