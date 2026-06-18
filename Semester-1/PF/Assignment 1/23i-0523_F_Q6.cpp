/*    Problem 6

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 1

*/

#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    unsigned int N, g1, g2, g3, key, c, n;
    cout<<"Enter a 32 bit positive integer : ";
    cin>>N;
    cout<<endl;
    
    //Seperating gate 1, gate 2, gate 3, constant.
    
    c=N;
    c=c>>24;
    
    g3=N;
    g3=g3<<8;
    g3=g3>>24;
    
    g2=N;
    g2=g2<<16;
    g2=g2>>24;
    
    g1=N;
    g1=g1<<24;
    g1=g1>>24;
    
    key=((g1^g2^g3)^c);	//Finding KEY
    
    //Printing gate 1, gate 2, gate 3, constant, key.
    
    cout<<"Entered Number(In bits):"<<bitset<32>(N)<<endl;
    cout<<"Gate-1 :   "<<bitset<8>(g1)<<endl;
    cout<<"Gate-2 :   "<<bitset<8>(g2)<<endl;
    cout<<"Gate-3 :   "<<bitset<8>(g3)<<endl;
    cout<<"Constant : "<<bitset<8>(c)<<endl;
    cout<<"KEY :      "<<bitset<8>(key)<<endl;

    return 0;
}

