#include <iostream>
#include "23i-0523_Moiz Ansari_Q2.h"
using namespace std;

int main()
{
	HOD hod;
	Teacher teacher;
	Security sec;
	GateKeeper gatekeeper;

	hod.input();
	teacher.input();
	sec.input();
	gatekeeper.input();

	hod.print_detail();
	teacher.print_detail();
	sec.print_detail();
	gatekeeper.print_detail();

	return 0;
}