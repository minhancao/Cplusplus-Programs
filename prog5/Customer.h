//
//  Customer.hpp
//
//  This is the header file for the class Customer.
//
//  Minh An Cao
//

#ifndef Customer_hpp
#define Customer_hpp

using namespace std;

#include <string>
#include <cstdlib>

class Customer
{
private:
    int years;
    int mileage;
    string name;
    double priority;
    double serialNum;

public:
	Customer(){}; //constructor
	~Customer(){}; //destructor

	//get functions
    int getYears(){return years;}
    int getMileage(){return mileage;}
    string getName(){return name;}
    double getPriority(){return priority;}
    double getSerialNum(){return serialNum;}

    //set functions
    void setYears(int yr){years = yr;}
    void setMileage(int mile){mileage = mile;}
    void setName(string n){name = n;}
    void setPriority(double p){priority = p;}
    void setSerialNum(double s){serialNum = s;}

    //display functions
	void display(){cout << endl; cout << "Name: " << name << endl; cout << "Mileage: " << mileage << endl; cout << "Years: " << years << endl; cout << endl;}

};

#endif
