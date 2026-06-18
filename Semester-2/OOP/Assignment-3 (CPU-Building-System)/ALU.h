#pragma once
#include <iostream>
#include <string>
using namespace std;

///////////////////////////
//                       //
//          ALU          //
//                       //
///////////////////////////

class ALU
{
private:
    int NoOfAdders;
    int NoOfSubtractor;
    int NoOfRegisters;
    int sizeOfRegisters;

public:
    //Constructors:
    ALU();
    ALU(int regsize, string archtype);

    //Setters:
    void setAdders(int add);
    void setSubtractor(int sub);
    void setRegisters(int reg);
    void setSizeofRegisters(int size);

    //Getters:
    int getAdders();
    int getSubtractor();
    int getRegisters();
    int getSizeofRegisters();
};

///////////////////////////////
//                           //
//            ALU            //
//                           //
///////////////////////////////

//Constructors:

ALU::ALU()
{
    NoOfAdders = 100;
    NoOfSubtractor = 100;
    NoOfRegisters = 32;
    sizeOfRegisters = 64;
}

ALU::ALU(int regsize, string archtype)
{
    NoOfAdders = 100;
    NoOfSubtractor = 100;
    if (archtype == "x86")
    {
        sizeOfRegisters = regsize;
        if (regsize == 32)
        {
            NoOfRegisters = 24;
        }
        else if (regsize == 64)
        {
            NoOfRegisters = 32;
        }
    }
    else if (archtype == "ARM64")
    {
        NoOfRegisters = 82;
        sizeOfRegisters = regsize;
    }
}

//Setters:

void ALU::setAdders(int add)
{
    NoOfAdders = add;
}

void ALU::setSubtractor(int sub)
{
    NoOfSubtractor = sub;
}

void ALU::setRegisters(int reg)
{
    NoOfRegisters = reg;
}

void ALU::setSizeofRegisters(int size)
{
    sizeOfRegisters = size;
}

//Getters:
int ALU::getAdders()
{
    return NoOfAdders;
}
int ALU::getSubtractor()
{
    return NoOfSubtractor;
}
int ALU::getRegisters()
{
    return NoOfRegisters;
}
int ALU::getSizeofRegisters()
{
    return sizeOfRegisters;
}
