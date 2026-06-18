#include <iostream>
#include <string>
#include <iomanip>

#include "i230523_F_Q1.h"
using namespace std;

int main()
{
	//srand(time(0));

	Mythoria land(0, 50, 0, 0);

	Creature* dragon = new Dragon(5, "Toothless", 3, 30, 10, 20);
	Creature* hydra = new Hydra(5, 5, "Snake", 2, 28, 8, 40);

	cout << "Spawned:\n\n";
	dragon->Display();
	cout << endl;
	hydra->Display();


	cout << endl << endl << endl;


	dragon->BlowFlame(*hydra);
	hydra->injectPoison(*dragon);

	cout << "First Attack:\n\n";
	dragon->Display();
	cout << endl;
	hydra->Display();


	cout << endl << endl << endl;




	dragon->Slither(*hydra, land);
	hydra->Move(*dragon, hydra->getRange(), land);

	cout << "Attack after Moved:\n\n";
	dragon->BlowFlame(*hydra);
	hydra->injectPoison(*dragon);

	
	dragon->Display();
	cout << endl;
	hydra->Display();

	return 0;
}