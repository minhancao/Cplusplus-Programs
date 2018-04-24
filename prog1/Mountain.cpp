#include "Mountain.hpp"
#include <iostream>
#include <iomanip>

Mountain::Mountain()
{
	Mountain::name = "";
	Mountain::elevation = 0;
	Mountain::range = "";
	Mountain::state = "";
}

Mountain::~Mountain()
{

}

string Mountain::getName()
{
    return Mountain::name;
}

double Mountain::getElevation()
{
    return Mountain::elevation;
}

string Mountain::getRange()
{
    return Mountain::range;
}

string Mountain::getState()
{
    return Mountain::state;
}

void Mountain::setName(string n)
{
    Mountain::name = n;
}

void Mountain::setElevation(double e)
{
    Mountain::elevation = e;
}

void Mountain::setRange(string r)
{
    Mountain::range = r;
}

void Mountain::setState(string s)
{
    Mountain::state = s;
}

void Mountain::displayMountain()
{
    cout  << setw(20) << left << name << " "
              << setw(7) << right << elevation << "  "
              << setw(22) << left << range << " " << left
              << setw(23) << state << endl;
}

void Mountain::displaySearchMountain()
{
    cout << "FOUND: "
             << name << " "
             << elevation << " "
             << range << " "
             << state << " \n\n";
}
