#pragma once
#include <iostream>
#include <string>
#include "CPU.h"
#include "MotherBaord.h"
#include "PhysicalMemory.h"
using namespace std;

////////////////////////////////
//                            //
//          Computer          //
//                            //
////////////////////////////////

class Computer
{
private:
    PhysicalMemory* pm;
    MotherBoard* mb;
    CPU* cpu;


public:
    // Constructors
    Computer();
    Computer(PhysicalMemory PM, MotherBoard MB, CPU CPU);

    // Setters
    void setComputer(PhysicalMemory PM, MotherBoard MB, CPU CPU);

    // Getters
    PhysicalMemory* getPhysicalMemory();
    MotherBoard* getMotherBoard();
    CPU* getCPU();
};

////////////////////////////////
//                            //
//          Computer          //
//                            //
////////////////////////////////

//Constructors:
Computer::Computer()
{
    pm = NULL;
    mb = NULL;
    cpu = NULL;
}
Computer::Computer(PhysicalMemory PM, MotherBoard MB, CPU CPU)
{
    pm = &PM;
    mb = &MB;
    cpu = &CPU;
}

// Setter
void Computer::setComputer(PhysicalMemory PM, MotherBoard MB, CPU CPU)
{
    pm = &PM;
    mb = &MB;
    cpu = &CPU;
}

// Getters
PhysicalMemory* Computer::getPhysicalMemory()
{
    return pm;
}

MotherBoard* Computer::getMotherBoard()
{
    return mb;
}

CPU* Computer::getCPU()
{
    return cpu;
}