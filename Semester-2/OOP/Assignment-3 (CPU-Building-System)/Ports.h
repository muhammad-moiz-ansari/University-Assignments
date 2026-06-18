#pragma once
#include <iostream>
#include <string>
using namespace std;

////////////////////////////
//                        //
//          Port          //
//                        //
////////////////////////////

class Port
{
private:
    string type,    //                1              2              3           4             5             6            7
        * p_type = new string[7]{ "VGI Port", "Charging Port", "USB Port", "HDMI Port", "USB-C Port", "AUDIO Port", "LAN Port" };
    int baud_rate,
        * p_baudrate = new int[7] {0, 0, 5, 18, 5, 0, 3};   //Unit: Gbps

public:
    //Constructors:
    Port();
    Port(string t, int rate);

    //Setters:
    void setType(string t);
    void setType(int index);
    void setBaudRate(int rate);

    //Getters:
    string getType();
    string getP_Type(int ind);
    int getBaudRate();
    int getP_BaudRate(int index);
};

//////////////////////////////
//                          //
//           Port           //
//                          //
//////////////////////////////

//Constructors:
Port::Port()
{
    type = "";
    baud_rate = 0;
}
Port::Port(string t, int rate)
{
    type = "";
    baud_rate = 0;
}

//Setters:
void Port::setType(string t)
{
    type = t;
}

void Port::setBaudRate(int rate)
{
    baud_rate = rate;
}

//Getters:
string Port::getType()
{
    return type;
}

string Port::getP_Type(int ind)
{
    return p_type[ind - 1];
}

int Port::getBaudRate()
{
    return baud_rate;
}

int Port::getP_BaudRate(int index)
{
    return p_baudrate[index - 1];
}