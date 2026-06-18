#include<iostream>

using namespace std;

int main()
{
	int a[10]={2,34,64,64,2,2,3,3,3,3};
	int b[10];
	int large=0,ellarge=0,count=0;
	
	ellarge=a[0];
	
	for(int i=0; i<10; i++)
	{
		count=0;
		for(int j=0; j<10; j++)
		{
			if(a[i]==a[j])
			{
				count=count+1;
				ellarge=a[i];
			}
		}
		if(count>=large)
		large=count;
	}
	cout<<large<<endl<<ellarge<<endl;
}

