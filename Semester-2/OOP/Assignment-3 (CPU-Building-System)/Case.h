#pragma once
#include <iostream>
#include <string>
using namespace std;

///////////////////////////
//                       //
//         Case          //
//                       //
///////////////////////////

class Case
{
private:
    string formFactor, color,
        * case_ffac = new string[3 + 3]{
                                        "ATX", "Micro ATX", "Mini ITX",  //For PC
                                        "Traditional Laptop", "Gaming Laptop", "Ultrabook" //For Laptop
    },
        * colors = new string[5]{ "Black", "Grey", "White", "Silver", "Gold" };
    double price;

public:
    //Constructors:
    Case();
    Case(int ffac, int col);

    //Setters:
    void setFormFactor(int ffac);
    void setColor(int col);
    void setPrice(float p);

    //Getters:
    string getFormFactor();
    string getFormFactor(int ind);
    string getColor();
    string getColor(int ind);
    double getPrice();
};

///////////////////////////
//                       //
//         Case          //
//                       //
///////////////////////////

//Constructors:
Case::Case()
{
    formFactor = "";
    color = "";
}
Case::Case(int ffac, int col)
{
    /*
    Form Factors:
    PC:
    1. ATX
    2. Micro ATX
    3. Mini ITX

    Laptop:
    4. Traditional Laptop
    5. Gaming Laptop
    6. Ultrabook
    */
    formFactor = case_ffac[col - 1];

    /*
    Colors:
    1. Black
    2. Grey
    3. White
    4. Silver
    5. Gold
    */
    color = colors[col - 1];
}

//Setters:
void Case::setFormFactor(int ffac)
{
    formFactor = case_ffac[ffac - 1];
}
void Case::setColor(int col)
{
    color = colors[col - 1];
}
void Case::setPrice(float p)
{
    price = p;
}

//Getters:
string Case::getFormFactor()
{
    return formFactor;
}
string Case::getFormFactor(int i)
{
    return case_ffac[i - 1];
}
string Case::getColor()
{
    return color;
}
string Case::getColor(int i)
{
    return colors[i - 1];
}
double Case::getPrice()
{
    return price;
}