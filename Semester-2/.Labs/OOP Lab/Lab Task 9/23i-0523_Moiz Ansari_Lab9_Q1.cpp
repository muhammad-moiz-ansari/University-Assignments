#include <iostream>
#include "23i-0523_Moiz Ansari_Q1.h"
using namespace std;

int main()
{
	string item1 = "Imran Shehzad Cosmetics", item2 = "FAST Anti-depressants";
	Item a(item1, 30, 100), b(item2, 20, 200), c(item1, 20, 100);

	!(++a); !a;
	!(a++); !a;

	!(--a); !a;
	!(a--); !a;

	a += 10; !a;
	b -= 5; !b;

	cout << "Total price = " << ~a << endl;

	a + c;
	a + b;
	!a;

}