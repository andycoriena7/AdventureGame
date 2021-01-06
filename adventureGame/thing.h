#ifndef THING_H
#define THING_H

#include <string>
#include <iostream>

class Thing
{
protected:
    std::string id;
    std::string description;
    int weight;
    Thing* next;
    // Disable copy ctor and assignment operator
    Thing(const Thing&);
    bool operator=(const Thing&);
public:
    Thing();
    Thing(std::string i, std::string desc, int wt = 1, Thing* nxt = 0);
    virtual ~Thing();
    std::string get_id() const;
    std::string get_description() const;
    void changeDescription(const std::string& newDescription);
    int get_weight() const;
    Thing* get_next() const;
    void set_next(Thing* ptr);
    bool operator==(const std::string&) const;
    virtual void print() const;
};

std::ostream& operator<<(std::ostream& out, const Thing& object);

class Gun : public Thing
{
    int bullets;
public:
    Gun(Thing* ptr = 0);
    int howManyBullets() const;
    bool shoot();
    bool noBullets() const;
};

class Ladder : public Thing
{
public:
    Ladder(Thing* ptr = 0);
};

class Knife : public Thing
{
public:
    Knife(Thing* ptr = 0);
};

class Lantern : public Thing
{
    bool lit;
public:
    Lantern(Thing* ptr = 0);
    bool isLit() const;
    void light();
    void unlight();
};

class Rope : public Thing
{
    bool tied;
public:
    Rope(Thing* ptr = 0);
    bool isTied() const;
    void tie();
    void unTie();
};

class Cheese : public Thing
{
public:
    Cheese(Thing* ptr = 0);
};

class Key : public Thing
{
public:
    Key(Thing* ptr = 0);
};

class Pole : public Thing
{
public:
    Pole(Thing* ptr = 0);
};

class Bike : public Thing
{
    bool broken;
public:
    Bike(Thing* ptr = 0);
    void fix();
    bool isBroken() const;
    void ride() const;
};

class Toolkit : public Thing
{
public:
    Toolkit(Thing* ptr = 0);
};

class Matches : public Thing
{
    int count;
public:
    Matches(Thing* ptr = 0);
    int get_count() const;
    bool lightMatch();
    bool lightBook();
    void getWet();
};

class Stalactite : public Thing
{
    bool broken;
public:
    Stalactite(Thing* ptr = 0);
    bool isBroken() const;
    void breakit();
};

class Coin : public Thing
{
public:
    Coin(Thing* ptr = 0);
};

class Crowbar : public Thing
{
public:
    Crowbar(Thing* ptr = 0);
};

class Statue : public Thing
{
public:
    Statue(Thing* ptr = 0);
};

#endif
