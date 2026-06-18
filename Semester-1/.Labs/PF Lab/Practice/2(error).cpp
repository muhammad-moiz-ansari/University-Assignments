//Write a program that gives the bit of number entered

#include <iostream>
#include <bitset>

using namespace std;
int main()
{
	int N, num_bit, bitsize, a, b;
	
	cout<<"Enter a number : ";
	cin>>N;
	cout<<endl;
	cout<<"Enter the postion of bit required : ";
	cin>>num_bit;
	cout<<endl;
	
	bitsize = sizeof(N)*8;
	//a = ((N << (bitsize-num_bit)) >> (bitsize-1)) << (num_bit-1);
	a = ((N << (32-num_bit)) >> (32-1)) << (num_bit-1);
	
	
	cout<<bitset<32>(N)<<endl;
	cout<<bitset<32>(N << (32-num_bit))<<endl;
	cout<<bitset<32>((N << (32-num_bit)) >> (32-1))<<endl;
	
	cout<<bitset<1>(a)<<endl;
	
	
	return 0;
}
