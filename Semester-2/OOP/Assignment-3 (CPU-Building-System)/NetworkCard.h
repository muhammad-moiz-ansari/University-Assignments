#pragma once
#include <iostream>
#include <string>
using namespace std;

////////////////////////////////////
//                                //
//          Network Card          //
//                                //
////////////////////////////////////

class NetworkCard
{
private:
    string type, * nctypes = NULL;
    int speed;
    double price;

public:
    // Constructors
    NetworkCard();
    NetworkCard(string t, int s, double p);

    // Setters
    void setType(string t);
    void setSpeed(int s);
    void setPrice(double p);

    // Getters
    string getType();
    int getSpeed();
    double getPrice();
    string getNcType(int ind);

    // Destructor
    ~NetworkCard();
};

////////////////////////////////////
//                                //
//          Network Card          //
//                                //
////////////////////////////////////

//Constructors
NetworkCard::NetworkCard()
{
    type = "";
    speed = 0;
    price = 0;
    nctypes = new string[2]{ "Ethernet", "Wi-Fi" };
}

NetworkCard::NetworkCard(string t, int s, double p)
{
    type = t;
    speed = s;
    price = p;
    nctypes = new string[2]{ "Ethernet", "Wi-Fi" };
}

//Setters
void NetworkCard::setType(string t)
{
    type = t;
}

void NetworkCard::setSpeed(int s)
{
    speed = s;
}

void NetworkCard::setPrice(double p)
{
    price = p;
}

//Getters
string NetworkCard::getType()
{
    return type;
}

int NetworkCard::getSpeed()
{
    return speed;
}

double NetworkCard::getPrice()
{
    return 0.0;
}

string NetworkCard::getNcType(int ind)
{
    return nctypes[ind - 1];
}

//Destructor
NetworkCard::~NetworkCard()
{
    delete[] nctypes;
}