#pragma once
#include <iostream>
#include <string>
#include "StorageDevice.h"
#include "MainMemory.h"
using namespace std;

///////////////////////////////////////
//                                   //
//          Physical Memory          //
//                                   //
///////////////////////////////////////

class PhysicalMemory : public MainMemory, public StorageDevice
{
private:
    int capacity;

public:
    //Constructors:
    PhysicalMemory();
    PhysicalMemory(int cap);

    //Setters:
    void setCapacity(int cap);

    //Getters:
    int getCapacity();
};

///////////////////////////////////////
//                                   //
//          Physical Memory          //
//                                   //
///////////////////////////////////////

//Constructors:
PhysicalMemory::PhysicalMemory()
{
    capacity = 0;
}
PhysicalMemory::PhysicalMemory(int cap)
{
    capacity = cap;
}

//Setters:
void PhysicalMemory::setCapacity(int cap)
{
    capacity = cap;
}

//Getters:
int PhysicalMemory::getCapacity()
{
    return capacity;
}