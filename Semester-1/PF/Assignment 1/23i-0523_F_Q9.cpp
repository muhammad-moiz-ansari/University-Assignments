/*    Problem 9

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 1

*/

#include <iostream>
using namespace std;
int main()
{
    int a, b, c, d, max1, max2 = 0;

    //Taking input
    cout << "Enter four integers:" << endl;
    cin >> a >> b >> c >> d;
    cout << endl;

    //Calculating first maximum number
    max1 = (a >= b && a >= c && a >= d) ? a : ((b >= a && b >= c && b >= d) ? b : ((c >= a && c >= b && c >= d) ? c : d));

    cout << "Maximum Number : " << max1 << endl;

   //Calculating second maximum number
    max2 = (a == max1) ? (b > c && b > d) ? (max1 == b) ? ((c > d) ? c : d) : b : (c > b && c > d) ? (max1 == c) ? ((b > d) ? b : d) : c : (max1 == d) ?
        ((c > b) ? c : d) : d : (b == max1) ? (a > c && a > d) ? (max1 == a) ? (c > d) ? c : d : a : (c > b && c > d) ? (max1 == c) ? (b > d) ? b : d
        : c : (max1 == d) ? (c > a) ? c : a : d : (c == max1) ? (a > b && a > d) ? (max1 == a) ? (b > d) ? b : d : a : (b > a && b > d) ? (max1 == b) ?
        (a > d) ? a : d : b : (max1 == d) ? (b > a) ? b : a : d : (a > b && a > c) ? (max1 == a) ? (c > b) ? c : b : a : (b > a && b > c) ? (max1 == b) ?
        (c > a) ? c : a : b : c;

    cout << "Second Maximum Number : " << max2 << endl;

    return 0;
}

