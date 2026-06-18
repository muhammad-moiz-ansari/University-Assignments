//#include <iostream>
//#include "23i-0523_F_Q3.h"
//using namespace std;
//
//int main() {
//
//	CAList tt, tt2, tt3, tt4, tt5, tt6; // assume CAList is the name of class
//	// operator[] is used to get "entry" against given "key" from CAList and
//
//	tt["OOP"] = "Dr.Ali";
//	tt["OOP"] = "Mr.Shehryar";
//	tt["OOP"] = "Ms.Hida";
//	tt["OOP"] = "Mr.Shams";
//	tt["LD"] += "Dr.Mehwish";
//	tt["LD"] -= "Dr.Mehwish";
//	tt["DLD"] = "Mr.Amir";
//	tt["DLD"] = "Mr.Shams";
//	tt["DLD"] = "Dr.Mehwish";
//	tt["LD"] += "Dr.Mehwish";
//	tt["LD"] -= "Dr.Mehwish";
//
//	cout << "tt is :\n" << tt;
//
//
//
//	tt2["Algo"] = "Mr.Owais";
//	tt2["OOP"] = "Mr.Shehryar";
//	tt2["Pak Stds"] = "Mr.Ajmal";
//	tt2["Pak Stds"] += "Ms.Gul";
//	tt2["Pak Stds"] += "Ms.Gul";
//	tt2["Pak Stds"] = "Ms.Memoona";
//	tt2["slamiat"] = "Dr.Tayab";
//	tt2["Isamiat"] += "Ms.Sobia";
//	tt2["Islaiat"] = "Mr.Usman";
//	tt2["Isamiat"] += "Ms.Gul";
//	tt2["Islamat"] += "Mr.Anas";
//	tt2["slamiat"] = "Dr.Tayb";
//	tt2["slamiat"] = "Dr.Taya";
//	tt2["slamiat"] = "Dr.ayab";
//
//
//	tt3["Pak Stds"] += "Ms.Gul";
//	tt3["Pak Stds"] = "Ms.Memoona";
//	tt3["Islamiat"] = "DrTayab";
//
//	cout << "\ntt2 is :\n" << tt2 << endl;
//
//	tt2["OOP"] -= "Mr.Shehryar";
//	tt2["Islamiat"] -= "Ms.Gul";
//
//	tt3 = tt + tt2 - tt3;
//
//	cout << "\ntt3 is :\n" << tt3 << endl << endl;
//
//	tt4["Islamiat"] = "Dr.Tayab";
//	tt4["Islamiat"] += "Msobia";
//	tt4["Islamiat"] = "Mr.Usman";
//	tt4["Islamiat"] += "Ms.ul";
//	tt4["Islamiat"] += "Mrnas";
//	tt2["Islamiat"] = "D.Tayab";
//	tt2["Islamiat"] += "Mobia";
//	tt2["Islamiat"] = "Mr.sman";
//	tt2["Islamiat"] += "Ms.l";
//	tt2["Islamiat"] += "Mrnas";
//
//	tt4 = tt4 + tt2 - tt;
//
//	cout << "\ntt4 is :\n" << tt4 << endl << endl;
//
//	tt5 = tt3 - tt4 + tt2;
//
//	cout << "\ntt5 is :\n" << tt5 << endl << endl;
//
//	tt6 = tt3 - tt4 - tt5 = tt6;
//
//	cout << "tt6 is :\n" << tt6 << endl << endl;
//}