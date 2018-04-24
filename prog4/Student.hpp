//
//  Student.hpp
//
//  This is the header file for the class Student.
//
//  Minh An Cao
//

#ifndef Student_hpp
#define Student_hpp

using namespace std;

#include <string>

class Student
{
private:
    int id;
    string name;
    double gpa;

public:
	Student(); //constructor
	~Student(); //destructor

	//get functions
    int getId();
    string getName();
    double getGpa();

    //set functions
    void setId(int idNum);
    void setName(string name1);
    void setGpa(double gpa1);

    //display functions
	void display();

};

#endif
