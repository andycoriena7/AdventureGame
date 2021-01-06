#ifndef LOCATION_H
#define LOCATION_H

#include <string>

#include "thing.h"
#include "listofthings.h"

class Location
{
protected:
    std::string id;
    std::string description;
    bool isDark;
    ListOfThings contents;
public:
    Location(const char* i, const char* d, bool dark = false);
    virtual ~Location() {}
    std::string get_id() const;
    std::string get_description() const;
    void set_description(const std::string& new_description);
    void print_description(bool lightIsOn = true) const;
    ListOfThings& get_contents();
    void describe(bool lightIsOn = true) const;
    void print_contents() const;
    void set_isDark(bool darkOrLight);
    bool get_isDark() const;
    friend std::ostream& operator<<(std::ostream& out, const Location& thing);
    virtual void help() const = 0;
};

class Meadow : public Location
{
public:
    Meadow();
    void help() const;
};

class Tree : public Location
{
public:
    Tree();
    void help() const;
};

class Treetop : public Location
{
public:
    Treetop();
    void help() const;
};

class Lake : public Location
{
public:
    Lake();
    void help() const;
};

class Boulder : public Location
{
public:
    Boulder();
    void help() const;
};

class Hole : public Location
{
public:
    Hole();
    void help() const;
};

class Tunnel : public Location
{
public:
    Tunnel();
    void help() const;
};

class Chamber : public Location
{
public:
    Chamber();
    void help() const;
};

class Shaft : public Location
{
public:
    Shaft();
    void help() const;
};

class Room : public Location
{
public:
    Room();
    void help() const;
};

#endif // LOCATION_H
