#pragma once
#include <iostream>
#include <string>
using namespace std;

////////////////////////////////////
//                                //
//          Graphic Card          //
//                                //
////////////////////////////////////

class GraphicCard
{
protected:
    string brand;
    int memorySize;
    double price;

public:
    //Constructors:
    GraphicCard();
    GraphicCard(string b, int ms, double p);

    //Setters:
    void setBrand(string b);
    void setMemorySize(int ms);
    void setPrice(double p);

    //Getters:
    string getBrand();
    int getMemorySize();
    double getPrice();
};

class GC_MAC : public GraphicCard
{
private:
    string type = "Apple GPU";

public:
    GC_MAC();
};

class GC_Windows : public GraphicCard
{
private:
    string type,
        * types = new string[2]{ "Nvidia","AMD" };

public:
    GC_Windows();
};

////////////////////////////////////
//                                //
//          Graphic Card          //
//                                //
////////////////////////////////////

/////// GC_Mac ////////
GC_MAC::GC_MAC()
{
    setBrand("Apple");
    setMemorySize(16);
    setPrice(100000);
}

/////// GC_Mac ////////
GC_Windows::GC_Windows()
{
    setBrand("None");
    setMemorySize(4);
    setPrice(1000);
}

//////// Graphic Card /////////
GraphicCard::GraphicCard()
{
    brand = "";
    memorySize = 0;
    price = 0;
}

GraphicCard::GraphicCard(string b, int ms, double p)
{
    brand = b;
    memorySize = ms;
    price = p;
}

void GraphicCard::setBrand(string b)
{
    brand = b;
}

void GraphicCard::setMemorySize(int ms)
{
    memorySize = ms;
}

void GraphicCard::setPrice(double p)
{
    price = p;
}

string GraphicCard::getBrand()
{
    return brand;
}

int GraphicCard::getMemorySize()
{
    return memorySize;
}

double GraphicCard::getPrice()
{
    return price;
}
