#pragma once
#include <iostream>
#include <string>
using namespace std;


///////////////////////////////////
//                               //
//          Main Memory          //
//                               //
///////////////////////////////////

class MainMemory
{
private:
    int capacity;
    string technologyType,
        * techtype = new string[2]{ "Semiconductor" ,"Silicon" },
        PhyMemType,
        * pm_types = new string[2]{ "DDR4/5", "LPDDR4/5" };
    double price;

public:
    //Constructors:
    MainMemory();
    MainMemory(int cap, string tech, double p);

    //Setters:
    void setCapacity(int cap);
    void setTechnologyType(string tech);
    void setTechnologyType(int index);
    void setPhyMemType(string tech);
    void setPhyMemType(int index);
    void setPrice(double p);

    //Getters:
    int getCapacity();
    string getTechnologyType();
    string getPhyMemType();
    double getPrice();
};

///////////////////////////////////
//                               //
//          Main Memory          //
//                               //
///////////////////////////////////

//Constructors:
MainMemory::MainMemory()
{
    capacity = 0;
    technologyType = "";
    price = 0;
}
MainMemory::MainMemory(int cap, string tech, double p)
{
    capacity = cap;
    technologyType = tech;
    price = p;
}

//Setters:
void MainMemory::setCapacity(int cap)
{
    capacity = cap;
}
void MainMemory::setTechnologyType(string tech)
{
    technologyType = tech;
}
void MainMemory::setTechnologyType(int index)
{
    technologyType = techtype[index - 1];
}
void MainMemory::setPhyMemType(string pmt)
{
    PhyMemType = pmt;
}
void MainMemory::setPhyMemType(int index)
{
    PhyMemType = pm_types[index - 1];
}

void MainMemory::setPrice(double p)
{
    price = p;
}

//Setters:
int MainMemory::getCapacity()
{
    return capacity;
}
string MainMemory::getTechnologyType()
{
    return technologyType;
}
string MainMemory::getPhyMemType()
{
    return PhyMemType;
}

double MainMemory::getPrice()
{
    return price;
}