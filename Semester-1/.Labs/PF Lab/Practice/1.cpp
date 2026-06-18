//answer must be in floating point
#include <iostream>
#include<cmath>
using namespace std;
int main()
{
// int value1=3, value2, value3;
double value1=3,value2,value3; // correction
value2 = 3 * pow(value1, 2.0);
//(double)value3 = 3 + value2 /2-1; //error: lvalue required as left operand of assignment // invalid typecasting
value3= 3 + (double)value2/2-1; //correction
cout << value3 << endl;
return 0;}
