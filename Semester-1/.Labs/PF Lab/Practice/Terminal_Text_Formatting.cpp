#include <iostream>
using namespace std;

int main()
{
	//cout<<"\033[1m";	//bold
	
    char arr1[]=" world";
    char arr3[]=" herem";
    char arr2[]={'h','e','l','l','o'};
    
    int size=0;
    for(int i=0; arr2[i]!='\0'; ++i)
        ++size;
    
    for(int i=0; i<110; ++i)
    {
		cout<<"\033["<<i<<"m";
		cout<<i<<": "<<arr2<<" ";
		cout<<size<<endl;
		cout<<"\033[0m";
	}
    return 0;
}
