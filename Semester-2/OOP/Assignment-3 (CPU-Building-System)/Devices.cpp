#pragma once
#include <iostream>
#include <string>
#include "23i-0523_F_Q.h"   //This header file has already included Devices.h
using namespace std;


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

//ComputerAssembly& MAC::getComputerAssembly()
//{
//    return computerassembly;
//}

//////////////////////////////////
//                              //
//          MAC_Laptop          //
//                              //
//////////////////////////////////

MAC_Laptop::MAC_Laptop()
{
    computerassembly.setDeviceType("MAC_Laptop");
}

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
