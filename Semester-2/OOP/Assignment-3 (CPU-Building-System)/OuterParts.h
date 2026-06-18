#pragma once
#include <iostream>
#include <string>
#include "Case.h"
#include "Battery.h"
#include "PowerSupply.h"
using namespace std;

///////////////////////////////////
//                               //
//          Outer Parts          //
//                               //
///////////////////////////////////

class OuterParts
{
private:
    PowerSupply* ptrpowersupply;
    Battery* bat;
    Case* c;

public:
    // Constructors
    OuterParts();
    OuterParts(PowerSupply& ps, Battery& b, Case& ca);

    // Setters
    void setPowerSupply(PowerSupply& ps);
    void setBattery(Battery& b);
    void setCase(Case& ca);

    // Getters
    PowerSupply* getPowerSupply();
    Battery* getBattery();
    Case* getCase();

    // Destructor
    ~OuterParts();
};

///////////////////////////////////
//                               //
//          Outer Parts          //
//                               //
///////////////////////////////////

// Constructors
OuterParts::OuterParts()
{
    ptrpowersupply = NULL;
    bat = NULL;
    c = NULL;
}
OuterParts::OuterParts(PowerSupply& ps, Battery& b, Case& ca)
{
    ptrpowersupply = &ps;
    bat = &b;
    c = &ca;
}

// Setters
void OuterParts::setPowerSupply(PowerSupply& ps)
{
    ptrpowersupply = &ps;
}

void OuterParts::setBattery(Battery& b)
{
    bat = &b;
}

void OuterParts::setCase(Case& ca)
{
    c = &ca;
}

// Getters
PowerSupply* OuterParts::getPowerSupply()
{
    return ptrpowersupply;
}

Battery* OuterParts::getBattery()
{
    return bat;
}

Case* OuterParts::getCase()
{
    return c;
}

// Destructor
OuterParts::~OuterParts()
{
    delete ptrpowersupply;
    delete bat;
    delete c;
}