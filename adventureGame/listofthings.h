#ifndef LISTOFTHINGS_H
#define LISTOFTHINGS_H

#include <string>
#include "thing.h"

class ListOfThings
{
    Thing*    top;
    ListOfThings(const ListOfThings&);
    void operator=(const ListOfThings&);
public:
    ListOfThings(Thing* ptr = 0);
    ~ListOfThings();
    Thing* get_top() const;
    void push(const std::string& item);
    void print() const;
    bool remove(const std::string& item);
    Thing*    find(const std::string& item) const;
    int get_weight() const;
    bool get(ListOfThings& fromList, const std::string& thing);
};

#endif
