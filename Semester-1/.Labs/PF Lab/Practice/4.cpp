#include <iostream>
using namespace std;

int main()
{
	cout<<"\033[1m"<<"\033[31m";
	
    char arr1[]=" world";
    char arr3[]=" herem";
    char arr2[]={'h','e','l','l','o'};
    
    int size=0;
    for(int i=0; arr2[i]!='\0'; ++i)
        ++size;

	cout<<arr2<<" ";
	cout<<size<<endl;
        
    return 0;
}
