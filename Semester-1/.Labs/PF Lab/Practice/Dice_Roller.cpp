#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;

int main()
{
	unsigned seed=time(0);
	const int min=1;
	const int max=6;
	
	srand(seed);
	int d1=(rand() % (max-min+1))+min;
	int d2=(rand() % (max-min+1))+min;
	
	cout<<"Dice is rolling ";
	cout.flush();
	usleep(300000);
	cout<<". ";
	cout.flush();
	usleep(300000);
	cout<<". ";
	cout.flush();
	usleep(300000);
	cout<<"."<<endl;
	cout.flush();
	usleep(300000);
	
	cout<<"          _"<<endl;
	cout<<"Dice 1 : |"<<d1<<"|"<<endl;
	cout<<"          -"<<endl<<endl;
	
	cout<<"          _"<<endl;
	cout<<"Dice 2 : |"<<d2<<"|"<<endl;
	cout<<"          -"<<endl;
	
	return 0;
}
