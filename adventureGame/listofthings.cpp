#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#include "animal.h"
#include "listofthings.h"

ListOfThings::ListOfThings(Thing* ptr) : top(ptr)
{
}

Thing* ListOfThings::get_top() const
{
    return top;
}


ListOfThings::~ListOfThings()
{
    Thing* temp = top;
    while (temp != 0)
    {
        top = top -> get_next();
        delete temp;
        temp = top;
    }
}

void ListOfThings::push(const string& item)
{
    Thing* ptr2Thing = 0;
    if (item == "gun") ptr2Thing = new Gun(top);
    else if (item == "ladder") ptr2Thing = new Ladder(top);
    else if (item == "knife") ptr2Thing = new Knife(top);
    else if (item == "lantern") ptr2Thing = new Lantern(top);
    else if (item == "rope") ptr2Thing = new Rope(top);
    else if (item == "key") ptr2Thing = new Key(top);
    else if (item == "pole") ptr2Thing = new Pole(top);
    else if (item == "eel") ptr2Thing = new Eel(top);
    else if (item == "fish") ptr2Thing = new Fish(top);
    else if (item == "bike") ptr2Thing = new Bike(top);
    else if (item == "toolkit") ptr2Thing = new Toolkit(top);
    else if (item == "matches") ptr2Thing = new Matches(top);
    else if (item == "spider") ptr2Thing = new Spider(top);
    else if (item == "bear") ptr2Thing = new Bear(top);
    else if (item == "frog") ptr2Thing = new Frog(top);
    else if (item == "fly") ptr2Thing = new Fly(top);
    else if (item == "rat") ptr2Thing = new Rat(top);
    else if (item == "cheese") ptr2Thing = new Cheese(top);
    else if (item == "stalactite") ptr2Thing = new Stalactite(top);
    else if (item == "minotaur") ptr2Thing = new Minotaur(top);
    else if (item == "serpent") ptr2Thing = new Serpent(top);
    else if (item == "bat") ptr2Thing = new Bat(top);
    else if (item == "coin") ptr2Thing = new Coin(top);
    else if(item == "crowbar") ptr2Thing = new Crowbar(top);
    else if (item == "statue") ptr2Thing = new Statue(top);
    else if (item == "ghost") ptr2Thing = new Ghost(top);
    if (ptr2Thing) top = ptr2Thing;
}

void ListOfThings::print() const
{
    Thing* temp = top;
    while (temp != 0)
    {
        if (temp->get_id()=="gun")
        {
            Gun* gunPtr = dynamic_cast<Gun*>(temp);
            cout << temp -> get_description() << " with " << gunPtr->howManyBullets() << " bullets" << endl;
        }
        else if (temp->get_id()=="matches")
        {
            Matches* matchesPtr = dynamic_cast<Matches*>(temp);
            cout << temp -> get_description() << " with ";
            if (matchesPtr->get_count()) cout << matchesPtr->get_count();
            else cout << "no";
            cout << " matches" << endl;
        }
        else cout << temp -> get_description() << endl;
        temp = temp -> get_next();
    }
    cout << endl;
}

int ListOfThings::get_weight() const
{
    int weight = 0;
    Thing* temp = top;

    while (temp != 0)
    {
        weight += temp -> get_weight();
        temp = temp -> get_next();
    }
    return weight;
}


Thing* ListOfThings::find(const string& item) const
{
    Thing* temp = top;
    while (temp != 0)
    {
        if (temp->get_id() == item) return temp;
        temp = temp -> get_next();
    }
    return 0;
}

bool ListOfThings::remove(const string& item)
{
    if (!find(item))
    {
        cerr << item << " is not in the ListOfThings\n";
        return false;
    }
    Thing* temp1 = top;
    Thing* temp2;
    if (top->get_id() == item)
    {
        top = top -> get_next();
        delete temp1;
        return true;
    }
    while (temp1->get_next()->get_id() != item)
    {
        temp1 = temp1 -> get_next();
    }
    temp2 = temp1 -> get_next();
    temp1->set_next(temp2 -> get_next());
    delete temp2;
    return true;
}


bool ListOfThings::get(ListOfThings& fromList, const std::string& thing)
{
    Thing* ptr2thing = fromList.find(thing);
    if (!ptr2thing)
    {
        cerr << thing << " is not in the ListOfThings\n";
        return false;
    }
    Thing* temp1 = fromList.get_top();
    Thing* temp2;
    if (fromList.get_top()->get_id() == thing)
    {
        fromList.top = fromList.get_top() -> get_next();
        temp1->set_next(top);
        top = temp1;
        return true;
    }

    while (temp1->get_next()&& temp1->get_next()->get_id() != thing)
    {
        temp1 = temp1 -> get_next();
    }
    temp2 = temp1 -> get_next();
    temp1->set_next(temp2 -> get_next());
    temp2->set_next(top);
    top = temp2;
    return true;
}
