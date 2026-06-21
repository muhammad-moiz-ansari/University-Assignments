#include <iostream>
using namespace std;

int main()
{
    float a, b;
    cout << "Enter first number: ";
    cin >> a;
    cout << "Enter second number: ";
    cin >> b;

    char ch;
    cout << "Choose operation (+, -, *, /, %): ";
    cin >> ch;

    cout << "\nResult: ";
    if(ch == '+')
        cout << a + b;
    else if(ch == '-')
        cout << a - b;
    else if(ch == '*')
        cout << a * b;
    else if(ch == '/')
        cout << a / b;
    else if(ch == '%')
        cout << a % b;
    else
        cout << "-\nInvalid input";
    cout  << endl;
    return 0;
}