/*    Problem 7

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 1

*/

#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    unsigned short int N, n ,a ; 
    cout<<"Enter a positive number : ";
    cin>>N;
    cout<<endl;
    
    //Calculating grey code
    
    a = N;
    a = a >> 1;
    n = N ^ a;
    
    //Printing Binary and grey code
    
    cout<<"Binary Code : "<<bitset<16>(N)<<endl<<endl;
    
    cout<<"Grey Code :   "<<bitset<16>(n)<<endl;
    
    return 0;
}


