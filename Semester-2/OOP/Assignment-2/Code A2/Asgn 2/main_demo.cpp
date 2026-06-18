#include <iostream>
#include "23i-0523_F_Q3.h"
using namespace std;

int main() {

    CAList tt, tt2, tt3, tt4, tt5, tt6;
    cout << tt << endl; //should be empty.

    //name entry
    tt["OS"] = "Ms. Rabail";
    tt["OS"] += "Mr.Shehryar";
    tt["OS"] = "Dr. Faisal Cheema";
    tt["OS"] = "Mr. M. Aadil Ur Rehman";
    tt["OS"] = "Mr. M. Aadil Ur Rehman";    //repetition in same course. shouldn't add.
    tt["OS"] += "Ms. Maryam Shahbaz";
    tt["OS"] += "Dr. Adnan Tariq";
    tt["OS"] += "6 limit crossed";

    tt["DS"] += "Ms. Rabail";
    tt["DS"] += "Mr. Majid Hussain";
    tt["DS"] = "Ms. Noor ul Ain";

    tt2["OS"] = "Dr. Ariyan";

    tt2["DS"] += "Ms. Rabail";
    tt2["DS"] += "Ms. Noor ul Ain";
    tt2["DS"] = "Dr. Syed Qaiser Ali Shah";

    cout << "\nTT:" << endl;
    cout << tt << endl;

    cout << "\nTT2:" << endl;
    cout << tt2 << endl;

    /* Output:
    TT:
    [ OS: {Ms. Rabail, Mr.Shehryar, Dr. Faisal Cheema, Mr. M. Aadil Ur Rehman, Ms. Maryam Shahbaz, Dr. Adnan Tariq}
      DS: {Ms. Rabail ,Mr. Majid Hussain, Ms. Noor ul Ain} ]
    TT2:
    [
      OS: {Dr. Ariyan}
      DS: {Ms. Rabail,Ms. Noor ul Ain, Dr. Syed Qaiser Ali Shah} ]
    */

    //name discard
    tt["OS"] -= "Mr. M. Aadil Ur Rehman";

    //name does not exist, discard
    tt["OS"] -= "i do not exist";

    //Course does not exist, discard
    tt["i do not exist"] -= "Ms. Rabail";

    cout << "\nTT:" << endl;
    cout << tt << endl;

    /* Output:
    TT:
    [ OS: {Ms. Rabail, Mr.Shehryar, Dr. Faisal Cheema, Ms. Maryam Shahbaz, Dr. Adnan Tariq}
      DS: {Ms. Rabail ,Mr. Majid Hussain, Ms. Noor ul Ain} ]

    */

    tt["OS"] += "Mr. M. Aadil Ur Rehman";

    cout << "\n--Addition of two CALists--" << endl;
    tt3 = tt + tt2;
    cout << "TT3:" << endl;
    cout << tt3 << endl;

    /* Output:
    TT3:
    [ OS: {Ms. Rabail, Mr.Shehryar, Dr. Faisal Cheema, Ms. Maryam Shahbaz, Dr. Adnan Tariq, Mr. M. Aadil Ur Rehman}
      DS: {Ms. Rabail ,Mr. Majid Hussain, Ms. Noor ul Ain, Dr. Syed Qaiser Ali Shah} ]

    */

    cout << "\n--Subtraction of two CALists--" << endl;
    tt4 = tt3 - tt;
    cout << "TT4:" << endl;
    cout << tt4 << endl;

    /* Output:
    TT4:
    [ DS: {Dr. Syed Qaiser Ali Shah} ]
    */

    tt5 = tt - tt;
    cout << "\nTT5:" << endl;
    cout << tt5 << endl; //should be empty.

    tt5["1"] = "1";
    tt5["2"] = "1";
    tt5["3"] = "1";
    tt5["4"] = "1";
    tt5["5"] = "1";
    tt5["6"] = "1";
    tt5["7"] = "1";
    tt5["8"] += "should not add this value.";
    cout << "\nTT5:" << endl;
    cout << tt5 << endl;

    return 0;
}