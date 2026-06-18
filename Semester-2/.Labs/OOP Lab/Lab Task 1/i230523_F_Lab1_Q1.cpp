#include<iostream>
#include "Debugg.h"
using namespace std;
int main() {
    calculator('*', 5, 6);
    //  num1 = -5.00000000
    //  num2 = 6.00000000
    //  result = 30.0000000
    calculator('/', 25, -5);
    //  num1 = 25.0000000
    //  num2 = -5.00000000
    //  result = 5.00000000
    calculator('+', 100, 6);
    //  num1 = 1000.00000000
    //  num2 = 6.00000000
    //  result = 106.00000000
    calculator('-', 15, 3);
    //  num1 = 15.0000000
    //  num2 = 13.0000000
    //  result = 18.0000000
}