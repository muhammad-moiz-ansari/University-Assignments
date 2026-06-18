/*
        Your Name: Muhammad Moiz Ansari
        Your Roll#: 23i-0523
        Your Section: BS(CS)-F
        Assignment # 2
*/

#pragma once

struct Container
{
    char* name;
    int containerno;
    Container* link;
};

class Shop {
public:
    Container* start;

    // Default constructor
    Shop() { start = NULL; }

    // Copy Constructor
    Shop(const Shop& other);

    void add_Container(char* name, int containerindex); /*This member function will take the name and containerindex of
    Article as input parameter. It creates the Container instance. If the new Container instance is the first in the chain then
    the pointer “start“ will point to it. Otherwise a new instance is attached at the end of the existing chain.*/

    void print_Shop(); //It prints all the articles with their container number in the chain.

    void delete_Chain(int containerindex); /* This member function will take the containerindex of Article as input parameter.
    It deletes the mentioned containerindex from the chain of Shop instance. And rejoins the remaining chain.*/

    void Sort_Chain(); //It sort all the elements in the chain based upon their containerindex.

    void update_name_at_containerNumber(int containerindex, char* name);//Updates name of a container using its container no.
    
    void remove_Duplicate(); //It removes all the containers with same article in the chain.

    void findContainer(int containerindex);// It prints article name in the selected container.

    void findContainer(int containerindex1, int containerindex2);// It prints article name in the container number range.The range is inclusive
    
    ~Shop();
};