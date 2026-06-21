#include <iostream>
using namespace std;

int main()
{
    float C;
    cout<<"Enter temperature in Celsius: ";
    cin>>C;

    float F = (C * (9.0/5));

    cout<<"Temperature in Fahrenhiet: "<<F<<"°F\n";

    return 0;
}