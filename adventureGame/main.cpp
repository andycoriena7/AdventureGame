#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#include "world.h"
#include "thing.h"
#include "location.h"
#include "human.h"
#include "proto.h"

int main()
{
    srand(static_cast<unsigned>(time(0)));
    string command;
    intro();

    bool alive;
    Human* you = 0;

    World TheWorld(you);

    int life = 9;

    while (life)
    {
        alive = true;
        TheWorld.clear();
        TheWorld.create();
        if (you) delete you;
        you = new Human(TheWorld);

        cout << endl << "Press Enter to continue" << endl << endl;
        while (cin.get() != '\n') ;
        you->moveTo("meadow");

        while (alive)
        {
            alive = you->processCommand();
        }
        life--;

        if (!alive)
        {
            switch (life)
            {
            case 8:
                cout << endl << "It's a good thing that you had 9 lives." << endl;
                break;
            case 7:
                cout << endl << "That's 2 down, 7 to go!" << endl;
                break;
            case 4:
                cout << endl << "I hope you are learning something." << endl;
                break;
            case 1:
                cout << endl << "You have one life to live.  Use it wisely." << endl;
                break;
            }
        }
        cout << endl;
    }
}

void intro()
{
    string temp;
    cout << "Welcome to Joe's first adventure (Version 1.1)" << endl << endl;
    cout << "To play this game you must enter one or two-word commands, such as:" << endl;
    cout << "   \"go tree\" or \"get rock\" or \"climb down\" or \"help\" or \"quit\"." << endl;
    cout << "\nYou can get a list of verbs to use by entering the command, \"verbs\"" << endl;
    cout << "You can identify your current location by entering the command, \"location\"" << endl;
    cout << "You can list your current possessions by entering the command, \"inventory\"" << endl;
    cout << "\nYou can ask for help at any location.  You may want to ask for help more" << endl
         << "than once, since help is minimal and random." << endl;
    cout << "\nThe goal of the game is to find the hidden treasure." << endl;
    cout << "You will have nine lives in this game.  Use them wisely." << endl;
    cout << "Use your imagination!!!" << endl << endl;
}

string secondWordOfCommand(const string& command)
{
    istringstream sin(command);
    string secondWord;
    sin >> secondWord;
    sin >> secondWord;
    return secondWord;
}

void clearscreen()
{
#ifdef __MINGW32__
    system("cls");
#else
    system("clear");
#endif
}

void delay(int secs)
{
    for (long i=0; i<60000000*secs; i++ ) ;
}

void changeDescriptionOfLocation(World& world, const string& location,
                                 const string& newDescription)
{
    for (size_t i = 0; i < world.size(); i++)
    {
        if (world[i]->get_id() == location)
        {
            world[i]->set_description(newDescription);
        }
    }
}

void print_verbs()
{
    vector<string> verbs;
    verbs.push_back("quit");
    verbs.push_back("exit");
    verbs.push_back("inventory");
    verbs.push_back("location");
    verbs.push_back("go");
    verbs.push_back("get");
    verbs.push_back("drop");
    verbs.push_back("verbs");
    verbs.push_back("climb");
    verbs.push_back("raise");
    verbs.push_back("lift");
    verbs.push_back("lean");
    verbs.push_back("tilt");
    verbs.push_back("prop");
    verbs.push_back("fix");
    verbs.push_back("ride");
    verbs.push_back("untie");
    verbs.push_back("scrape");
    verbs.push_back("shoot");
    verbs.push_back("kill");
    verbs.push_back("remove");
    verbs.push_back("help");
    verbs.push_back("return");
    verbs.push_back("light");
    verbs.push_back("feed");
    verbs.push_back("swat");
    verbs.push_back("squat");
    verbs.push_back("duck");
    verbs.push_back("stab");
    verbs.push_back("eat");
    verbs.push_back("unlock");
    verbs.push_back("bribe");
    verbs.push_back("open");

    sort(verbs.begin(),verbs.end());
    cout << left;
    for (size_t i = 0; i < verbs.size(); i++)
    {
        cout << setw(12) << verbs[i];
        if (i%5==4) cout << endl;
    }
    cout << endl;
}

void win()
{
    for (int i = 0; i < 10; i++)
    {
        cout << "\n\aYOU DID IT!  YOU'VE GOT THE TREASURE.  YOU'LL NOW BE RICH AND FAMOUS" << endl;
        delay(10);
    }
    exit(EXIT_SUCCESS);
}
