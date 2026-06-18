#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()


{
	srand(time(0));
	
	int a=(rand()%100)-50;
	cout<<a<<endl;
	return 0;
}

