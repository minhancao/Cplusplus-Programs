//
//  Student.cpp
//
//  This file implements the functions in the Student header file.
//
//  Minh An Cao
//

#include "Student.hpp"
#include <iostream>
#include <iomanip>

Student::Student()
{
    Student::id = 0;
    Student::name = "";
    Student::gpa = 0;
}

Student::~Student()
{

}

int Student::getId()
{
    return Student::id;
}

string Student::getName()
{
    return Student::name;
}

double Student::getGpa()
{
    return Student::gpa;
}

void Student::setId(int idNum)
{
    Student::id = idNum;
}

void Student::setName(string name1)
{
    Student::name = name1;
}

void Student::setGpa(double gpa1)
{
    Student::gpa = gpa1;
}

void Student::display()
{

}


