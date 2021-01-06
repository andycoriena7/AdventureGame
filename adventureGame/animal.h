#ifndef ANIMAL_H
#define ANIMAL_H

#include "thing.h"

class Animal : public Thing
{
protected:
    bool alive;
    std::string dead_description;
    bool hungry;
public:
    Animal(const std::string& i, const std::string& desc, const std::string& dead_desc, int wt, Thing* ptr);
    void kill();
    bool isAlive() const;
    bool isHungry() const;
    void setHunger(bool hunger);
    void feed();
    virtual string eats() const = 0;
};

class Eel : public Animal
{
public:
    Eel(Thing* ptr = 0);
    string eats() const;
};

class Fish : public Animal
{
public:
    Fish(Thing* ptr = 0);
        string eats() const;
};

class Spider : public Animal
{
public:
    Spider(Thing* ptr = 0);
    string eats() const;
};

class Fly : public Animal
{
public:
    Fly(Thing* ptr = 0);
    string eats() const;
};

class Frog : public Animal
{
public:
    Frog(Thing* ptr = 0);
        string eats() const;
};

class Bear : public Animal
{
public:
    Bear(Thing* ptr = 0);
        string eats() const;
};

class Minotaur : public Animal
{
public:
    Minotaur(Thing* ptr = 0);
        string eats() const;
};

class Rat : public Animal
{
public:
    Rat(Thing* ptr = 0);
        string eats() const;
};

class Serpent : public Animal
{
public:
    Serpent(Thing* ptr = 0);
        string eats() const;
};

class Bat : public Animal
{
public:
    Bat(Thing* ptr = 0);
        string eats() const;
};

class Ghost : public Animal
{
public:
    Ghost(Thing* ptr = 0);
        string eats() const;
};

#endif
