#pragma once
#include <iostream>
#include <string>
using namespace std;

//////////////////////////////////////
//                                  //
//          Storage Device          //
//                                  //
//////////////////////////////////////

class StorageDevice
{
private:
    string type,
        * sdtypes = NULL;
    int capacity;   //Unit: Gb
    double price;

    int num_of_sd;

public:
    // Constructors
    StorageDevice();
    StorageDevice(string t, int cap, double p, int nos);

    // Setters
    void setType(string t);
    void setCapacity(int cap);
    void setPrice(double p);
    void setNumOfSD(int nos);

    // Getters
    string getType();
    int getCapacity();
    double getPrice();
    int getNumOfSD();

    // Destructor
    ~StorageDevice();
};

//////////////////////////////////////
//                                  //
//          Storage Device          //
//                                  //
//////////////////////////////////////

// Constructors
StorageDevice::StorageDevice()
{
    type = "";
    capacity = 0;
    price = 0.0;
    num_of_sd = 0;
    sdtypes = new string[3]{ "Consumer HDD", "NAS HDD", "SSD" };
}

StorageDevice::StorageDevice(string t, int cap, double p, int nos)
{
    type = t;
    capacity = cap;
    price = p;
    num_of_sd = nos;
    sdtypes = new string[3]{ "Consumer HDD", "NAS HDD", "SSD" };
}

// Setters
void StorageDevice::setType(string t)
{
    type = t;
}

void StorageDevice::setCapacity(int cap)
{
    capacity = cap;
}

void StorageDevice::setPrice(double p)
{
    price = p;
}

void StorageDevice::setNumOfSD(int nos)
{
    num_of_sd = nos;
}

// Getters
string StorageDevice::getType()
{
    return type;
}

int StorageDevice::getCapacity()
{
    return capacity;
}

double StorageDevice::getPrice()
{
    return price;
}

int StorageDevice::getNumOfSD()
{
    return num_of_sd;
}

// Destructor
StorageDevice::~StorageDevice()
{
    delete[] sdtypes;
}