#include <iostream>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int main()
{
	const int size = 30; 
	char arr[size];
	while(true)
	{
		cout<<"\nEnter a string: \n";
		read(0, arr, size);

		for(int i=0; i<size; ++i)
		{
			if(arr[i]=='\n')
				arr[i]='\0';
		}

		if(arr[0]=='e' && arr[1]=='x' && arr[2]=='i' && arr[3]=='t' && arr[4]=='\0')
			break;
		cout<<"String entered: \n";
		write(1, arr, size);
	}
	
	return 0;
}
