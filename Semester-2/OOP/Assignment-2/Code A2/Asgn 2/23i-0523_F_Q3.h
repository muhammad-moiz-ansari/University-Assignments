/*
        Your Name: Muhammad Moiz Ansari
        Your Roll#: 23i-0523
        Your Section: BS(CS)-F
        Assignment # 2
*/

#pragma once
#include <iostream>
using namespace std;

class CAList
{
    const int ksize = 7, vsize = 6;   //Max sizes
    int k_index = 0,    //To keep track of keys index
        * v_index = NULL,     //To keep track of values index
        keys = 0, * values = NULL;    //To keep track of size of array (How many keys or values of a key are present)
    bool* b_key = NULL;      //To keep track of the key in which add values

    string** arr = NULL;

public:
    CAList();

    CAList(const CAList&);

    CAList& operator=(CAList&);

    CAList& operator[](string);

    CAList& operator=(string);

    CAList& operator+=(string);

    CAList& operator+(CAList);

    CAList& operator+=(CAList);

    void remove_key(CAList&, int);

    void remove_value(CAList&, int);

    CAList& operator-(CAList);

    CAList& operator-=(CAList);

    CAList& operator-=(string);

    friend ostream& operator<<(ostream& output, const CAList& list);

    ~CAList();
};

ostream& operator<<(ostream& output, const CAList& list);