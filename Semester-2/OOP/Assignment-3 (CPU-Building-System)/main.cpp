#include <iostream>
#include <cmath>

#include "ControlUnit.h"
#include "ALU.h"
#include "GraphicCard.h"
#include "NetworkCard.h"
#include "CPU.h"
#include "StorageDevice.h"
#include "MainMemory.h"
#include "Ports.h"
#include "MotherBaord.h"
#include "PhysicalMemory.h"
#include "Case.h"
#include "Battery.h"
#include "PowerSupply.h"
#include "OuterParts.h"
#include "Computer.h"
#include "ComputerAssembly.h"
#include "Devices.h"

using namespace std;

int main()
{
	const string laptop = "Laptop", pc = "PC", maclaptop = "MAC_Laptop", macpc = "MAC_PC";

	int comptype = 0, ans = 0, m = 0;
	double p = 0;

	ComputerAssembly* ptrcomputerassembly = NULL;
	cout << "Welcome to Computer Assembling Area!\n\n";

	//Computer Type:
	Device device;
	comptype = device.selectcomp();

	//Make Computer
	if (comptype == 1)
	{
		Laptop laptop;
		ptrcomputerassembly = &(laptop.getComputerAssembly());
	}
	if (comptype == 2)
	{
		PC pc;
		ptrcomputerassembly = &(pc.getComputerAssembly());
	}
	if (comptype == 3)
	{
		MAC_PC macpc;
		ptrcomputerassembly = &(macpc.getComputerAssembly());
	}
	if (comptype == 4)
	{
		MAC_Laptop maclaptop;
		ptrcomputerassembly = &(maclaptop.getComputerAssembly());
	}
	ptrcomputerassembly->setDeviceType(comptype);

	//Adding Components:
	if (ptrcomputerassembly->getDeviceType() == pc || ptrcomputerassembly->getDeviceType() == macpc)
		ptrcomputerassembly->addPowerSupply();
	else
		ptrcomputerassembly->addBattery();

	ptrcomputerassembly->addCase();
	ptrcomputerassembly->addStorageDevice();
	ptrcomputerassembly->createPhysicalMemory();
	ptrcomputerassembly->addMainMemory();
	ptrcomputerassembly->createMotherBoard();
	
	if (ptrcomputerassembly->getDeviceType() == laptop || ptrcomputerassembly->getDeviceType() == pc)
	{
		cout << "\nDo you want to add Graphic Card?\n";
		cout << "1. Yes\n"
			<< "2. No\n"
			<< "Choose one option: ";

		while (1)
		{
			cin >> ans;
			if (ans >= 1 && ans <= 2)
				break;
			else
				cout << "Select only 1 or 2: ";
		}
		if (ans == 1)
			ptrcomputerassembly->addGraphicCard();
		else
			cout << "\nDefault Graphic Card\n";
	}
	else
	{
		ptrcomputerassembly->addGraphicCard("Apple", 16, 100000);
	}

	ptrcomputerassembly->addNetworkCard();

	if (ptrcomputerassembly->getDeviceType() == laptop || ptrcomputerassembly->getDeviceType() == pc)
	{
		ptrcomputerassembly->createComputer(1);
		ptrcomputerassembly->createCPU(1);
	}
	else
	{
		ptrcomputerassembly->createComputer(2);
		ptrcomputerassembly->createCPU(2);
	}

	///// Display /////
	ptrcomputerassembly->Display();

	/////// Price ////////
	p = ptrcomputerassembly->getBatteryPrice() + ptrcomputerassembly->getCasePrice() + ptrcomputerassembly->getGraphicCardPrice() + ptrcomputerassembly->getMainMemoryPrice() + ptrcomputerassembly->getNetworkCardPrice() + ptrcomputerassembly->getPowerSupplyPrice() + ptrcomputerassembly->getStorageDevicePrice() + ptrcomputerassembly->getIntel_AMDCPUPrice() + ptrcomputerassembly->getApple_CPUPrice() + ptrcomputerassembly->getMotherBoardPrice();
	ptrcomputerassembly->setPrice(p);

	cout << "Price = Rs. " << ptrcomputerassembly->getCompAssPrice() << endl;

	return 0;
}