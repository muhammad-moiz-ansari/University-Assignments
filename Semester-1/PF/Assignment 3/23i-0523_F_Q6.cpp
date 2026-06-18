/*    Problem 6

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 3

*/

#include <iostream>
using namespace std;

void order(int arr1[], int arr2[], int arr3[], int arrt[], int, int, int, int);

int main()
{ 
	int s1, s2, s3, st;
	
	cout<<"Enter the size of array 1: ";
	cin>>s1;
	cout<<"Enter the size of array 2: ";
	cin>>s2;
	cout<<"Enter the size of array 3: ";
	cin>>s3;
	
	st=s1+s2+s3;
	int arr1[s1], arr2[s2], arr3[s3], arrt[st];
	
	//Inputting arrays:
	
	cout<<"\nEnter positive values of elements of array 1: \n";
	for(int i=0; i<s1; ++i)
	{
		cout<<"Value "<<i+1<<" = ";
		cin>>arr1[i];
		if(arr1[i]<0)
		  --i;
	}
	
	cout<<"\nEnter positive values of elements of array 2: \n";
	for(int i=0; i<s2; ++i)
	{
		cout<<"Value "<<i+1<<" = ";
		cin>>arr2[i];
		if(arr2[i]<0)
		  --i;
	}
	
	cout<<"\nEnter positive values of elements of array 3: \n";
	for(int i=0; i<s3; ++i)
	{
		cout<<"Value "<<i+1<<" = ";
		cin>>arr3[i];
		if(arr3[i]<0)
		  --i;
	}
	cout<<endl;
	
	//Outputting arrays:
	
	cout<<"Array 1: ";
	for(int i=0; i<s1; ++i)
		cout<<arr1[i]<<"  ";
	cout<<endl;
	cout<<"Array 2: ";
	for(int i=0; i<s2; ++i)
		cout<<arr2[i]<<"  ";
	cout<<endl;
	cout<<"Array 3: ";
	for(int i=0; i<s3; ++i)
		cout<<arr3[i]<<"  ";
	cout<<endl;
	
	order(arr1, arr2, arr3, arrt, s1, s2, s3, st);
	
	
	
	
	return 0;
}

void order(int arr1[], int arr2[], int arr3[], int arrt[], int s1, int s2, int s3, int st)
{
	int ch[st], r1=0, r2=0, r3=0,
		t=0, c=0;
	int ar1[s1], ar2[s2], ar3[s3];
	
	//Making copy arrays:
	for(int i=0; i<s1; ++i)
		ar1[i]=arr1[i];
	for(int i=0; i<s2; ++i)
		ar2[i]=arr2[i];
	for(int i=0; i<s3; ++i)
		ar3[i]=arr3[i];
	
	//Putting -1,-2,-3 in copies of array:
	
	//Array 1:
	for(int i=0; i<s1; ++i)
	{
		for(int j=0; j<s1; ++j)
		{
			if(i==j)
			  continue;
			if(ar1[i]==ar1[j])
			{
			  ar1[i]=-1;
			  //ar1[j]=-1;
			}
		}
	}
	//Array 2:
	for(int i=0; i<s2; ++i)
	{
		for(int j=0; j<s2; ++j)
		{
			if(i==j)
			  continue;
			if(ar2[i]==ar2[j])
			{
			  ar2[i]=-2;
			  //ar2[j]=-2;
			}
		}
	}
	//Array 3:
	for(int i=0; i<s3; ++i)
	{
		for(int j=0; j<s3; ++j)
		{
			if(i==j)
			  continue;
			if(ar3[i]==ar3[j])
			{
			  ar3[i]=-3;
			  //ar3[j]=-3;
			}
		}
	}
	
	/*
	//For array 1 & 2:
	for(int i=0; i<st; ++i)
	{
		for(int j=0; j<st; ++j)
		{
			if(i==j)
			  continue;
			if(arr1[i]==arr2[j])
			{
			  ar1[i]=-12;
			  break;
			  r1=1;
			}
		}
		if(r1==1)
		{
		  continue;
		  r1=0;
		}
	}
	//For array 2 & 3:
	for(int i=0; i<st; ++i)
	{
		for(int j=0; j<st; ++j)
		{
			if(i==j)
			  continue;
			if(arr2[i]==arr3[j])
			{
			  ar2[i]=-23;
			  break;
			}
		}
		if(r2==1)
		{
		  continue;
		  r2=0;
		}
	}
	//For array 1 & 3:
	for(int i=0; i<st; ++i)
	{
		for(int j=0; j<st; ++j)
		{
			if(i==j)
			  continue;
			if(arr1[i]==arr3[j])
			{
			  ar3[j]=-13;
			  break;
			}
		}
		if(r3==1)
		{
		  continue;
		  r3=0;
		}
	}
	*/
	//For array 1, 2 & 3:
	for(int i=0; i<st; ++i)
	{
		for(int j=0; j<st; ++j)
		{
			for(int k=0; k<st; ++k)
			{
				if(i==j==k)
				  continue;
				if(arr1[i]==arr2[j]==arr3[k])
				{
				  ar3[k]=-123;
				  ch[t]=arr3[k];
				  ++t;
				}
			}
		}
	}
	
	
	//Making resultant array:
	int m=0;
	for(int i=0; i<s1; ++i, ++m)
		arrt[m]=ar1[i];
		
	for(int i=0; i<s1; ++i, ++m)
		arrt[m]=ar2[i];
		
	for(int i=0; i<s1; ++i, ++m)
		arrt[m]=ar3[i];
	
	//Sorting:
	int temp;
	
	for(int i=0; i<=st-1; ++i)
	{
		for(int j=0; j<st-i-1; ++j)
		{
			if(arrt[j]%2!=0)
			{
				temp=arrt[j];
				arrt[j]=arrt[j+1];
				arrt[j+1]=temp;
			}
		}
	}
	
	for(int i=0; i<=st-1; ++i)
	{
		for(int j=0; j<st-i-1; ++j)
		{
			if(arrt[j]>arrt[j+1])
			{
				temp=arrt[j];
				arrt[j]=arrt[j+1];
				arrt[j+1]=temp;
			}
		}
	}
	
	/*
	cout<<" 1: ";
	for(int i=0; i<s1; ++i)
		cout<<ar1[i]<<"  ";
	cout<<endl;
	cout<<" 2: ";
	for(int i=0; i<s2; ++i)
		cout<<ar2[i]<<"  ";
	cout<<endl;
	cout<<" 3: ";
	for(int i=0; i<s3; ++i)
		cout<<ar3[i]<<"  ";
	cout<<endl;
	*/
	
	cout<<"Resultant Array: ";
	for(int i=0; i<st; ++i)
		cout<<arrt[i]<<"  ";
	cout<<endl;
	
	
}
