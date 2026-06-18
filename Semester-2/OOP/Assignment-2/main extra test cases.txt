/*
		Your Name: Muhammad Moiz Ansari
		Your Roll#: 23i-0523
		Your Section: BS(CS)-F
		Assignment # 2
*/

#include <iostream>
#include "23i-0523_F_Q3.h"
using namespace std;

int main()
{
	CAList t1, t2, t3, tt, tt2, tt3, tt4; // assume CAList is the name of class
	////done operator[] is used to get "entry" against given "key" from CAList and can be used in following context with operator= to 
	// create/refresh an entry 
	
	t1["OOP"] = "Dr.Ali";
	t1["OOP"] = "Mr.Shehryar";
	t1["OOP"] = "Ms.Hida";
	t1["OOP"] = "Mr.Shams";
	t1["OOP"] = "Mr.Amir";
	t1["OOP"] = "Mr.X";
	t1["OOP"] = "Dr.Mehwish";
	t1["DLD"] = "Mr.Amir";
	t1["DLD"] = "Mr.Shams";
	t1["DLD"] = "Dr.Mehwish";
	t1["Algo"] = "Mr.Owais";
	t1["Pak Stds"] = "Mr.Ajmal";
	t1["Islamiat"] = "Dr.Tayab";
	t1["MVC"] = "Dr.Imran";
	t1["Exp Wr"] = "Ms.Rafiah";
	t1["Exp Wr Lab"] = "Ms.Sumaiyyah";
	cout<<"t1:\n" << t1;
	
	tt["OOP"] = "Dr.Ali";
	tt["OOP"] = "Mr.Shehryar";
	tt["OOP"] = "Ms.Hida";
	tt["OOP"] = "Mr.Shams";
	tt["DLD"] = "Mr.Amir";
	tt["DLD"] = "Mr.Shams";
	tt["DLD"] = "Dr.Mehwish";
	cout << "tt:\n" << tt;

	//output should look like: [ OOP : { Dr.Ali, Mr.Shehryar, Ms.Hida, Mr.Shams}, 
	//							 DLD : { Mr.Amir, Mr.Shams, Dr.Mehwish } ]

////done operator+= with an "entry" is used to add new "value" against a given "key".
// if entry with given "key" does not exist then new entry is created in CAList.
////done Following operators += and = perform the same operation

	tt2["Algo"] = "Mr.Owais";			////done:add a check to check if a key or value already exists so skip that
	tt2["Algo"] += "Mr.Owais";
	tt2["OOP"] = "Mr.Shehryar";
	tt2["Pak Stds"] = "Mr.Ajmal";
	tt2["Pak Stds"] += "Ms.Gul";
	tt2["Pak Stds"] = "Ms.Memoona";
	tt2["Islamiat"] = "Dr.Tayab";
	tt2["Islamiat"] += "Ms.Sobia";
	tt2["Islamiat"] = "Mr.Usman";
	tt2["Islamiat"] += "Ms.Gul";
	tt2["Islamiat"] += "Mr.Anas";
	cout << "tt2:\n" << tt2;

// following statement creates a new entry in CAList, and then adds values to it
// operator+ is also used to add two (CAList)s and return a new CAList.
////done: operator= is used to assign one List to another(deep copy). 

	tt3 = tt + tt2; ////done: tt3 now looks like the CAList in figure above!(same as set union operation)
	cout << "tt3:\n" << tt3;

	t2 = tt;
	t2 += tt2;
	cout << "t2:\n" << t2;

/* At this stage tt, tt2, and tt3 look like following respectively:
tt:

[ OOP : { Dr.Ali, Mr.Shehryar, Ms.Hida, Mr.Shams},
DLD : { Mr.Amir,Mr.Shams,Dr.Mehwish } ]

tt2:

[ Algo : { Mr.Owais },
OOP : {Mr.Shehryar },
Pak Stds : { Mr.Ajmal,Ms.Gul,Ms.Memoona} ,
Islamiat : { Dr.Tayab,Ms.Sobia,Mr.Usman,Ms.Gul,Mr.Anas }]

tt3:

[ OOP : { Dr.Ali, Mr.Shehryar, Ms.Hida, Mr.Shams},
DLD : { Mr.Amir, Mr.Shams, Dr.Mehwish },
Algo : {Mr.Owais },
Pak Stds : { Mr.Ajmal, Ms.Gul, Ms.Memoona} ,
Islamiat : { Dr.Tayab, Ms.Sobia, Mr.Usman, Ms.Gul, Mr.Anas }]*/

	tt4 = tt - tt2; //This Operation will work similar to the set difference operation
	cout << "tt4:\n" << tt4;

	////done:operator-=
	t3 = tt;
	t3 -= tt2;
	cout << "t3:\n" << t3;

/*
tt4 :

[OOP:{ Dr.Ali, Ms.Hida, Mr.Shams},
DLD : { Mr.Amir, Mr.Shams, Dr.Mehwish }] 
*/

	return 0;
}