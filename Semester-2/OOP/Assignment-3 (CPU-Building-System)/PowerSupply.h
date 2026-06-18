#pragma once
#include <iostream>
#include <string>
using namespace std;

////////////////////////////////////
//                                //
//          Power Supply          //
//                                //
////////////////////////////////////

class PowerSupply
{
private:
    int wattage;
    string efficiencyRating,
        * effrating = new string[3]{ "80 Plus Bronze", "80 Plus Gold", "80 Plus Platinum" };
    double price;

public:
    //Constructors:
    PowerSupply();
    PowerSupply(int watt, int effrat, double price);

    //Setters:
    void setWattage(int watt);
    void setEfficiencyRating(int effrat);
    void setPrice(double p);

    //Getters:
    int getWattage();
    string getEfficiencyRating();
    string getEfficiencyRating(int index);
    double getPrice();
};

////////////////////////////////////
//                                //
//          Power Supply          //
//                                //
////////////////////////////////////

//Constructors:
PowerSupply::PowerSupply()
{
    wattage = 0;
    efficiencyRating = "";
    price = 0;
}

PowerSupply::PowerSupply(int watt, int effrat, double p)
{
    wattage = watt;
    /*
    Efficient Ratings:
    1. 80 Plus Bronze
    2. 80 Plus Gold
    3. 80 Plus Platinum
    */
    efficiencyRating = effrating[effrat - 1];
    price = p;
}

//Setters:
void PowerSupply::setWattage(int watt)
{
    wattage = watt;
}
void PowerSupply::setEfficiencyRating(int effrat)
{
    efficiencyRating = effrating[effrat - 1];
}
void PowerSupply::setPrice(double p)
{
    price = p;
}

//Getters:
int PowerSupply::getWattage()
{
    return wattage;
}
string PowerSupply::getEfficiencyRating()
{
    return efficiencyRating;
}
string PowerSupply::getEfficiencyRating(int i)
{
    return effrating[i - 1];
}
double PowerSupply::getPrice()
{
    return price;
}