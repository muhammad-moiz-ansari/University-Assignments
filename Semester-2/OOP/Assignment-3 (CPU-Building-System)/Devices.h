#pragma once
#include <iostream>
using namespace std;

//////////////////////////////
//                          //
//          Device          //
//                          //
//////////////////////////////

class Device
{
protected:
    int CompType;
    ComputerAssembly* computerassptr;

public:
    Device();

    int getCompType();
    ComputerAssembly& getComputerAssembly();

    int selectcomp();
};


//////////////////////////////
//                          //
//          Laptop          //
//                          //
//////////////////////////////

class Laptop : public Device
{
private:
    ComputerAssembly computerassembly;

public:
    Laptop();
};

//////////////////////////
//                      //
//          PC          //
//                      //
//////////////////////////

class PC : public Device
{
private:
    ComputerAssembly computerassembly;

public:
    PC();
};

//////////////////////////////
//                          //
//          MAC_PC          //
//                          //
//////////////////////////////

class MAC_PC : public Device
{
private:
    ComputerAssembly computerassembly;

public:
    MAC_PC();
};

//////////////////////////////////
//                              //
//          MAC_Laptop          //
//                              //
//////////////////////////////////

class MAC_Laptop : public Device
{
private:
    ComputerAssembly computerassembly;

public:
    MAC_Laptop();
};







//////////////////////////////
//                          //
//          Device          //
//                          //
//////////////////////////////

//Constructors
Device::Device()
{
    CompType = 0;
    computerassptr = new ComputerAssembly();
}

//Getter
int Device::getCompType()
{
    return CompType;
}

//Functions
int Device::selectcomp()
{
    cout << "Which one do you want?\n"
        << "1. Laptop\n2. PC\n3. MAC_PC\n4. MAC_Laptop\n\nComputer Type: ";
    while (1)
    {
        cin >> CompType;
        if (CompType >= 1 && CompType <= 4)
            break;
        else
            cout << "Select only 1, 2, 3 or 4: ";
    }

    return CompType;
}

ComputerAssembly& Device::getComputerAssembly()
{
    return *computerassptr;
}

//////////////////////////////
//                          //
//          Laptop          //
//                          //
//////////////////////////////

Laptop::Laptop()
{
    computerassembly.setDeviceType("Laptop");
}

//ComputerAssembly& Laptop::getComputerAssembly()
//{
//    return computerassembly;
//}

//////////////////////////
//                      //
//          PC          //
//                      //
//////////////////////////

PC::PC()
{
    computerassembly.setDeviceType("PC");
}

//ComputerAssembly& PC::getComputerAssembly()
//{
//    return computerassembly;
//}

//////////////////////////////
//                          //
//          MAC_PC          //
//                          //
//////////////////////////////

MAC_PC::MAC_PC()
{
    computerassembly.setDeviceType("MAC_PC");
}

//////////////////////////////////
//                              //
//          MAC_Laptop          //
//                              //
//////////////////////////////////

MAC_Laptop::MAC_Laptop()
{
    computerassembly.setDeviceType("MAC_Laptop");
}