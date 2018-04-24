#ifndef Mountain_hpp
#define Mountain_hpp

using namespace std;

#include <string>

class Mountain
{
private:
    string name;
    double elevation;
    string range;
    string state;

public:
	Mountain(); //constructor
	~Mountain(); //destructor

	//get functions
    string getName();
    double getElevation();
    string getRange();
    string getState();

    //set functions
    void setName(string n);
    void setElevation(double e);
    void setRange(string r);
    void setState(string s);

    //display functions
	void displayMountain();
    void displaySearchMountain();

};

#endif
