#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

#include "location.h"
#include "thing.h"
#include "proto.h"

Location::Location(const char* i, const char* d, bool dark)
    : id(i), description(d), isDark(dark), contents(0)
{}

string Location::get_id() const
{
    return id;
}

string Location::get_description() const
{
    return description;
}

void Location::set_description(const string& new_description)
{
    description=new_description;
}

ListOfThings& Location::get_contents()
{
    return contents;
}
void Location::set_isDark(bool darkOrLight)
{
    isDark = darkOrLight;
}

bool Location::get_isDark() const
{
    return isDark;
}
void Location::describe(bool lightIsOn) const
{
    print_description(lightIsOn);

    cout << endl;
    if (lightIsOn && contents.get_top()!= 0)
    {
        cout << "You can also see" << endl;
        print_contents();
    }
}

void Location::print_contents() const
{
    Thing* temp = contents.get_top();
    while (temp != 0)
    {
        cout << temp -> get_description() << endl;
        //   if (temp->get_next() && temp->get_next()->get_next()!= 0) cout << ", ";
        //    else if (temp->get_next() && temp->get_next()->get_next()== 0) cout << " and ";
        temp = temp -> get_next();
    }
    //  cout << '.' << endl;
}

void Location::print_description(bool lightIsOn) const
{
    size_t charPrinted = 8;
    cout << "You are ";
    string word;

    string printThisDescription;
    if (lightIsOn) printThisDescription = description;
    else
    {
        printThisDescription = description.substr(0,description.find('.'));
        printThisDescription += ".  You cannot see anything.";
    }

    istringstream sin(printThisDescription);
    while (sin >> word)
    {
        cout << word << ' ';
        charPrinted += word.size() +1;
        if (charPrinted > 66)
        {
            cout << endl;
            charPrinted = 0;
        }
    }
    cout << endl;
}

Meadow::Meadow()
    : Location("meadow","in a meadow next to a lake.  There is a large oak tree containing a tire swing, a crevice in the ground, a large boulder, and an old fence with a broken gate.  Next to the boulder is a sign that reads \'Beware of falling rocks\'.")
{
    contents.push("gun");
    contents.push("ladder");
    contents.push("knife");
    contents.push("bike");
    contents.push("toolkit");
    contents.push("cheese");
}

void Meadow::help() const
{
    vector<string> aids;
    aids.push_back("Be sure to check out the tree and the lake.");
    aids.push_back("You'll need help to climb the tree.");
    aids.push_back("Don't eat the cheese.");
    aids.push_back("To get up the tree, you might want to lean the ladder against it.");
    aids.push_back("To climb the tree, you'll need to set the ladder down and lean it against the tree.");
    cout << aids[rand()%aids.size()] << endl;
}

Tree::Tree()
    : Location("tree","in a large oak tree.  You can see the rope hanging down.  You could go back down or you could go higher.  The branches don't look very safe and there is an ill wind blowing.")
{
    contents.push("lantern");
    contents.push("frog");
}

void Tree::help() const
{
    vector<string> aids;

    aids.push_back("It's funny that you would find a lantern here.");
    aids.push_back("There must be a reason that you can go higher.");
    aids.push_back("You shouldn't be afraid to go higher");
    aids.push_back("You'll probably want to get that rope.");
    aids.push_back("You know you don't have to get everything you see.");

    cout << aids[rand()%aids.size()] << endl;
}

Treetop::Treetop()
    : Location("treetop","at the top of a large oak tree.  You can see the tire swing tied to a branch high up in the tree.  You can see the meadow below, the fence with the broken gate, the lake, the large boulder.  There is something curious behind the boulder.")
{
    contents.push("rope");
}

void Treetop::help() const
{
    vector<string> aids;
    aids.push_back("That rope swing is tied pretty tight.");
    aids.push_back("The view up here is pretty good.");
    aids.push_back("Enjoy the view");

    cout << aids[rand()%aids.size()] << endl;
}

Lake::Lake()
    : Location("lake","standing waist-deep in a cold lake next to a meadow.  You can see dark leaves and sticks on the bottom of the lake.")
{
    contents.push("key");
    contents.push("pole");
    contents.push("eel");
    contents.push("fish");
}

void Lake::help() const
{
    vector<string> aids;
    aids.push_back("There are 3 dangerous animals here.");
    aids.push_back("It is important to get rid of the right animal first");
    aids.push_back("Watch out for that dark area in the bottom of the lake");
    aids.push_back("Why is that key shiny?");
    cout << aids[rand()%aids.size()] << endl;
}

Boulder::Boulder()
    : Location("boulder","behind the large boulder, standing next to a dark hole in the ground.")
{
    contents.push("matches");
}

void Boulder::help() const
{
    vector<string> aids;
    aids.push_back("Watch your step.");
    aids.push_back("Why would you need matches?");
    aids.push_back("It looks dark down there.");
    cout << aids[rand()%aids.size()] << endl;
}

Hole::Hole()
    : Location("hole","in a deep dark damp hole.  A skeleton lies on the ground.  You can see a low tunnel on the far side of the hole.",true)
{
    contents.push("fly");
    contents.push("bear");
}

void Hole::help() const
{
    vector<string> aids;

    aids.push_back("It sure is dark in here.");
    aids.push_back("Watch out for the bear.");
    aids.push_back("That fly is flying pretty fast.");
    aids.push_back("Bears get hungry, too.");
    aids.push_back("Try not to bump your head.");
    cout << aids[rand()%aids.size()] << endl;
}

Tunnel::Tunnel()
    : Location("tunnel","in a low narrow tunnel. In the middle of the tunnel, a spider web hangs from the ceiling.  Beyond the web is an opening into a larger area.",true)
{
    contents.push("spider");
    contents.push("rat");
}

void Tunnel::help() const
{
    vector<string> aids;

    aids.push_back("Keep low.");
    aids.push_back("You don't always need a bullet.");
    aids.push_back("That cheese did look really tasty.");
    cout << aids[rand()%aids.size()] << endl;
}

Chamber::Chamber()
    : Location("chamber","in a large open chamber. There is water dripping from the ceiling.  A deep shaft descends from the center of the chamber.  A thin, but strong, stalagmite rises toward the ceiling next to the shaft.",true)
{
    contents.push("stalactite");
    contents.push("minotaur");
    contents.push("coin");
}

void Chamber::help() const
{
    vector<string> aids;
    aids.push_back("It's going to take a lot to bring the minotaur down.");
    aids.push_back("It's important to know the difference between a stalactite and a stalagmite.");
    cout << aids[rand()%aids.size()] << endl;
}
Shaft::Shaft()
    : Location("shaft","in a narrow vertical shaft. The shaft descends to the darkness below.  Cobwebs prevent you from seeing the bottom of the shaft.",true)
{
    contents.push("serpent");
    contents.push("bat");
}

void Shaft::help() const
{
    vector<string> aids;
    aids.push_back("The serpent has an attitude.");
    aids.push_back("Did you know that bats eat spiders?");
    cout << aids[rand()%aids.size()] << endl;
}

Room::Room()
    : Location("room","in a small dusty room full of cobwebs.  You can see the rope hanging from the shaft.  There is a treasure chest sitting on the floor in the center of the room.",true)
{
    contents.push("ghost");
}

void Room::help() const
{
    vector<string> aids;
    aids.push_back("You can't kill a ghost.");
    aids.push_back( "And now for the key.");
    cout << aids[rand()%aids.size()] << endl;
}
