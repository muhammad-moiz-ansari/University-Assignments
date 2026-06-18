#pragma once
#include <iostream>
#include <string>
#include "ControlUnit.h"
#include "ALU.h"
using namespace std;

///////////////////////////////
//                           //
//            CPU            //
//                           //
///////////////////////////////

//CPU
class CPU
{
protected:
    ALU alu;
    ControlUnit cu;

    string ArchType;
    string ArchSize;
    double price;
    string ProcessorType = "";
    string AS1 = "32-bit";
    string AS2 = "64-bit";

public:
    //Constructors:
    CPU();
    CPU(int regsize, double p);

    //Setters:
    void setRegisters(int reg);
    void setSizeofRegisters(int size);
    void setClock(float c);
    void setCPU(string str);
    void setArchSize(string str);
    void setPrice(double p);

    //Getters:
    int getAdders();
    int getSubtractor();
    int getRegisters();
    int getSizeofRegisters();
    float getClock();
    CPU getCPU();
    string getArchType();
    string getArchSize();
    double getPrice();
};

////////// Intel/AMD //////////
class Intel_AMD_CPU : public CPU
{
protected:
    bool selected;
    string* processortypes;

public:
    Intel_AMD_CPU();

    void setSelected(bool b);
    void setProcessorType(int index);

    bool getSelected();
    string getProcessorTypes(int index);
    string getProcessorType();
};

//////////// Apple ////////////
class Apple_CPU : public CPU
{
protected:
    bool selected;
    string* processortypes;

public:
    Apple_CPU();

    void setSelected(bool b);
    void setProcessorType(int index);

    bool getSelected();
    string getProcessorTypes(int index);
    string getProcessorType();
};

///////////////////////////////
//                           //
//            CPU            //
//                           //
///////////////////////////////

//CPU
//Constructors:
CPU::CPU()
{
    ArchSize = AS2;
    price = 0;
}
CPU::CPU(int regsize, double p)
{
    price = p;
    alu = ALU(regsize, ArchType);
    cu = ControlUnit(regsize);
}

//Setters:

void CPU::setRegisters(int reg)
{
    alu.setRegisters(reg);
}

void CPU::setSizeofRegisters(int size)
{
    alu.setSizeofRegisters(size);
}

void CPU::setClock(float c)
{
    cu.setClock(c);
}

void CPU::setCPU(string archtype)
{
    int add = 100, sub = 100, reg = 0, size = 64;
    float c = 0;
    if (archtype == "x86")
    {
        //if (archtype == "32-Bit")
        //{
        //    reg = 24;
        //    size = 32;
        //}
        //else
        //{
        reg = 32;
        //size = 64;
    //}
    }
    else if (archtype == "ARM64")
    {
        reg = 82;
        //if (archtype == "32-Bit")
        //    size = 32;
        //else
        //    size = 64;
    }

    //if (size == 32)
    //    c = 3.5;

    //else
    c = 5.5;

    alu.setAdders(add);
    alu.setSubtractor(sub);
    alu.setRegisters(reg);
    alu.setSizeofRegisters(size);
    cu.setClock(c);
}

void CPU::setArchSize(string str)
{
    ArchSize = str;
}

void CPU::setPrice(double p)
{
    price = p;
}

//Getters:
int CPU::getAdders()
{
    return alu.getAdders();
}

int CPU::getSubtractor()
{
    return alu.getSubtractor();
}

int CPU::getRegisters()
{
    return alu.getRegisters();
}

int CPU::getSizeofRegisters()
{
    return alu.getSizeofRegisters();
}

float CPU::getClock()
{
    return cu.getClock();
}

CPU CPU::getCPU()
{
    return *this;
}

string CPU::getArchType()
{
    return ArchType;
}

string CPU::getArchSize()
{
    return ArchSize;
}

double CPU::getPrice()
{
    return price;
}

////////// Intel/AMD //////////
Intel_AMD_CPU::Intel_AMD_CPU()
{
    processortypes = new string[4]{ "Core i3", "Core i5", "Core i7", "Core i9" };
    ArchType = "x86";
    selected = 0;
}

void Intel_AMD_CPU::setSelected(bool b)
{
    selected = b;
}

bool Intel_AMD_CPU::getSelected()
{
    return selected;
}

string Intel_AMD_CPU::getProcessorTypes(int index)
{
    return processortypes[index - 1];
}

string Intel_AMD_CPU::getProcessorType()
{
    return ProcessorType;
}

void Intel_AMD_CPU::setProcessorType(int index)
{
    ProcessorType = processortypes[index - 1];
}

//////////// Apple ////////////
Apple_CPU::Apple_CPU()
{
    processortypes = new string[3]{ "M1", "M1 Pro", "M1 Max" };
    ArchType = "ARM64";
    selected = 0;
}

void Apple_CPU::setSelected(bool b)
{
    selected = b;
}
void Apple_CPU::setProcessorType(int index)
{
    ProcessorType = processortypes[index - 1];
}

bool Apple_CPU::getSelected()
{
    return selected;
}

string Apple_CPU::getProcessorTypes(int index)
{
    return processortypes[index - 1];
}

string Apple_CPU::getProcessorType()
{
    return ProcessorType;
}
