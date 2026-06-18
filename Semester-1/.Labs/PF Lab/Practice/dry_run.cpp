#include <iostream>
using namespace std;

/*
void print(const int* const, int=2);

int main()
{
    int a[][3]={1,2,3};
  
    print(a[1]);
    print(a[2]);
    print(a[0]);
}
void print(const int* const a, int N)
{
    for(int i = 0; i < N; i++)
    cout << *(a+i) << endl;
    cout << endl;
}
*/

//int main()
//{
    //cout<<("apple"<"Apple")<<("allign">"all")<<("manor"<"manir")<<("man or">"manor");
    //cout<<('A'<"A");   //<-- Whats the error in this line
    
    /*
    void* vp;
    int a = 69;
    vp = &a;
    cout <<  (char*)vp << endl;
    cout << * (int*)vp << endl;
    cout << * (float*)vp << endl;
    */

    /*
    int* vp;
    float b = 6.9;
    vp = (int*)&b;
    cout << &b << endl;
    cout << &vp << endl;
    cout << (float*)vp << endl;
    cout << (float**)vp << endl;
    cout << (float***)vp << endl;
    cout << (float****)vp << endl;
    */
/*
void f2(int *p)
{
    int* x = new int;
    *x = 4;
    *p = *x;
    cout << *p << endl;
}

void f1(int *p)
{
    f2(p);
}

int main()
{
    int x = 2;
    int *p = &x;
    f1(p);
    cout << *p << endl;
    cout << x << endl;

    cout<<endl;

    return 0;
}*/

#include <iostream>
using namespace std;

int main()
{
    cout<<("apple">"Apple")<<("allign">"all")<<("manor">"manir")<<("man or">"manor");
    
    //1111
    return 0;
}