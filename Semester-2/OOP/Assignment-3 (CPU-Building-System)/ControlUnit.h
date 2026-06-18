#pragma once
#include <iostream>
#include <string>
using namespace std;

////////////////////////////////////
//                                //
//          Control Unit          //
//                                //
////////////////////////////////////

class ControlUnit
{
private:
    float clock;

public:
    //Constructors:
    ControlUnit();
    ControlUnit(int regsize);

    //Setters:
    void setClock(float c);

    //Getters:
    float getClock();
};

////////////////////////////////////
//                                //
//          Control Unit          //
//                                //
////////////////////////////////////

//Constructors:
ControlUnit::ControlUnit()
{
    clock = 3;
}
ControlUnit::ControlUnit(int regsize)
{
    if (regsize == 32)
        clock = 3.5;

    else if (regsize == 64)
        clock = 5.5;
}

//Setters:
void ControlUnit::setClock(float c)
{
    clock = c;
}

//Getters:
float ControlUnit::getClock()
{
    return clock;
}