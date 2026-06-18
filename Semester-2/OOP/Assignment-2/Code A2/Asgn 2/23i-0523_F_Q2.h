/*
        Your Name: Muhammad Moiz Ansari
        Your Roll#: 23i-0523
        Your Section: BS(CS)-F
        Assignment # 2
*/

#pragma once
#include <iostream>
using namespace std;

class String
{
    // think about the private data members
    char* s;

public:
    // provide definitions of following functions
    String(); // default constructor
    String(const char* str); // initializes the string with constant c-string
    String(const String&); // copy constructor to initialize the string from the existing string
    String(int x); // initializes a string of predefined size
    char* getdata(); //returns the string inside the object
    // Binary Operators // Sub - script Operators
    const char operator[](int i) const; // returns the character at index [x]
    //NOTE: in above [] operator functions if i=negative int value, print ith character from end of string e.g. in case of “LOOP”
    //      if i=-1 OR i=3, it should return ‘P’ similarly i = -4 OR i = 0, //return ‘L’

    // Arithmetic Operators
    String operator+(const String& str); // appends a String at the end of the String
    String operator+(const char& str); // appends a char at the end of the String
    String operator+(const char* str); // appends a String at the end of the String
    String operator-(const String& substr); //removes the substr from the String
    String operator-(const char& str); //removes all occurrences of char from the String
    String operator-(const char* str); //removes the str from the String

    // Assignment Operators
    String& operator=(const String&); // copies one String to another
    String& operator=(char*); // copies one c-string to another

    // Logical Operators
    bool operator==(const String&) const; // returns true if two Strings are equal
    bool operator==(const char*) const; // returns true if the c-string is equal to the String

    // Unary Operators 
    // Boolean Not Operator

    bool operator!(); // returns true if the String is empty

    // Function-Call Operators
    //If something is not found then return -1
    int operator()(char) const; // returns the first index of the character being searched
    int operator()(const String&) const; // returns the first index of the String being searched
    int operator()(const char*) const; // returns the index of the c-string being searched

    // Conversion Operator
    operator int() const; // returns the length of string
    ~String(); // destructor

    friend ostream& operator<<(ostream& output, const String& str); // outputs the string
    friend istream& operator>>(istream& input, String& str); // inputs the string

};

ostream& operator<<(ostream& output, const String& str); // outputs the string
istream& operator>>(istream& input, String& str); // inputs the string