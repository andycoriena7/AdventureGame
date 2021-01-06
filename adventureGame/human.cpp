#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

#include "thing.h"
#include "animal.h"
#include "human.h"
#include "location.h"
#include "proto.h"
#include "listofthings.h"

Human::Human(World& theWorld)
    : location(0), inventory(), commandCount(0), world(theWorld)
{}


bool Human::hasA(const string& item) const
{
    return inventory.find(item) != 0;
}

bool Human::hasA_LitLantern() const
{
    Lantern* ptr2Lantern = dynamic_cast<Lantern*>(getPtr2ThingInInventory("lantern"));
    if (ptr2Lantern && ptr2Lantern->isLit()) return true;
    return false;
}

bool Human::hasA_LoadedGun() const
{
    Gun* ptr2Gun = dynamic_cast<Gun*>(getPtr2ThingInInventory("gun"));
    if (ptr2Gun && ptr2Gun->howManyBullets()) return true;
    return false;
}

void Human::miscEvents()
{
    if (hasA_LitLantern())
    {
        Lantern* ptr2Lantern = dynamic_cast<Lantern*>(getPtr2ThingInInventory("lantern"));
        int randy = rand() % 21;
        switch (randy)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            cout << "\nYou feel a slight breeze, the flame in the lantern flickers." << endl;
            break;
        case 5:
            cout << "\nYou feel the slight breeze again." << endl;
            ptr2Lantern->unlight();
            delay(40);
            location->describe(false);
            break;
        case 7:
            cout << "\nYou hear a distant scream." << endl;
            break;
        case 9:
            cout << "\nYou hear some snoring." << endl;
            break;
        case 11:
            if (hasA_LitLantern())
            {
                cout << "\nYou tripped on a tree root and dropped the lantern." << endl;
                ptr2Lantern->unlight();
                delay(40);
                location->describe(false);
                location->get_contents().get(inventory,"lantern");
            }
            break;
        default:
            ;
        }
    }
}

void Human::lightMatch()
{
    Matches* ptr2Matches = dynamic_cast<Matches*>(getPtr2ThingInInventory("matches"));
    if (hasA("matches"))
    {
        if (hasA_LitLantern())
        {
            ptr2Matches->lightMatch();
            cout << "\nWhy would you light a match when the lantern is on?  You just wasted a match." << endl;
            return;
        }
        else if (ptr2Matches->lightMatch())
        {
            cout << "\nThe match flashes for 5 seconds and you can see ..." << endl;
            cout << "You can also see" << endl;
            location->print_contents();
            delay(15);
            clearscreen();
            location->print_description(false);
        }
        else
        {
            cout << "\nYour book of matches is empty" << endl;
        }
    }
}

void Human::lightMatches()
{
    if (hasA("matches"))
    {
        Matches* ptr2Matches = dynamic_cast<Matches*>(getPtr2ThingInInventory("matches"));

        if (ptr2Matches->get_count())
        {
            cout << "\nYou idiot!  You just lit the whole book of matches" << endl;
            cout << "\nThe match flashes for 10 seconds and you can see ..." << endl;
            cout << "\na low narrow tunnel. In the middle if the tunnel, a spider web hangs from the ceiling.  Beyond the web is an opening into a larger area." << endl;

            cout << "\nYou can also see" << endl;
            location->print_contents();
            delay(30);
            ptr2Matches->lightBook();
            clearscreen();
            location->print_description(false);
        }
        else
        {
            cout << "Your book of matches is empty" << endl;
        }
    }
}

void Human::lightLantern()
{

    if (!hasA("matches"))
    {
        cout << "\nYou can light your lantern without a match." << endl;
        return;
    }
    if (!hasA("lantern"))
    {
        cout << "\nYou don't have a lantern." << endl;
        return;
    }
    delay(7);
    cout << endl;
    Matches* ptr2Matches = dynamic_cast<Matches*>(getPtr2ThingInInventory("matches"));

    ptr2Matches->lightMatch();
    cout << endl;
    delay(7);
    Lantern* ptr2Lantern = dynamic_cast<Lantern*>(getPtr2ThingInInventory("lantern"));
    ptr2Lantern->light();
    cout << endl;
    location->describe(true);
}

Thing* Human::getPtr2ThingInLocation(const string& thing)
{
    return location->get_contents().find(thing);
}

Thing* Human::getPtr2ThingInInventory(const string& thing) const
{
    return inventory.find(thing);
}

void Human::moveTo(const string& newLocation, bool lightIsOn)
{
    // look for the win
    if (newLocation == "meadow" && hasA("statue"))
    {
        win();
    }

    location = world.getLocation(newLocation);

    clearscreen();

    location->describe(lightIsOn);
}

string Human::getCommand() const
{
    string command;
    cout << Prompt;
    getline(cin,command);
    for (size_t i=0; i<command.size(); i++)
        command[i] = tolower(command[i]);
    return command;
}

bool Human::processCommand()
{
    bool alive = true;
//   commandCount++;

    string command = getCommand();
    if (command == "quit" || command == "exit")
    {
        cout << endl << "Ok.  Bye bye." << endl << endl;
        exit(1);
    }
    else if (command == "help")
    {
        location->help();
    }
    else if (command == "inventory" || command == "inv")
    {
        print_inventory();
    }
    else if (command == "location" || command == "loc")
    {
        clearscreen();
        location->describe();
    }
    else if (command == "verbs")
    {
        print_verbs();
    }

    else if (location->get_id()=="meadow") alive = processMeadow(command);
    else if (location->get_id()=="lake") alive = processLake(command);
    else if (location->get_id()=="tree") alive = processTree(command);
    else if (location->get_id()=="treetop") alive = processTreetop(command);
    else if (location->get_id()=="boulder") alive = processBoulder(command);
    else if (location->get_id()=="hole") alive = processHole(command);
    else if (location->get_id()=="tunnel") alive = processTunnel(command);
    else if (location->get_id()=="chamber") alive = processChamber(command);
    else if (location->get_id()=="shaft") alive = processShaft(command);
    else if (location->get_id()=="room") alive = processRoom(command);
    return alive;
}

bool Human::getThing(const string& item)
{
    if (hasA(item))
    {
        cout << "You already have this" << endl;
        return false;
    }

    Thing* ptr2Item = location->get_contents().find(item);
    
    if (ptr2Item != 0)
    {
        int itemWeight = ptr2Item->get_weight();
        if (getInventoryWeight()+itemWeight > MaxCarryWeight)
        {
            cout << "You are carrying too much to get that item" << endl;
            return false;
        }
        inventory.get(location->get_contents(),item);
        // location->get_contents().remove(item);
        cout << "Got it" << endl;
        return true;
    }
    else cout << "I don't know how to get that." << endl;
    return false;
}

bool Human::dropThing(const string& item)
{
    if (!hasA(item))
    {
        cout << "You don't have a " << item << endl;
        return false;
    }

    location->get_contents().get(inventory,item);

    cout << "Dropped it"<< endl;
    return true;
}

int Human::getInventoryWeight() const
{
    return inventory.get_weight();
}

bool Human::feed(const string& animal)
{
    Animal* ptr2Animal = dynamic_cast<Animal*>(location->get_contents().find(animal));
    if (!ptr2Animal)
    {
        cout << "\nThere is no " << animal << "here." << endl;
        return false;
    }
    else
    {
        string animalDiet = ptr2Animal->eats();
        Thing* ptr2Food = inventory.find(animalDiet);
        if (!ptr2Food)
        {
            cout << "\nYou don't have any " << animalDiet << " to feed the " << animal << endl;
            return false;
        }
        inventory.remove(animalDiet);
        ptr2Animal->setHunger(false);
    }
    return true;
}

bool Human::shoot(const string& animal)
{
    if (hasA("gun"))
    {
        Gun* ptr2Gun = dynamic_cast<Gun*>(inventory.find("gun"));
        if (ptr2Gun->shoot())
        {
            Animal* ptr2Animal = dynamic_cast<Animal*>(location->get_contents().find(animal));

            if (ptr2Animal)
            {
                ptr2Animal->kill();
                cout << "Good shot!  The " << animal << " is dead."  << endl;
            }
            else
            {
                cout << "You just wasted a bullet, there is no " << animal << " here." << endl;
                return false;
            }
        }
    }
    else
    {
        cout << "You can't shoot without a gun"<< endl;
        return false;
    }
    return true;
}

void Human::print_inventory() const
{
    if (inventory.get_top())
    {
        cout << "You are carrying" << endl;
        inventory.print();
    }

    else cout << "You are not carrying anything."  << endl;
}

bool Human::processMeadow(const string& command)
{
    static bool ladderInPlace = false;
    bool alive = true;
    static bool toolkit = false;

    if (command == "go tree" || command == "climb tree")
    {
        if (ladderInPlace)
        {
            moveTo("tree");
        }
        else
        {
            cout << "You can't do that at this time" << endl;
        }
    }
    else if (command == "raise ladder" || command == "lift ladder" || command == "prop ladder" || command == "lean ladder" || command == "tilt ladder" || command == "lean lad" || command == "ll")
    {
        if (hasA("ladder"))
        {
            location->get_contents().get(inventory,"ladder");
            cout << "The ladder is now leaning against the tree." << endl;

            ladderInPlace = true;
        }
    }
    else if (command == "cut cheese")
    {
        cout << "\nThat's gross!!! You just killed yourself and everybody around youZ" << endl;
        alive = false;
    }
    else if (command == "eat cheese")
    {
        if (hasA("cheese"))
        {
            inventory.remove("cheese");
            cout << "Wow!  That's really good cheese.  I hope you don't need it later!" << endl;
        }
        else
        {
            cout << "\nYou should get the cheese first" << endl;
        }
    }
    else if(command == "open toolkit")
    {
        toolkit = true;
        cout <<"Inside is a crowbar." << endl;
        if( command == "get crowbar")
        {
            inventory.push("crowbar");
        }
    }
    
    else if (command == "get crowbar")
    {
        if(toolkit)
        {
            inventory.push("crowbar");
            cout << "got it" << endl;
        }
        else
            cout <<"I don't know how to get that." << endl;
    }
    
   else if (command.substr(0,4) == "get " && command != "get crowbar")
    {
        string what = secondWordOfCommand(command);
        if (what == "lad") what = "ladder";
        else if (what == "lan") what = "lantern";
        else if (what == "che") what = "cheese";
        else if (what == "kni") what = "knife";
       // else if (what == "cro") what = "crowbar";
        getThing(what);
    }
 
    else if (command.substr(0,5) == "drop ")
    {
        string what = secondWordOfCommand(command);
        dropThing(what);
    }
    else if (command == "fix bike")
    {
        Bike* ptr2Bike = dynamic_cast<Bike*>(inventory.find("bike"));
        if(hasA("bike") && ptr2Bike->isBroken())
        {
            if (hasA("toolkit"))
            {
                ptr2Bike ->fix();
            }
            else
            {
                cout << "You can't fix the bike without any tools" << endl;
            }
        }
    }

    else if (command == "ride bike")
    {
        if (hasA("bike"))
        {
            Bike* ptr2Bike = dynamic_cast<Bike*>(inventory.find("bike"));
            if(ptr2Bike->isBroken())
            {
                cout << "You can't ride a broken bike." << endl;
            }
            else
            {
                ptr2Bike->ride();
                alive = false;
            }
        }
        else
        {
            cout << "You don't have a bike." << endl;
        }
    }

    else if (command == "go lake")
    {
        Matches* ptr2Matches = dynamic_cast<Matches*>(getPtr2ThingInInventory("matches"));
        if (ptr2Matches)
        {
            delay(10);
            ptr2Matches->getWet();
        }
        moveTo("lake");
    }
    else if (command == "go crevice")
    {
        cout << "Oh no!  You fell into a deep crevice and died.  Too bad, you lose." << endl;
        alive = false;
    }
    else if (command.substr(0,5) == "go bo")
    {
        moveTo("boulder");
    }
    else if (command == "go fence" || command == "go gate")
    {
        cout << "There's nothing there.  You're wasting your time." << endl;
    }
    else if (command == "go swing" || command == "go tire")
    {
        cout << "You really don't have time for that." << endl;
    }

    else cout << "Huh?" << endl;

    return alive;
}

bool Human::processTree(const string& command)
{
    bool alive = true;

    if (command == "go down" || command == "climb down" || command == "go meadow"  || command == "go mea")
    {
        moveTo("meadow");
    }
    else if (command == "go up" || command == "climb higher" || command == "go higher" || command == "climb up" )
    {
        moveTo("treetop");
    }
    else if (command.substr(0,4) == "get ")
    {
        string what = secondWordOfCommand(command);
        if (what == "lan") what = "lantern";
        getThing(what);
    }
    else if (command.substr(0,5) == "drop ")
    {
        string what = secondWordOfCommand(command);
        dropThing(what);
    }

    else cout << "Huh?" << endl;

    return alive;
}

bool Human::processBoulder(const string& command)
{
    static bool ladderInPlace = false;
    if (command.substr(0,5) == "go me" || command == "return")
    {
        moveTo("meadow");
    }
    else if (command == "go hole" || command == "go down" || command == "go ladder")
    {
        if (ladderInPlace)
        {
            moveTo("hole",hasA_LitLantern());
        }
        else
        {
            cout << endl << "\nOh no!!!  You fell into the deep dark hole and died.  Too bad.  You could use that ladder." << endl;
            return false;
        }
    }
    else if (command.substr(0,4) == "get ")
    {
        string what = secondWordOfCommand(command);
        if (what == "mat") what = "matches";
        getThing(what);
    }
    else if (command == "drop ladder" || command == "place ladder" || command == "drop lad")
    {
         if (hasA("ladder")){
        ladderInPlace = true;
        dropThing("ladder");
        cout << "\nThe ladder is in the hole leading down." << endl;
        changeDescriptionOfLocation(world, "boulder","behind the large boulder, standing next to a dark hole in the ground.  A ladder is coming out of the hole in the ground.");
        changeDescriptionOfLocation(world, "hole","in a deep dark damp hole.  A skeleton lies on the ground.  You can see a low tunnel on one side of the hole and a ladder rising up on the other side.");
         }
         else
         {
             cout << "You don't have a ladder."  << endl;
         }
    }
    else if (command.substr(0,5) == "drop ")
    {
        string what = secondWordOfCommand(command);
        dropThing(what);
    }

    else cout << "Huh?" << endl;

    return true;
}

bool Human::processTreetop(const string& command)
{
    if (command == "go down" || command == "climb down")
    {
        moveTo("tree");
        return true;
    }
    else if (command == "get rope")
    {
        cout << "\nYou can't get the rope.  There is a knot holding the rope to a limb." << endl;
        return true;
    }
    else if (command == "untie rope" || command == "untie knot" || command == "untie swing") {
        if (getThing("rope")) {
            Rope* ptr2Rope = dynamic_cast<Rope*> (getPtr2ThingInInventory("rope"));
            ptr2Rope->unTie();
            cout << "\nOk, you've got the rope.  The tire falls down and rolls into the crevice." << endl;
            changeDescriptionOfLocation(world, "meadow", "in a meadow next to a lake.  There is a large oak tree, a crevice in the ground, a large boulder, and an old fence with a broken gate.  Next to the boulder is a sign that reads \'Beware of falling rocks\'.");
            changeDescriptionOfLocation(world, "tree", "in a large oak tree.  You could go back down || you could go higher.  The branches don't look very safe and there is an ill wind blowing.");
        }
        return true;
    }

    else if (command.substr(0,5) == "drop ")
    {
        string what = secondWordOfCommand(command);
        dropThing(what);
        return true;
    }

    else cout << "Huh?" << endl;

    return true;
}

bool Human::processLake(const string& command)
{
    static bool leechPresent = true;
    static bool leechNotification = false;
    Eel* ptr2Eel = dynamic_cast<Eel*>(getPtr2ThingInLocation("eel"));
    Fish* ptr2Fish = dynamic_cast<Fish*>(getPtr2ThingInLocation("fish"));

    int areYouLucky = rand() % 101;

    if (areYouLucky % 19 == 0 && leechPresent && leechNotification)
    {
        cout << "\nToo bad - you just bled to death.  Better luck next time.\n" << endl;
		leechNotification = false;
        return false;
    }
    if (areYouLucky % 17 == 0 && !leechNotification && leechPresent)
    {
        cout << "\nOh no!  There is a blood sucking leech attached to your leg." << endl;
        cout << "You have 60 seconds to remove it, || you will bleed to death.\n" << endl;
        leechNotification = true;
    }
    if (areYouLucky % 23 == 0 && getPtr2ThingInLocation("fish"))
    {
        cout << "\nOh no!  That fish is a piranha && just ate your left leg.  You are now dead." << endl;
        return false;
    }
    if (areYouLucky % 53 == 0 && getPtr2ThingInLocation("eel"))
    {
        cout << "\nOh no!  That eel is a killer and ate your right leg.  You are now dead." << endl;
        return false;
    }

    if (command.substr(0,6) == "go mea" || command == "go shore")
    {
		if (leechNotification)
		{
			leechNotification = false;
			if (areYouLucky % 2 == 0) {
				cout << "\nThat leech is still stuck to your leg.  Did you think it would just go away by itself?\n"
					<< "You don't know leeches!  Oh!  And, you're dead now." << endl;
				return false;
			}
			else
			{
				cout << "Are you lucky or what?  Remember that leech on your leg?  It just fell off by itself." << endl;
			}
		}
        moveTo("meadow");
        return true;
    }
    else if (command.substr(0,4) == "get ")
    {
        string what = secondWordOfCommand(command);
        getThing(what);
        if (ptr2Eel && ptr2Eel->isAlive()&& (!ptr2Eel->isHungry()) && what == "eel")
        {
            cout << "\nYou idiot!!!  That eel is a killer and you were just eaten.  You're dead!" << endl;
            return false;
        }
        if (ptr2Fish && ptr2Fish->isAlive() && !ptr2Fish->isHungry() && what == "fish")
        {
            cout << "\nYou idiot!!!  That fish is a piranha and you were just eaten.  You're dead!" << endl;
            return false;
        }
        return true;
    }
    else if (command.substr(0,5) == "drop ")
    {
        string what = secondWordOfCommand(command);
        dropThing(what);
        return true;
    }
    else if (command == "feed fish")
    {
        if (feed("fish"))
        {
            ptr2Fish->changeDescription("A happy and not-so-skinny fish.");
            cout << "\nThe fish ate the dead eel.  It is now happy and not-so-skinny." << endl;
        }
    }
    else if (command == "feed eel")
    {
        if (feed("eel"))
        {
            ptr2Fish->changeDescription("A happy eel.");
            cout << "\nThe eel ate the dead fish.  It is now happy." << endl;
        }
    }
    else if (command == "shoot fish" || command == "kill fish")
    {
        shoot("fish");
        return true;
    }
    else if (command == "shoot eel" || command == "kill eel")
    {
        if (shoot("eel"))
        {
            // If the fish is alive, it will eat the dead eel
            Fish* ptr2Fish = dynamic_cast<Fish*>(getPtr2ThingInLocation("fish"));
            if (ptr2Fish && ptr2Fish->isAlive())
            {
                location->get_contents().remove("eel");
                cout << "Wow!  The fish just ate the dead eel" << endl;
            }
        }
        return true;
    }

    else if ((command == "scrape leech" || command == "remove leech") && hasA("knife"))
    {
        cout << "Wow!  That was a close call" << endl;
        leechPresent = false;
    }
    else cout << "Huh?" << endl;

    return true;
}

bool Human::processHole(const string& command)
{
    Gun* ptr2Gun = dynamic_cast<Gun*>(getPtr2ThingInInventory("gun"));
    Bear* ptr2Bear = dynamic_cast<Bear*>(getPtr2ThingInLocation("bear"));
    Fly* ptr2Fly = dynamic_cast<Fly*>(getPtr2ThingInLocation("fly"));

    static bool isLow = false;
    static int timeInHole = 0;
    timeInHole++;

    if (timeInHole > 10 && ptr2Bear && ptr2Bear->isAlive() && ptr2Bear->isHungry())
    {
        cout << "Oh no!  You were just eaten by the mean hungry bear.  You should have dealt with that bear before now.\nYou're dead." << endl;
        return false;
    }

    if (command == "go up" || command == "climb up" || command == "climb ladder" || command== "go boulder")
    {
        moveTo("boulder");
        return true;
    }

    else if (command.substr(0,5) == "drop ")
    {
        string what = secondWordOfCommand(command);
        dropThing(what);
        return true;
    }

    else if (command == "light match")
    {
        lightMatch();
        return true;
    }

    else if (command == "light matches")
    {
        lightMatches();
        return true;
    }

    else if (command.substr(0,9) == "light lan" || command == "ll")
    {
        lightLantern();
    }
    else if (command == "get bear")
    {
        if (ptr2Bear && ptr2Bear->isAlive())
        {
            cout << "\nYou stupid!  The bear is no longer hungry, but you are dead" << endl;
            return false;
        }
        else
        {
            getThing("bear");
        }
    }
    else if (command == "get fly" || command == "kill fly")
    {
        if (ptr2Fly && ptr2Fly->isAlive())
        {
            cout << "\nYou can't do that.  The fly is too fast for you." << endl;
        }
        else
        {
            getThing("fly");
        }
    }
    else if (command == "feed bear")
    {
        if (feed("bear"))
        {
            ptr2Bear->changeDescription("A nice friendly bear.");
            cout << "\nThe bear ate the dead eel.  It is now a nice friendly bear." << endl;
        }
    }

    else if (command == "shoot fly")
    {
        if (!ptr2Gun)
        {
            cout << "\nYou can't shoot the fly without a gun." << endl;
        }
        if (ptr2Gun->noBullets())
        {
            cout << "\nYour gun is empty." << endl;
        }
        ptr2Gun->shoot();
        cout << "\nYou missed." << endl;
    }
    else if (command == "swat fly")
    {
        Fly* ptr2Fly = dynamic_cast<Fly*>(location->get_contents().find("fly"));

        if (ptr2Fly)
        {
            ptr2Fly->kill();
            cout << "\nGood aim!  That fly is dead."  << endl;
        }
        else
        {
            cout << "\nWhat fly?" << endl;
        }
    }
    else if (command == "shoot bear")
    {
        if (!ptr2Gun)
        {
            cout << "\nYou can't shoot the bear without a gun." << endl;
        }
        else if (ptr2Gun->noBullets())
        {
            cout << "\nYour gun is empty." << endl;
        }
        else
        {
            static bool firstShot = true;
            ptr2Gun->shoot();
            if (firstShot)
            {
                cout << "\nYou wounded the bear and just made it madder than ever. It growls loudly." << endl;
                firstShot = false;
            }
            else
            {
                if (ptr2Bear)
                {
                    ptr2Bear->kill();
                    cout << "\nYou got em that time!  The bear is dead."  << endl;
                }
            }
        }
    }
    else if (command == "stab bear")
    {
        Knife* ptr2Knife = dynamic_cast<Knife*>(getPtr2ThingInInventory("knife"));
        if (!ptr2Knife)
        {
            cout << "\nYou can't stab the bear without a knife." << endl;
        }
        else
        {
            ptr2Bear->kill();
            cout << "\nYou stabbed the bear.  He's dead."  << endl;
        }
    }

    else if (command.substr(0,4) == "get ")
    {
        string what = secondWordOfCommand(command);
        getThing(what);
        return true;
    }
    else if (command.substr(0,6) == "go tun")
    {
        if (ptr2Bear && ptr2Bear->isAlive() && ptr2Bear->isHungry())
        {
            cout << "\nThe bear will not let you pass."  << endl;
        }
        else
        {
            if (isLow)
            {
                // If the bear is not dead, wake him up
                if (ptr2Bear && ptr2Bear->isAlive())
                {
                    ptr2Bear->setHunger(true);
                    ptr2Bear->changeDescription("a very hungry and very mean bear");
                }
                changeDescriptionOfLocation(world, "tunnel","in a low narrow tunnel. In the middle if the tunnel, a spider web hangs from the ceiling.  At one end, there is an opening into a larger area.  At the other is a hole with a ladder in it.");
                moveTo("tunnel",hasA_LitLantern());
                return true;
            }
            else
            {
                cout << "\nYou bumped your head on the entrance to the tunnel." << endl;
                delay(10);
                cout << "\nYour head starts to bleed." << endl;
                delay(10);
                cout << "\nYou died." << endl;
                return false;
            }
        }
    }
    else if (command.substr(0,5) == "squat" || command.substr(0,4) == "duck")
    {
        isLow = true;
        cout << "\nOk, now you're \"low down\"." << endl;
    }

    else cout << "Huh?" << endl;

    miscEvents();
    return true;
}

bool Human::processTunnel(const string& command)
{
    Spider* ptr2Spider = dynamic_cast<Spider*>(getPtr2ThingInLocation("spider"));
    Rat* ptr2Rat = dynamic_cast<Rat*>(getPtr2ThingInLocation("rat"));
    Gun* ptr2Gun = dynamic_cast<Gun*>(getPtr2ThingInInventory("gun"));

    static int timeInTunnel = 0;
    timeInTunnel++;

    if (timeInTunnel > 7 && ptr2Spider && ptr2Spider->isHungry())
    {
        cout << "\nOh no!  You were just eaten by the black widow spider." << endl;
        delay(5);
        cout << "\nYou're starting to feel weak ..." << endl;
        delay(5);
        cout << "\nYou're feeling weaker ..." << endl;
        delay(5);
        cout << "\nYou're dead!" << endl;
        return false;
    }

    if (command == "go back" || command == "go hole" || command == "return")
    {
        moveTo("hole",hasA_LitLantern());
        return true;
    }
    if (command == "go opening")
    {
        if (ptr2Spider && ptr2Spider->isHungry() && ptr2Spider->isAlive())
        {
            cout << "\nThe spider will not let you pass." << endl;
        }
        else if (ptr2Rat && ptr2Rat->isHungry() && ptr2Rat->isAlive())
        {
            cout << "\nThe rat will not let you pass." << endl;
        }
        else moveTo("chamber",hasA_LitLantern());
        return true;
    }

    else if (command.substr(0,5) == "drop ")
    {
        string what = secondWordOfCommand(command);
        dropThing(what);
        return true;
    }

    else if (command == "light match")
    {
        lightMatch();
        return true;
    }

    else if (command == "light matches")
    {
        lightMatches();
        return true;
    }

    else if (command.substr(0,9) == "light lan")
    {
        lightLantern();
        return true;
    }

    else if (command == "shoot spider")
    {
        if (!ptr2Spider)
        {
            cout << "\nThere is no spider." << endl;
        }
        else if (!ptr2Gun)
        {
            cout << "\nYou can't shoot the spider without a gun." << endl;
        }
        else if (ptr2Gun->noBullets())
        {
            cout << "\nYour gun is empty." << endl;
        }
        else if (ptr2Gun && ptr2Spider && !(ptr2Spider->isAlive()))
        {
            cout << "\nWhy would you shoot a dead spider?" << endl;
            if (ptr2Gun->shoot()) cout << "\nYou just wasted a bullet." << endl;
            return true;
        }
        else if (ptr2Gun && ptr2Spider && !(ptr2Spider->isHungry()))
        {
            cout << "\nWhy would you shoot a happy, well-fed spider?" << endl;
            if (ptr2Gun->shoot()) cout << "\nYou just wasted a bullet." << endl;
            return true;
        }
        else
        {
            static bool firstShot = true;
            ptr2Gun->shoot();
            if (firstShot)
            {
                cout << "\nYou missed the spider.  It runs too fast." << endl;
                firstShot = false;
            }
            else
            {
                ptr2Spider->kill();
                cout << "\nYou got em that time!  The spider is dead."  << endl;
            }
        }
    }
    else if (command == "get spider")
    {
        if (ptr2Spider)
        {
            if (ptr2Spider->isAlive() && ptr2Spider->isHungry())
            {
                cout << "\nAre you nuts???  That spider is a black widow, and hungry, I might add." << endl;
                cout << "\nYou're dead.  Next time bring your brain." << endl;
                return false;
            }
            getThing("spider");
        }
    }
    else if (command == "feed spider")
    {
        if (feed("spider"))
        {
            ptr2Spider->changeDescription("A happy black widow spider.");
            cout << "\nThe spider ate the fly.  It is happy now." << endl;
        }
    }

    else if (command == "get rat")
    {
        if (ptr2Rat)
        {
            if (ptr2Rat->isAlive() && ptr2Rat->isHungry())
            {
                cout << "\nAre you crazy?  Didn't you see those teeth?" << endl;
                cout << "\nYou're dead.  Next time bring your brain and some cheese." << endl;
                return false;
            }
            getThing("rat");
        }
    }
    else if (command == "feed rat")
    {
        if (feed("rat"))
        {
            ptr2Rat->changeDescription("A sleeping rat with sharp teeth and bad breath.");
            cout << "\nThe rat ate the cheese.  It went to sleep." << endl;
        }
    }
    else if (command == "shoot rat")
    {
        if (!ptr2Rat)
        {
            cout << "\nThere is no rat." << endl;
        }
        if (!ptr2Gun)
        {
            cout << "\nYou can't shoot the rat without a gun." << endl;
        }
        else if (ptr2Gun && ptr2Rat && !(ptr2Rat->isAlive()))
        {
            cout << "\nWhy would you shoot a dead rat?" << endl;
            if (ptr2Gun->shoot()) cout << "\nYou just wasted a bullet." << endl;
            return true;
        }
        else if (ptr2Gun->noBullets())
        {
            cout << "\nYour gun is empty." << endl;
        }
        else
        {
            static bool firstShot = true;
            ptr2Gun->shoot();
            if (firstShot)
            {
                cout << "\nYou missed the rat.  It runs too fast." << endl;
                firstShot = false;
            }
            else
            {
                ptr2Rat->kill();
                cout << "\nYou got em that time!  The rat is dead."  << endl;
            }
        }
    }
    else if (command.substr(0,4) == "get ")
    {
        string what = secondWordOfCommand(command);
        if (what == "lan") what = "lantern";
        getThing(what);
    }
    else cout << "Huh?" << endl;

    miscEvents();

    return true;
}

bool Human::processChamber(const string& command)
{
    static int timeInChamber = 0;
    timeInChamber++;
    static bool ropeInPlace = false;
    Stalactite* ptr2Stalactite = dynamic_cast<Stalactite*>(getPtr2ThingInLocation("stalactite"));
    Minotaur* ptr2Minotaur = dynamic_cast<Minotaur*>(getPtr2ThingInLocation("minotaur"));
    Gun* ptr2Gun = dynamic_cast<Gun*>(getPtr2ThingInInventory("gun"));
    bool alive = true;

    if (command == "go back" || command == "go tunnel" || command == "return")
    {
        moveTo("tunnel",hasA_LitLantern());
    }

    else if (command.substr(0,5) == "drop ")
    {
        string what = secondWordOfCommand(command);
        if (what == "sc") what = "stalactite";
        dropThing(what);
    }

    else if (command == "light match")
    {
        lightMatch();
    }

    else if (command == "light matches")
    {
        lightMatches();
    }

    else if (command.substr(0,9) == "light lan" || command == "ll")
    {
        lightLantern();
    }

    else if (command.substr(0,12) == "break stalac" || command == "break sc")
    {
        cout <<" \n with what?" << endl;
        string buffer;
        getline (cin, buffer);
        if(buffer.find("crowbar") != string::npos)
        {
            if(!hasA("crowbar")) cout <<"You dont have a crowbar" << endl;
            else
            {
                location->get_contents().get(inventory, "crowbar");
                ptr2Stalactite->breakit();
            }
        }
        else
            cout <<"You can't do that" << endl;
    }
    else if (command.substr(0,10) == "get stalac" || command == "get sc")
    {
        if (!ptr2Stalactite->isBroken())
        {
            cout << "\nYou can't get the stalactite yet.  It is hanging from the ceiling." << endl;
        }
        else if (hasA("stalactite"))
        {
            cout << "\nYou already have the stalactite." << endl;
        }
        else getThing("stalactite");
    }
    else if (command == "tie rope")
    {
        if (!hasA("rope")) cout << "You don't have a rope." << endl;
        else
        {
            cout << "\nTie it to what?" << endl;
            string buffer;
            getline(cin,buffer);
            if (buffer.find("stalagmite") != string::npos)
            {
                location->get_contents().get(inventory,"rope");
                Rope* ptr2Rope = dynamic_cast<Rope*>(getPtr2ThingInLocation("rope"));
                ptr2Rope->changeDescription("a rope tied to the stalagmite and dropping into the shaft");
                cout << "\nOk, the rope is tied to the stalagmite and drops into the shaft." << endl;
                ropeInPlace = true;
            }
            else
            {
                cout << "\nThat's not going to work." << endl;
            }
        }
    }
    else if (command == "kill minotaur")
    {
        cout << "\nHow?" << endl;
    }
    else if (command == "stab minotaur")
    {
        if (!ptr2Minotaur)
        {
            cout << "\nThere is no minotaur." << endl;
        }
        else if (!ptr2Minotaur && !ptr2Minotaur->isAlive())
        {
            cout << "\nWhy would you try to stab a dead minotaur.  You've got too much time on your hands." << endl;
        }
        else if (hasA("knife") && !hasA("stalactite"))
        {
            cout << "\nThat puny little knife can't kill a minotaur.  You're gonna need something bigger than that." << endl;
        }
        else if (hasA("stalactite"))
        {
            cout << "\nThat's it!  You got em. The minotaur is bleeding profusely." << endl;
            delay(20);
            cout << "\nHe's dead." << endl;
            ptr2Minotaur->kill();
        }
        else
        {
            cout << "\nWith what?" << endl;
        }
    }
    else if (command == "shoot minotaur")
    {
        if (!ptr2Minotaur)
        {
            cout << "\nThere is no minotaur." << endl;
        }
        else if (!ptr2Gun)
        {
            cout << "\nYou can't shoot the minotaur without a gun." << endl;
        }
        else if (ptr2Gun->noBullets())
        {
            cout << "\nYour gun is empty." << endl;
        }
        else if (ptr2Gun && ptr2Minotaur && !(ptr2Minotaur->isAlive()))
        {
            cout << "\nWhy would you shoot a dead minotaur?" << endl;
            if (ptr2Gun->shoot()) cout << "\nYou just wasted a bullet." << endl;
        }
        else
        {
            cout << "\nYou're wasting your time and your bullet, you can't kill a minotaur with a gun.\nThey're almost invincible."  << endl;
            ptr2Gun->shoot();
        }
    }
    else if (command.substr(0,4) == "get ")
    {
        string what = secondWordOfCommand(command);
        getThing(what);
    }
    else if (command == "go shaft" || command == "go rope")
    {
        if (ptr2Minotaur->isAlive())
        {
            cout << "\nThe minotaur will not let you leave the chamber.  Somebody has to die." << endl;
        }
        else if (ropeInPlace)
        {
            changeDescriptionOfLocation(world, "chamber","in a large open chamber. There is water dripping from the ceiling.  A deep shaft descends from the center of the chamber.  A stalagmite, with a rope tied to it, rises toward the ceiling next to the shaft.  On the far side of the chamber a tunnel leads away.");
            moveTo("shaft",hasA_LitLantern());
        }
        else
        {
            cout << "\nThe shaft is too steep to descend without some help." << endl;
        }
    }
    else cout << "Huh?" << endl;

    if (timeInChamber == 6 && ptr2Minotaur && ptr2Minotaur->isAlive())
    {
        if (timeInChamber == 10)
        {
            cout << "\nThe minotaur just ripped your head off.  You should do something about that guy." << endl;
            delay(5);
            cout << "\nYou're dead!" << endl;
            delay(5);
            alive = false;
        }
        cout << "\nWatch out, the minotaur sees you in the chamber." << endl;
    }
    else
    {
        miscEvents();
    }

    return alive;
}

bool Human::processShaft(const string& command)
{
    static int timeInShaft = 0;
    timeInShaft++;
    Bat* ptr2Bat = dynamic_cast<Bat*>(getPtr2ThingInLocation("bat"));
    Serpent* ptr2Serpent = dynamic_cast<Serpent*>(getPtr2ThingInLocation("serpent"));
    bool alive = true;

    if (command == "go back" || command == "go chamber" || command == "return" || command == "go up")
    {
        moveTo("chamber",hasA_LitLantern());
    }

    else if (command == "go down" || command == "go bottom")
    {
        if (ptr2Bat->isHungry())
        {
            cout << "\nThe bat will not let you get out of the shaft." << endl;
        }
        if (ptr2Serpent->isAlive())
        {
            cout << "\nThe serpent will not let you leave.  Somebody has to die." << endl;
        }
        cout << "\nYou slowly descend the rope.  You pass a dense layer of cobwebs ..." << endl;
        delay(40);
        changeDescriptionOfLocation(world, "shaft","in a narrow vertical shaft. A rope leads up the shaft.  Cobwebs are very thick in here.");
        moveTo("room",hasA_LitLantern());
    }
    else if (command.substr(0,4) == "get ")
    {
        string what = secondWordOfCommand(command);
        getThing(what);
    }
    else if (command.substr(0,5) == "drop ")
    {
        string what = secondWordOfCommand(command);
        dropThing(what);
    }

    else if (command == "light match")
    {
        lightMatch();
    }

    else if (command == "light matches")
    {
        lightMatches();
    }

    else if (command.substr(0,9) == "light lan" || command == "ll")
    {
        lightLantern();
    }

    else if (command == "shoot bat")
    {
        cout << "\nYou can't shoot a bat.  It's flying too fast." << endl;
    }

    else if (command == "stab bat")
    {
        cout << "\nYou can't stab a bat.  It won't hold still." << endl;
    }

    else if (command == "kill bat")
    {
        cout << "\nHow?" << endl;
    }

    else if (command == "feed bat")
    {
        if (feed("bat"))
        {
            ptr2Bat->changeDescription("A pleased vampire bat.");
            ptr2Bat->setHunger(false);
            cout << "\nThe bat ate the spider." << endl;
        }
    }

    else if (command == "shoot serpent")
    {
        shoot("serpent");
    }

    else if (command == "stab serpent")
    {
        cout << "\nYou can't stab a serpent.  You can't get that close to it." << endl;
    }

    else if (command == "kill serpent")
    {
        cout << "\nHow?" << endl;
    }
    else if (command == "feed serpent")
    {
        if (feed("serpent"))
        {
            ptr2Serpent->changeDescription("A fat and happy serpent.");
            ptr2Serpent->setHunger(false);
            cout << "\nThe serpent ate the rat." << endl;
        }
        else cout << "\nThe serpent eats rats and humans.  You need to do something about this slime ball!  Now!!!" << endl;
    }
    else cout << "Huh?" << endl;

    if (timeInShaft > 5 && ptr2Bat && ptr2Bat->isAlive() && !ptr2Bat->isHungry())
    {
        if (timeInShaft > 7 && !hasA("statue"))
        {
            cout << "\nThe bat just bit you on the neck.  You are bleeding." << endl;
            delay(15);
            cout << "\nYou're dead!" << endl;
            delay(5);
            alive = false;
        }
        else
        {
            cout << "\nThe vampire bat is getting closer." << endl;
        }
    }

    else if (timeInShaft > 6 && ptr2Serpent && ptr2Serpent->isAlive())
    {
        if (timeInShaft > 8)
        {
            cout << "\nThe serpent just bit you on the arm." << endl;
            delay(10);
            cout << "\nHe injected his deadly poison into you." << endl;
            delay(10);
            cout << "\nYou're dead!" << endl;
            delay(5);
            alive = false;
        }
        else
        {
            cout << "\nThe serpent is slithering toward you." << endl;
        }
    }
    else miscEvents();

    return alive;
}


bool Human::processRoom(const string& command)
{
    static int timeInRoom = 0;
    timeInRoom++;
    Ghost* ptr2Ghost = dynamic_cast<Ghost*>(getPtr2ThingInLocation("ghost"));
    static bool ChestUnlocked = false;
    static bool ChestOpened = false;
    bool alive = true;

    if (command == "go back" || command == "go up" || command == "return" || command == "go rope" || command == "go shaft")
    {
        if (!ptr2Ghost)
            moveTo("shaft",hasA_LitLantern());
    }

    else if (command.substr(0,5) == "drop ")
    {
        string what = secondWordOfCommand(command);
        dropThing(what);
    }

    else if (command == "light match")
    {
        lightMatch();
    }

    else if (command == "light matches")
    {
        lightMatches();
    }

    else if (command.substr(0,9) == "light lan" || command == "ll")
    {
        lightLantern();
    }

    else if (command == "shoot ghost")
    {
        cout << "\nYou can't shoot a ghost!" << endl;
    }

    else if (command == "stab ghost")
    {
        cout << "\nYou can't stab a ghost." << endl;
    }

    else if (command == "kill ghost")
    {
        cout << "\nYou can't kill a ghost." << endl;
    }

    else if (command == "feed ghost")
    {
        cout << "\nThe ghost is not hungry." << endl;
    }
    else if (command == "bribe ghost")
    {
        if (hasA("coin"))
        {
            location->get_contents().remove("ghost");
            inventory.remove("coin");
            cout << "\nThe ghost took your gold coin and disappeared" << endl;
        }
        else cout << "\nYou don't have anything the ghost wants.  Ghosts like gold." << endl;
    }

    else if (command == "open chest")
    {
        if (ChestUnlocked)
        {
            cout << "\nThe lid of the chest opens slowly." << endl;
            delay(25);
            cout << "\nThe hinged are rusty.  This treasure chest hasn't been opened in a long time." << endl;
            delay(25);
            cout << "\nThere is a glow coming from within .";
            delay(5);
            for (int i = 0; i < 16; i++)
            {
                cout << '.';
                delay(4);
            }
            cout << "\n\nTHE TREASURE" << endl << "It's the Lost Golden Beagle Statue from the island of Amazonia Dotia Comia." << endl
                 << "It's worth billions!!!" << endl << "Now, if you can only get back to the Meadow with it ..." << endl;
            ChestOpened = true;
        }
        else
        {
            cout << "\nYou can't open the chest, it is locked." << endl;
        }
    }

    else if (command == "get chest")
    {
        cout << "\nIt's too heavy.  It must be full of something." << endl;
    }

    else if (command == "unlock chest")
    {
        if (hasA("key"))
        {
            cout << "\nThe chest is unlocked.  You knew that key would come in handy some day." << endl;
            ChestUnlocked = true;
        }
        else
        {
            cout << "\nYou'll need a key to unlock the chest." << endl;
        }
    }

    else if (command == "get statue" || command == "get beagle")
    {
        if (ChestOpened)
        {
            inventory.push("statue");
            cout << "\nIt's yours.  Now, let's make tracks and get outa here." << endl;
        }
        else
        {
            cout << "\nYou can't get that yet." << endl;
        }
    }
    else if (command.substr(0,4) == "get ")
    {
        string what = secondWordOfCommand(command);
        if (what == "lan") what = "lantern";
        getThing(what);
    }
    else cout << "Huh?" << endl;

    if (timeInRoom > 5 && ptr2Ghost)
    {
        if (timeInRoom > 7)
        {
            cout << "\nThe ghost just ate you.  And you thought ghosts didn't eat humans." << endl;
            delay(10);
            cout << "\nYou're dead now." << endl;
            delay(10);
            alive = false;
        }
        else
        {
            cout << "\nThe ghost approaches ..." << endl;
        }
    }
    else
    {
        miscEvents();
    }

    return alive;
}
