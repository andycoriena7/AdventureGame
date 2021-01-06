#include <iostream>
#include <string>
using namespace std;

#include "thing.h"
#include "proto.h"

Thing::Thing() : id(""), description(""), weight(0), next(0)
{}

Thing::Thing(string i, string desc, int wt, Thing* nxt) : id(i), description(desc), weight(wt), next(nxt)
{}

Thing::~Thing() { }

string Thing::get_id() const
{
    return id;
}

string Thing::get_description() const
{
    return description;
}

void Thing::changeDescription(const string& newDescription)
{
    description = newDescription;
}

int Thing::get_weight() const
{
    return weight;
}

Thing* Thing::get_next() const
{
    return next;
}

void Thing::set_next(Thing* ptr)
{
    next = ptr;
}

void Thing::print() const
{
    cout << description << endl;
}

bool Thing::operator==(const string& name) const
{
    return id == name;
}

ostream& operator<<(ostream& out, const Thing& object)
{
    out << object.get_description();
    return out;
}

Gun::Gun(Thing* ptr)
    : Thing("gun","a gun",2,ptr), bullets(5)
{}

int Gun::howManyBullets() const
{
    return bullets;
}

bool Gun::shoot()
{
    if (bullets)
    {
        bullets--;
        if (bullets == 0) cout << "\nThat was your last bullet" << endl;
        if (bullets == 1) cout << "\nYou have only one bullet left.  You had better make it count." << endl;
    }
    else
    {
        cout << "\nYour gun is empty." << endl;
        return false;
    }
    return true;
}

bool Gun::noBullets() const
{
    return bullets == 0;
}

Ladder::Ladder(Thing* ptr)
    : Thing("ladder","a tall ladder",5,ptr)
{}


Cheese::Cheese(Thing* ptr)
    : Thing("cheese","a wedge of tasty Gouda cheese",2,ptr)
{ }

Knife::Knife(Thing* ptr)
    : Thing("knife","a sharp knife",2,ptr)
{}

Lantern::Lantern(Thing* ptr)
    : Thing("lantern","a kerosene lantern",3,ptr), lit(false)
{}

bool Lantern::isLit() const
{
    return lit;
}
void Lantern::light()
{
    cout << "The lantern is lit now" << endl;
    lit = true;
}
void Lantern::unlight()
{
    cout << "\nThe lantern goes out" << endl << endl;
    lit = false;
}

Rope::Rope(Thing* ptr)
    : Thing("rope","a rope",2,ptr), tied(true)
{}

bool Rope::isTied() const
{
    return tied;
}

void Rope::tie()
{
    tied = true;
}

void Rope::unTie()
{
    tied = false;
}

Key::Key(Thing* ptr)
    : Thing("key","a shiny brass key",1,ptr)
{}

Pole::Pole(Thing* ptr)
    : Thing("pole","a fishing pole",2,ptr)
{}

Bike::Bike(Thing* ptr)
    : Thing("bike","a rusty bike with a broken chain",3,ptr), broken(true)
{}

void Bike::fix()
{
    broken = false;
    changeDescription("a rusty bike");
    cout << "The broken chain is fixed." << endl;
}

bool Bike::isBroken() const
{
    return broken;
}

void Bike::ride() const
{
    cout << endl << endl;

    for (int i =0; i< 40; i++)
    {
        cout << '\r';
        for (int j=0; j<i; j++)
        {
            cout << ' ';
        }
        cout << "o+o";
        delay(1);
    }
    cout << endl<< endl<< "Oh no!!!  You crashed the bike.  Where's your helmet?  You just died." << endl;
}
Matches::Matches(Thing* ptr)
    : Thing("matches","a book of matches",1,ptr), count(20)
{}

int Matches::get_count() const
{
    return count;
}

bool Matches::lightMatch()
{
    if (count)
    {
        cout<< "Lit a match" <<endl;
        count--;
        if (count==0) description = "an empty book of matches.";
        return true;
    }
    return false;
}

bool Matches::lightBook()
{
    if (count)
    {
        count = 0;
        description = "an empty book of matches.";
        return true;
    }
    return false;
}

void Matches::getWet()
{
    if (count)
    {
        cout << "\nYour matches are all wet, you cannot use them." << endl;
        count = 0;
    }
}

Toolkit::Toolkit(Thing* ptr)
    : Thing("toolkit","a toolkit",3,ptr)
{}

Stalactite::Stalactite(Thing* ptr)
    : Thing("stalactite","a long sharp stalactite hanging down from the ceiling above the stalagmite",4,ptr), broken(false)
{
}

bool Stalactite::isBroken() const
{
    return broken;
}

void Stalactite::breakit()
{
    broken = true;
    changeDescription("a sharp six foot piece of a stalactite");
    cout << "\nA sharp six foot piece of the stalactite has fallen to the floor of the chamber." << endl;
}

Crowbar::Crowbar(Thing* ptr)
    : Thing("crowbar", "a crowbar", 3, ptr)
{
}

Statue::Statue(Thing* ptr)
    : Thing("statue","the Lost Golden Beagle Statue",3,ptr)
{
}

Coin::Coin(Thing* ptr)
    : Thing("coin","a gold coin",1,ptr)
{
}
