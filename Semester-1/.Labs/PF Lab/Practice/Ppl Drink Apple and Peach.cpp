#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	int N;
	float a, p, apple, peach;
	
	cout<<"Enter total number of people : ";
	cin>>N;
	
	apple = N * 0.58;   //58% of people drink apple juice
	peach = N * 0.42;  //42% of people drink peach juice
	
	cout<<fixed<<setprecision(2);
	cout<<"Number of people who drink apple juice : "<<apple<<endl;
	cout<<"Number of people who drink peach juice : "<<peach<<endl;
	
	return 0;
}
