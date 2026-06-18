#pragma once
#include <iostream>
#include <string>
#include "MainMemory.h"
#include "Ports.h"
using namespace std;

///////////////////////////////////
//                               //
//         Mother Board          //
//                               //
///////////////////////////////////

class MotherBoard
{
private:
    MainMemory* mm;
    int num_of_ports;
    double price;
    Port* ports;
    GraphicCard* gc;
    //                                   1              2              3           4             5             6            7
    string* p_type = new string[7]{ "VGI Port", "Charging Port", "USB Port", "HDMI Port", "USB-C Port", "AUDIO Port", "LAN Port" };
    int* p_baudrate = new int[7] {0, 0, 5, 18, 5, 0, 3};   //Unit: Gbps

public:
    //Constructors:
    MotherBoard();
    MotherBoard(MainMemory M, int p_n, GraphicCard GC, double p);

    //Setters:
    void setMotherBoard(MainMemory M, int p_n);
    void setMainMemory(MainMemory M);
    void setNumOfPorts(int n);
    void setPorts(int ind, int br, int type);
    void setPorts(int ind, int br, string str);
    void setPrice(double p);

    //Getters:
    MainMemory getMainMemory();
    int getMainMemoryCapacity();
    string getMainMemoryType();
    string getMainMemoryPhyType();
    int getNumOfPorts();
    string getPortType(int ind);
    int getPortBaudRate(int ind);
    double getPrice();
    string getP_Types(int ind);
    int getP_BaudRates(int ind);
};

///////////////////////////////////
//                               //
//         Mother Board          //
//                               //
///////////////////////////////////

//Constructors:
MotherBoard::MotherBoard()
{
    num_of_ports = 0;
    ports = new Port[0]();
    price = 0;
}

MotherBoard::MotherBoard(MainMemory M, int p_n, GraphicCard GC, double p)
{
    mm = &M;
    num_of_ports = p_n;
    ports = new Port[num_of_ports]();
    gc = &GC;
    price = p;
}

//Setters:
void MotherBoard::setMotherBoard(MainMemory M, int p_n)
{
    mm = &M;
    num_of_ports = p_n;
    delete[] ports;
    ports = new Port[num_of_ports]();
}
void MotherBoard::setMainMemory(MainMemory M)
{
    delete mm;
    mm = &M;
}
void MotherBoard::setNumOfPorts(int n)
{
    num_of_ports = n;
}
void MotherBoard::setPorts(int ind, int br, int typenum)
{
    ports[ind].setBaudRate(br);

    // Port String Numberings:
    // 1. "VGI Port"
    // 2. "Charging Port"
    // 3. "USB Port"
    // 4. "HDMI Port"
    // 5. "USB-C Port"
    // 6. "AUDIO Port"
    // 7. "LAN Port"

    ports[ind].setType(ports->getP_Type(typenum - 1));
}
void MotherBoard::setPorts(int ind, int br, string str)
{
    ports[ind].setBaudRate(br);
    ports[ind].setType(str);
}

//Getters:
MainMemory MotherBoard::getMainMemory()
{
    return *mm;
}

int MotherBoard::getMainMemoryCapacity()
{
    return mm->getCapacity();
}

string MotherBoard::getMainMemoryType()
{
    return mm->getTechnologyType();
}

string MotherBoard::getMainMemoryPhyType()
{
    return mm->getPhyMemType();
}

int MotherBoard::getNumOfPorts()
{
    return num_of_ports;
}

string MotherBoard::getPortType(int ind)
{
    return ports[ind - 1].getType();
}

int MotherBoard::getPortBaudRate(int ind)
{
    return ports[ind - 1].getBaudRate();
}

string MotherBoard::getP_Types(int ind)
{
    return p_type[ind];
}
int MotherBoard::getP_BaudRates(int ind)
{
    return p_baudrate[ind];
}

void MotherBoard::setPrice(double p)
{
    price = p;
}

double MotherBoard::getPrice()
{
    return price;
}