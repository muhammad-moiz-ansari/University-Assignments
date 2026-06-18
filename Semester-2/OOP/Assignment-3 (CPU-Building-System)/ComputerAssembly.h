#pragma once
#include <iostream>
using namespace std;

////////////////////////////////////////
//                                    //
//          Computer Assembly         //
//                                    //
////////////////////////////////////////

class ComputerAssembly
{
protected:
    string DeviceType;
    double price;

    PowerSupply powersupply;
    Battery battery;
    Case dev_case;
    NetworkCard networkcard;
    GraphicCard graphiccard;
    MainMemory mainmemory;
    StorageDevice storagedevice;
    PhysicalMemory physicalmemory;
    MotherBoard motherboard;
    OuterParts outerparts;
    Intel_AMD_CPU IAcpu;
    Apple_CPU Acpu;
    Computer computer;

public:
    const string* const devicetype = new string[4]{ "Laptop","PC","MAC_PC", "MAC_Laptop" };
    const string laptop = "Laptop", pc = "PC", maclaptop = "MAC_Laptop", macpc = "MAC_PC";
    //Constructor
    ComputerAssembly();
    ComputerAssembly(string devtype, double p);

    //Setter
    void setDeviceType(int compt);
    void setDeviceType(string str);
    void setPrice(int p);

    //Getter
    string getDeviceType();
    double getCompAssPrice();

    double getPowerSupplyPrice();
    double getBatteryPrice();
    double getCasePrice();
    double getNetworkCardPrice();
    double getGraphicCardPrice();
    double getMainMemoryPrice();
    double getStorageDevicePrice();
    double getMotherBoardPrice();
    double getIntel_AMDCPUPrice();
    double getApple_CPUPrice();


    //Functions
    void Display();

    //Addition:
    void addPowerSupply();
    void addBattery();
    void addCase();
    void addNetworkCard();
    void addGraphicCard();
    void addGraphicCard(string b, int msize, double p);
    void addStorageDevice();
    void addMainMemory();
    void createPhysicalMemory();
    void createComputer(int);
    void createOuterParts();
    void createCPU(int);
    void createMotherBoard();

    //Destructor
    ~ComputerAssembly();
};





/////////////////////////////////////////
//                                     //
//          Computer Assembly          //
//                                     //
/////////////////////////////////////////

//Constructors
ComputerAssembly::ComputerAssembly()
{
    DeviceType = "";
    price = 0;
}
ComputerAssembly::ComputerAssembly(string devtype, double p)
{
    DeviceType = devtype;
    price = p;
}

//Setter
void ComputerAssembly::setDeviceType(int compt)
{
    DeviceType = devicetype[compt - 1];
}
void ComputerAssembly::setDeviceType(string str)
{
    DeviceType = str;
}
void ComputerAssembly::setPrice(int p)
{
    price = p;
}

//Getters
string ComputerAssembly::getDeviceType()
{
    return DeviceType;
}
double ComputerAssembly::getCompAssPrice()
{
    return price;
}

// Getters for component prices in ComputerAssembly class

double ComputerAssembly::getPowerSupplyPrice()
{
    return powersupply.getPrice();
}

double ComputerAssembly::getBatteryPrice()
{
    return battery.getPrice();
}

double ComputerAssembly::getCasePrice()
{
    return dev_case.getPrice();
}

double ComputerAssembly::getNetworkCardPrice()
{
    return networkcard.getPrice();
}

double ComputerAssembly::getGraphicCardPrice()
{
    return graphiccard.getPrice();
}

double ComputerAssembly::getMainMemoryPrice()
{
    return mainmemory.getPrice();
}

double ComputerAssembly::getStorageDevicePrice()
{
    return storagedevice.getPrice();
}

double ComputerAssembly::getMotherBoardPrice()
{
    return motherboard.getPrice();
}

double ComputerAssembly::getIntel_AMDCPUPrice()
{
    return IAcpu.getPrice();
}

double ComputerAssembly::getApple_CPUPrice()
{
    return Acpu.getPrice();
}

//////////////// Functions ///////////////////
// 
// //Addition:     //Inputs have limits. Check limits, if not in range, again take input in cin. Continue loop till correct input is given
// 
//Display:      
void ComputerAssembly::Display()
{
    cout<<"\n\n" << "-------------------------------------\n"
                 << "|      Computer Made Qualities      |\n"
                 << "-------------------------------------\n\n"
        << "Device Type: " << DeviceType << endl << endl
        << "Case:\n"
        << "Colour: " << dev_case.getColor() << endl
        << "Form Factor: " << dev_case.getFormFactor() << endl << endl;

    if (DeviceType == pc || DeviceType == macpc)
    {
        cout << "Power Supply:\n"
            << "Wattage:" << powersupply.getWattage() << "W" << endl
            << "Efficiency Rating: " << powersupply.getEfficiencyRating() << endl << endl;
    }
    else
    {
        cout << "Battery:\n"
            << "Capacity: " << battery.getCapacity() << "Wh" << endl << endl;
    }

    cout << "Main Memory:\n";
    cout << "Made of: " << mainmemory.getTechnologyType() << endl;
    cout << "Type: " << mainmemory.getPhyMemType() << endl;
    cout << "Capacity: " << mainmemory.getCapacity() << endl << endl;


    cout << "Ports:\n";
    for (int i = 0; i < motherboard.getNumOfPorts(); ++i)
        cout << i + 1 << ". Type: " << motherboard.getPortType(i + 1) << "\t" << "Baud Rate: " << motherboard.getPortBaudRate(i + 1) << " baud" << endl;
    cout << endl;

    cout << "Storage Devices:\n"
        << "Type: " << storagedevice.getType() << endl
        << "Capacity: " << storagedevice.getCapacity() << "GB" << endl << endl;

    cout << "Physical Memory:\n"
        << "Number of Storage Devices: " << physicalmemory.getCapacity() << endl << endl;

    cout << "Network Card:\n"
        << "Type: " << networkcard.getType() << endl
        << "Speed: " << networkcard.getSpeed() << endl << endl;

    cout << "Graphic Card:\n"
        << "Brand: " << graphiccard.getBrand() << endl
        << "Memory Size: " << graphiccard.getMemorySize() << "Gb" << endl << endl;

    cout << "CPU:\n";
    if (IAcpu.getSelected())
    {
        cout << "Processor: " << IAcpu.getProcessorType() << endl
            << "Achitecture Type: " << IAcpu.getArchType() << endl
            << "Architecture Size: " << IAcpu.getArchSize() << endl
            << "No Of Adders: " << IAcpu.getAdders() << endl
            << "No Of Subtractor: " << IAcpu.getSubtractor() << endl
            << "No Of Registers: " << IAcpu.getRegisters() << endl
            << "Size Of Registers: " << IAcpu.getSizeofRegisters() << endl << endl;
    }
    else
    {
        cout << "Processor: " << Acpu.getProcessorType() << endl
            << "Achitecture Type: " << Acpu.getArchType() << endl
            << "Architecture Size: " << Acpu.getArchSize() << endl
            << "No Of Adders: " << Acpu.getAdders() << endl
            << "No Of Subtractor: " << Acpu.getSubtractor() << endl
            << "No Of Registers: " << Acpu.getRegisters() << endl
            << "Size Of Registers: " << Acpu.getSizeofRegisters() << endl << endl;
    }


}

//Addition:
void ComputerAssembly::addPowerSupply()
{
    int watt = 0, effrat = 0;
    double p = 0;

    cout << "\nEnter the attributes of power supply:\n";
    if (DeviceType == "PC" || DeviceType == "MAC_PC")
    {
        //Wattage
        cout << "\nEnter Wattage (Min = 300W, Max = 1200W): ";
        while (1)
        {
            cin >> watt;
            if (watt >= 300 && watt <= 1200)
                break;
            else
                cout << "Select between the range (Min = 300W, Max = 1200W): ";
        }
        powersupply.setWattage(watt);
        cout << "Wattage = " << powersupply.getWattage() << " W\n";

        //Efficiency Rating
        cout << "\nFor efficiency ratting, choose one of the following:\n"
            << "1. 80 Plus Bronze\n"
            << "2. 80 Plus Gold\n"
            << "3. 80 Plus Platinum\n\nRating: ";
        while (1)
        {
            cin >> effrat;
            if (effrat == 1 || effrat == 2 || effrat == 3)
                break;
            else
                cout << "Select only 1, 2 or 3: ";
        }
        powersupply.setEfficiencyRating(effrat);
        cout << "\nEfficiency Rating: " << powersupply.getEfficiencyRating() << endl;

        //Price:
        if (powersupply.getEfficiencyRating() == powersupply.getEfficiencyRating(1))
            p = powersupply.getWattage() * 27.80;
        else if (powersupply.getEfficiencyRating() == powersupply.getEfficiencyRating(2))
            p = powersupply.getWattage() * 41.65;
        else if (powersupply.getEfficiencyRating() == powersupply.getEfficiencyRating(3))
            p = powersupply.getWattage() * 55.55;
        powersupply.setPrice(p);
        cout << "Price = " << p << endl;
    }
    else
        cout << "\nPower supply not supported.\n";
}

void ComputerAssembly::addBattery()
{
    int cap = 0;
    double p = 0;

    cout << "\nEnter the attributes of battery:\n";
    if (DeviceType == "Laptop" || DeviceType == "MAC_Laptop")
    {
        //Battery
        cout << "\nEnter Capacity of Battery in Wh (Min = 30Wh, Max = 60Wh): ";
        while (1)
        {
            cin >> cap;
            if (cap >= 30 && cap <= 60)
                break;
            else
                cout << "Select between the range (Min = 30Wh, Max = 60Wh): ";
        }
        battery.setCapacity(cap);
        cout << "\nBattery = " << battery.getCapacity() << " W\n";

        //Price
        p = battery.getCapacity() * 135;
        battery.setPrice(p);
        cout << "Price = " << p << endl;
    }
    else
        cout << "\nBattery not supported.\n";
}

void ComputerAssembly::addCase()
{
    int ff = 0, col = 0;
    float p = 0;

    //Form Factor:
    cout << "\nFor Form Factor, choose one of the following:\n";
    if (DeviceType == pc || DeviceType == macpc)
    {
        cout << "PC:\n"
            << "1. ATX\n"
            << "2. Micro ATX\n"
            << "3. Mini ITX\n\n";
    }
    else
    {
        cout << "Laptop :\n"
            << "1. Traditional Laptop\n"
            << "2. Gaming Laptop\n"
            << "3. Ultrabook\n";
    }
    while (1)
    {
        cin >> ff;
        if (ff >= 1 && ff <= 3)
            break;
        else
            cout << "Select only 1, 2 or 3: ";
    }
    if (DeviceType == pc || DeviceType == macpc)
        dev_case.setFormFactor(ff);
    else
    {
        ff += 3;
        dev_case.setFormFactor(ff);
    }

    cout << "\nForm Factor: " << dev_case.getFormFactor(ff) << endl;

    //Colors:
    cout << "\nFor Colors, choose one of the following:\n"
        << "1. Black\n"
        << "2. Grey\n"
        << "3. White\n"
        << "4. Silver\n"
        << "5. Gold\n";
    while (1)
    {
        cin >> col;
        if (col >= 1 && col <= 5)
            break;
        else
            cout << "Select only between 1 & 5: ";
    }
    dev_case.setColor(col);
    cout << "\nColor: " << dev_case.getColor(col) << endl;

    //Price:
    if (DeviceType == "PC" || DeviceType == "MAC_PC")
    {
        cout << "\nEnter the price of case you want (Min = Rs.1000 , Max = Rs.10000): ";
        while (1)
        {
            cin >> p;
            if (p >= 1000 && p <= 10000)
                break;
            else
                cout << "Select in the given range (Min = Rs.1000 , Max = Rs.10000): ";
        }
        dev_case.setPrice(p);
        cout << "\nPrice = " << dev_case.getPrice() << endl;
    }
    else
        dev_case.setPrice(0);
}

void ComputerAssembly::addNetworkCard()
{
    int t = 0, n = 0;
    float min = 0.1, max = 0,
        maxlaptop = 10,
        maxpc = 50;
    double p = 0;

    //Type:
    cout << "\nFor Network Card Type, choose one of the following:\n"
        << "1. Ethernet\n"
        << "2. Wi-Fi\n";
    while (1)
    {
        cin >> t;
        if (t >= 1 && t <= 2)
            break;
        else
            cout << "Select 1 or 2: ";
    }
    networkcard.setType(networkcard.getNcType(t));
    cout << "\nNetwork Card Type: " << networkcard.getType() << endl;

    //Speed:
    if (DeviceType == laptop || DeviceType == maclaptop)
        max = maxlaptop;
    else
        max = maxpc;

    cout << "\nEnter Speed of Network Card (Gbps): \n";
    while (1)
    {
        cin >> n;
        if (n >= min)
        {
            if (n <= max)
                break;
            else
                cout << "\nEnter within the range\nMin = " << min << ", Max = " << max << "\nSpeed (Gbps) : ";
        }
        else
            cout << "\nEnter within the range\nMin = " << min << ", Max = " << max << "\nSpeed (Gbps): ";
    }
    networkcard.setSpeed(n);
    cout << "\nSpeed = " << n << " Gbps\n";

    //Price:
    t = 5.5 * 275;
    p = n * t;
    networkcard.setPrice(p);
    cout << "\nPrice = " << p << endl;
}

void ComputerAssembly::addGraphicCard()
{
    string br = "";
    int n = 0, t = 0;
    int min = 1, max = 0;
    int maxlaptop = 16;
    int maxpc = 24;
    double p = 0;

    //Brand:
    cout << "\nEnter the brand of Graphic Card: ";
    cin >> br;
    graphiccard.setBrand(br);

    //Memory Size:
    if (DeviceType == laptop || DeviceType == maclaptop)
        max = maxlaptop;
    else
        max = maxpc;

    cout << "\nEnter capacity of Graphic Card (Gb): \n";
    while (1)
    {
        cin >> n;
        if (n >= min)
        {
            if (n <= max)
                break;
            else
                cout << "\nEnter within the range\nMin = " << min << ", Max = " << max << "\nCapacity(Gb) : ";
        }
        else
            cout << "\nEnter within the range\nMin = " << min << ", Max = " << max << "\nCapacity (Gb): ";
    }
    graphiccard.setMemorySize(n);
    cout << "\nCapacity: " << graphiccard.getMemorySize() << endl;

    //Type:
    cout << "\nFor Graphic Card Type, choose one of the following:\n"
        << "1. Nvidia\n"
        << "2. AMD\n";
    while (1)
    {
        cin >> t;
        if (t >= 1 && t <= 2)
            break;
        else
            cout << "Select 1 or 2: ";
    }
    /////////////////////////// set type

        //Quality:
    cout << "\nFor Quality, choose one of the following:\n"
        << "1. Entry-level graphics card\n"
        << "2. Mid-range graphics card\n"
        << "3. High-end graphics card\n"
        << "4. Workstation or professional-grade graphics card\n";
    while (1)
    {
        cin >> t;
        if (t >= 1 && t <= 4)
            break;
        else
            cout << "Select only between 1 & 4: ";
    }

    //Price:
    if (t == 1)
        n = 4 * 275;
    else if (t == 2)
        n = 5 * 275;
    else if (t == 3)
        n = 7 * 275;
    else if (t == 4)
        n = 9 * 275;

    p = n * graphiccard.getMemorySize();
    graphiccard.setPrice(p);
    cout << "\nPrice = " << p << endl;
}

inline void ComputerAssembly::addGraphicCard(string b, int msize, double p)
{
    graphiccard.setBrand(b);
    graphiccard.setMemorySize(msize);
    graphiccard.setPrice(p);
}

void ComputerAssembly::addMainMemory()
{
    int n = 0;

    //Main Memory Type:
    if (DeviceType == laptop || DeviceType == pc)
    {
        mainmemory.setTechnologyType(1);
        mainmemory.setPhyMemType(1);
    }
    else if (DeviceType == maclaptop || DeviceType == macpc)
    {
        mainmemory.setTechnologyType(2);
        mainmemory.setPhyMemType(2);
    }
    cout << "\nMain Memory Technology Type: " << mainmemory.getTechnologyType() << endl;
    cout << "\nMain Memory Physical Memory Type: " << mainmemory.getPhyMemType() << endl;

    //Main Memory Capacity:
    cout << "\nHow much capacity of main memory do you want?\n"
        << "Capacity = 2^n \n\nn: ";
    while (1)
    {
        cin >> n;
        if (n >= 2)
        {
            if ((DeviceType == laptop || DeviceType == maclaptop) && n <= 7)
                break;
            else if ((DeviceType == pc || DeviceType == macpc) && n <= 8)
                break;
            else
                cout << "\nMin Cap = 4Gb, Max Cap = 128Gb(for laptop), 256Gb(for PC) \nSelect n between 2-7(for laptop), 2-8(for PC): ";
        }
        else
            cout << "\nMin Cap = 4Gb, Max Cap = 128Gb(for laptop), 256Gb(for PC) \nSelect n between 2-7(for laptop), 2-8(for PC): ";
    }
    mainmemory.setCapacity(pow(2, n));
    cout << "\nMain Memory Capacity = " << mainmemory.getCapacity() << "Gb\n";
}

void ComputerAssembly::addStorageDevice()
{
    int sd = 0, n = 0;
    bool b = 0;
    double p = 0;

    int nos = 0,    //No of sd
        min = 1,
        maxlaptop = 2,
        maxpc = 4;
    //Number of SDs:
    cout << "\nHow many storage devices do you want? (Min = " << min << ", Max = " << maxlaptop << "(for Laptop), " << maxpc << "(for PC))\nNo. of SDs: ";
    while (1)
    {
        cin >> nos;
        if (nos >= min)
        {
            if ((DeviceType == laptop || DeviceType == maclaptop) && nos <= maxlaptop)
                break;
            else if ((DeviceType == pc || DeviceType == macpc) && nos <= maxpc)
                break;
            else
                cout << "\nChoose within the range\nMin = " << min << ", Max = " << maxlaptop << "(for Laptop), " << maxpc << "(for PC) \nNo. of SDs: ";
        }
        else
            cout << "\nChoose within the range\nMin = " << min << ", Max = " << maxlaptop << "(for Laptop), " << maxpc << "(for PC) \nNo. of SDs: ";
    }
    storagedevice.setNumOfSD(nos);

    //Type and Capacity:
    //Storage Device Type:
    cout << "\nWhat type of storage device do you want?\n"
        << "1. Consumer HDD\n2. NAS HDD\n3. SSD\n\nStorage Device Type: ";

    while (1)
    {
        cin >> sd;
        if (sd >= 1 && sd <= 3)
            break;
        else
            cout << "Select only 1, 2 or 3: ";
    }
    if (sd == 1)
        storagedevice.setType("Consumer HDD");
    else if (sd == 2)
        storagedevice.setType("NAS HDD");
    else
        storagedevice.setType("SSD");

    cout << "\nStorage Device Type = " << storagedevice.getType() << endl;

    //Storage Device Capacity
    cout << "\nHow much capacity of storage device do you want?\n";
    if (storagedevice.getType() == "Consumer HDD" || storagedevice.getType() == "NAS HDD")
    {
        min = 1;
        maxlaptop = 4;
        maxpc = 14;

        cout << "1. 500 GB\n"
            << "2. More than 1 TB\n"
            << "Choose one option: ";

        sd = 0;
        while (1)
        {
            cin >> sd;
            if (sd >= 1 && sd <= 2)
                break;
            else
                cout << "Select only 1 or 2: ";
        }
        if (sd == 1)
            storagedevice.setCapacity(500);
        else
            b = 1;
    }
    else if (storagedevice.getType() == "SSD")
    {
        min = 1;
        maxlaptop = 4;
        maxpc = 8;

        cout << "1. 128 GB\n"
            << "2. 256 GB\n"
            << "3. 512 GB\n"
            << "4. More than 1 TB\n"
            << "Choose one option: ";

        sd = 0;
        while (1)
        {
            cin >> sd;
            if (sd >= 1 && sd <= 4)
                break;
            else
                cout << "Select only 1, 2, 3 or 4: ";
        }
        if (sd == 1)
            storagedevice.setCapacity(128);
        else if (sd == 2)
            storagedevice.setCapacity(256);
        else if (sd == 3)
            storagedevice.setCapacity(512);
        else
            b = 1;
    }

    if (b == 1)
    {
        cout << "Capacity (Tb): ";
        while (1)
        {
            cin >> n;
            if (n >= min)
            {
                if ((DeviceType == laptop || DeviceType == maclaptop) && n <= maxlaptop)
                    break;
                else if ((DeviceType == pc || DeviceType == macpc) && n <= maxpc)
                    break;
                else
                    cout << "\nEnter within the range\nMin = " << min << ", Max = " << maxlaptop << "(for Laptop), " << maxpc << "(for PC) \nCapacity (Tb): ";
            }
            else
                cout << "\nEnter within the range\nMin = " << min << ", Max = " << maxlaptop << "(for Laptop), " << maxpc << "(for PC) \nCapacity (Tb): ";
        }
        storagedevice.setCapacity(n * 1000);
    }

    //Price:
    if (storagedevice.getType() == "Consumer HDD" || storagedevice.getType() == "NAS HDD")
        p = storagedevice.getCapacity() * 10.8;
    else if (storagedevice.getType() == "SSD")
        p = storagedevice.getCapacity() * 50;

    cout << "Price = " << p << endl;
    storagedevice.setPrice(p);
}

void ComputerAssembly::createPhysicalMemory()
{
    physicalmemory.setCapacity(storagedevice.getNumOfSD());
}


void ComputerAssembly::createOuterParts()
{
    outerparts.setPowerSupply(powersupply);
    outerparts.setBattery(battery);
    outerparts.setCase(dev_case);
}

void ComputerAssembly::createCPU(int m)
{
    int t = 0;
    double p = 0;
    cout << "\n---CPU---\n";

    //Arch Size:
    if (m == 1)
        cout << "\nArchitecture Size: " << IAcpu.getArchSize() << endl;
    else
        cout << "\nArchitecture Size: " << Acpu.getArchSize() << endl;

    //Arch Type:
    if (m == 1)
        cout << "\nArchitecture Type: " << IAcpu.getArchType() << endl;
    else
        cout << "\nArchitecture Type: " << Acpu.getArchType() << endl;

    //Setting CPU
    if (m == 1)
    {
        IAcpu.setCPU(IAcpu.getArchType());
        IAcpu.setSelected(1);
    }
    else
    {
        Acpu.setCPU(IAcpu.getArchType());
        Acpu.setSelected(1);
    }

    //Processor
    if (m == 1)
    {
        cout << "\nChoose one of the following processors:\n"
            << "1. Core i3\n"
            << "2. Core i5\n"
            << "3. Core i7\n"
            << "4. Core i9\n";
        while (1)
        {
            cin >> t;
            if (t >= 1 && t <= 4)
                break;
            else
                cout << "Select only between 1 & 4: ";
        }
        IAcpu.setProcessorType(t);
    }
    else
    {
        cout << "\nChoose one of the following processors:\n"
            << "1. M1\n"
            << "2. M1 Pro\n"
            << "3. M1 Max\n";
        while (1)
        {
            cin >> t;
            if (t >= 1 && t <= 3)
                break;
            else
                cout << "Select only between 1 & 3: ";
        }
        Acpu.setProcessorType(t);
    }

    //Price:
    p = 28000 * t;
    if (m == 1)
        IAcpu.setPrice(p);
    else
        Acpu.setPrice(p);
}

void ComputerAssembly::createComputer(int m)
{
    if (m == 1)
        computer.setComputer(physicalmemory, motherboard, IAcpu);
    else
        computer.setComputer(physicalmemory, motherboard, Acpu);
}

void ComputerAssembly::createMotherBoard()
{
    int nop = 0,    //No of ports
        min = 5,
        maxlaptop = 10,
        maxpc = 18;

    //Number of Ports:
    cout << "\nHow many ports do you want? (Min = " << min << ", Max = " << maxlaptop << "(for Laptop), " << maxpc << "(for PC))\nNo. of Ports: ";
    while (1)
    {
        cin >> nop;
        if (nop >= min)
        {
            if ((DeviceType == laptop || DeviceType == maclaptop) && nop <= maxlaptop)
                break;
            else if ((DeviceType == pc || DeviceType == macpc) && nop <= maxpc)
                break;
            else
                cout << "\nChoose within the range\nMin = " << min << ", Max = " << maxlaptop << "(for Laptop), " << maxpc << "(for PC) \nNo. of Ports: ";
        }
        else
            cout << "\nChoose within the range\nMin = " << min << ", Max = " << maxlaptop << "(for Laptop), " << maxpc << "(for PC) \nNo. of Ports: ";
    }

    //Mother Board
    motherboard.setMainMemory(mainmemory);
    motherboard.setNumOfPorts(nop);

    //Types of Ports:
    string* typesofports = new string[nop];
    //                           0              1              2           3             4             5            6            
    //* ptype = new string[7]{ "VGI Port", "Charging Port", "USB Port", "HDMI Port", "USB-C Port", "AUDIO Port", "LAN Port" };
    int p = 0, index = 0;

    cout << "Default Ports:\n"
        << "1. " << motherboard.getP_Types(1)
        << "\n2. " << motherboard.getP_Types(5)
        << "\n3. " << motherboard.getP_Types(2)
        << "\n4. " << motherboard.getP_Types(2)
        << "\n\nSelect the rest of the ports. If you dont want to add that port choose None(if option available else it's necessary).\n";

    typesofports[index++] = motherboard.getP_Types(1);
    typesofports[index++] = motherboard.getP_Types(5);
    typesofports[index++] = motherboard.getP_Types(2);
    typesofports[index++] = motherboard.getP_Types(2);
    cout << "\nPorts left = " << nop - index << endl;
    cout << "\nWhich one do you want:\n"
        << "1. VGI Port\n2. HDMI Port\n3. Both\nEnter Port: ";
    while (1)
    {
        cin >> p;
        if (p >= 1 && p <= 3)
        {
            if (p == 3 && (index < nop - 1))
                break;
            else if (p >= 1 && p <= 2 && index < nop)
                break;
            else
                cout << "Select only 1 or 2(Space not available for both): ";
        }
        else
        {
            cout << "Choose only 1, 2 or 3: ";
        }
    }
    if (p == 1)
        typesofports[index++] = motherboard.getP_Types(0);
    else if (p == 2)
        typesofports[index++] = motherboard.getP_Types(3);
    else
    {
        typesofports[index++] = motherboard.getP_Types(0);
        typesofports[index++] = motherboard.getP_Types(3);
    }

    while (index < nop)
    {
        //USB-C Port:
        cout << "\nPorts left = " << nop - index << endl;
        p = 0;
        if (index < nop)
        {
            cout << "Select any one option: "
                << "\n1. One USB-C Port\n2. Two USB-C Ports\n3. None\nOption: ";
            while (1)
            {
                cin >> p;
                if (p >= 1 && p <= 3)
                {
                    if (p == 2 && (index < nop - 1))
                        break;
                    else if (p == 1 && (index < nop))
                        break;
                    else if (p == 3)
                        break;
                    else
                        cout << "Can't add port (Space not enough): ";
                }
                else
                {
                    cout << "Choose only 1, 2 or 3: ";
                }
            }
            if (p == 1)
                typesofports[index++] = motherboard.getP_Types(4);
            else if (p == 2)
            {
                typesofports[index++] = motherboard.getP_Types(4);
                typesofports[index++] = motherboard.getP_Types(4);
            }
            else
            {
            }
        }
        else
            break;

        //LAN Port:
        cout << "\nPorts left = " << nop - index << endl;
        p = 0;
        if (index < nop)
        {
            cout << "Select any one option: "
                << "\n1. One LAN Port\n2. Two LAN Ports\n3. None\nOption: ";
            while (1)
            {
                cin >> p;
                if (p >= 1 && p <= 3)
                {
                    if (p == 2 && (index < nop - 1))
                        break;
                    else if (p == 1 && (index < nop))
                        break;
                    else if (p == 3)
                        break;
                    else
                        cout << "Can't add port (Space not enough): ";
                }
                else
                {
                    cout << "Choose only 1, 2 or 3: ";
                }
            }
            if (p == 1)
                typesofports[index++] = motherboard.getP_Types(6);
            else if (p == 2)
            {
                typesofports[index++] = motherboard.getP_Types(6);
                typesofports[index++] = motherboard.getP_Types(6);
            }
            else
            {
            }
        }
        else
            break;

        //Audio Ports:
        cout << "\nPorts left = " << nop - index << endl;
        p = 0;
        if (index < nop)
        {
            cout << "Select any one option: "
                << "\n1. One AUDIO Port\n2. Two AUDIO Ports\n3. None\nOption: ";
            while (1)
            {
                cin >> p;
                if (p >= 1 && p <= 3)
                {
                    if (p == 2 && (index < nop - 1))
                        break;
                    else if (p == 1 && (index < nop))
                        break;
                    else if (p == 3)
                        break;
                    else
                        cout << "Can't add port (Space not enough): ";
                }
                else
                {
                    cout << "Choose only 1, 2 or 3: ";
                }
            }
            if (p == 1)
                typesofports[index++] = motherboard.getP_Types(5);
            else if (p == 2)
            {
                typesofports[index++] = motherboard.getP_Types(5);
                typesofports[index++] = motherboard.getP_Types(5);
            }
            else
            {
            }
        }
        else
            break;

        //HDMI Port:
        cout << "\nPorts left = " << nop - index << endl;
        p = 0;
        if (index < nop)
        {
            cout << "Select any one option: "
                << "\n1. One HDMI Port\n2. Two HDMI Ports\n3. None\nOption: ";
            while (1)
            {
                cin >> p;
                if (p >= 1 && p <= 3)
                {
                    if (p == 2 && (index < nop - 1))
                        break;
                    else if (p == 1 && (index < nop))
                        break;
                    else if (p == 3)
                        break;
                    else
                        cout << "Can't add port (Space not enough): ";
                }
                else
                {
                    cout << "Choose only 1, 2 or 3: ";
                }
            }
            if (p == 1)
                typesofports[index++] = motherboard.getP_Types(3);
            else if (p == 2)
            {
                typesofports[index++] = motherboard.getP_Types(3);
                typesofports[index++] = motherboard.getP_Types(3);
            }
            else
            {
            }
        }
        else
            break;

        //VGI Port:
        cout << "\nPorts left = " << nop - index << endl;
        p = 0;
        if (index < nop)
        {
            cout << "Select any one option: "
                << "\n1. One VGI Port\n2. Two VGI Ports\n3. None\nOption: ";
            while (1)
            {
                cin >> p;
                if (p >= 1 && p <= 3)
                {
                    if (p == 2 && (index < nop - 1))
                        break;
                    else if (p == 1 && (index < nop))
                        break;
                    else if (p == 3)
                        break;
                    else
                        cout << "Can't add port (Space not enough): ";
                }
                else
                {
                    cout << "Choose only 1, 2 or 3: ";
                }
            }
            if (p == 1)
                typesofports[index++] = motherboard.getP_Types(0);
            else if (p == 2)
            {
                typesofports[index++] = motherboard.getP_Types(0);
                typesofports[index++] = motherboard.getP_Types(0);
            }
            else
            {
            }
        }
        else
            break;

        //USB Ports
        cout << "\nPorts left = " << nop - index << endl;
        p = 0;
        if (index < nop)
        {
            cout << "How many USB Ports? "
                << "Amount (Less than or equal to " << nop - index << ") : ";
            while (1)
            {
                cin >> p;
                if (index < nop)
                    break;
                else
                    cout << "Space not enough\n"
                    << "Choose in given amount range (Less than or equal to " << nop - index << "): ";
            }
            for (int i = 0; i < p; ++i)
                typesofports[index++] = motherboard.getP_Types(2);
        }
        else
            break;
    }
    //Setting Ports:
    motherboard.setMotherBoard(mainmemory, nop);
    for (int i = 0; i < nop; ++i)
    {
        for (p = 0; p < 7 && !(typesofports[i] == motherboard.getP_Types(p)); ++p); //To find baud rate

        motherboard.setPorts(i, motherboard.getP_BaudRates(p), typesofports[i]);
    }

    motherboard.setPrice(250 * nop);
}

inline ComputerAssembly::~ComputerAssembly()
{
    delete[] devicetype;
}
