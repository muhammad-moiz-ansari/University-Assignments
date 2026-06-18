#pragma once
#include <iostream>
using namespace std;

//--------- Question-1 -----------

int getCharCount(char* ptr, char c)
{
    static int count;
    static int i = 0;
    if (i == 0)
        count = 0;

    if (*(ptr + i) == c)
        ++count;

    if (*(ptr + i) == '\0')
    {
        i = 0;
        return count;
    }
    ++i;
    getCharCount(ptr, c);
}

int getCharCount(char* ptr, char c, int i, int count)
{
    if (*(ptr + i) == c)
        count++;
    if (*(ptr + i) == '\0')
        return count;
    getCharCount(ptr, c, ++i, count);
}

//--------- Question-2 -----------

//string reverseWord(string word, int start, int end)
//{
//    if (start <= end)
//    {
//        char a, b;
//        b = word[end];
//        a = word[start];
//        word[start++] = b;
//        word[end--] = a;
//        return reverseWord(word, start, end);
//    }
//
//    return word;
//}
string reverseWord(string str, int start, int end)
{
    char a, b;
    a = str[start];
    b = str[end];
    str[end] = a;
    str[start] = b;
    if (start < end)
        return reverseWord(str, ++start, --end);
    else
        return str;
}

//--------- Question-3 -----------
//int fibonacci(int n)
//{
//    static int a = -1;
//    static int b = 1;
//    static int i = 0;
//    int c = a + b;
//    a = b;
//    b = c;
//
//
//    if (n == i)
//    {
//        i = 0;
//        a = -1;
//        b = 1;
//        return c;
//    }
//    ++i;
//    fibonacci(n);
//
//}
int fibonacci(int n)
{
    static int a = -1, b = 1, i = 0;
    int c;

    c = a + b;
    a = b;
    b = c;

    if (n == i)
    {
        a = -1;
        b = 1;
        i = 0;
        return c;
    }
    ++i;

    fibonacci(n);
}
void printFibonacci(int n)
{
    static int a = -1, b = 1, i = 0;
    int c;

    c = a + b;
    a = b;
    b = c;

    if (i < n)
    {
        cout << c << "  ";
    }
    else
    {
        a = -1;
        b = 1;
        i = 0;
        cout << endl;
        return;
    }
    ++i;
    printFibonacci(n);
}

//--------- Question-4 -----------
//
//void star(int n)
//{
//    if (n > 0)
//    {
//        cout << "*";
//        --n;
//        star(n);
//
//    }
//}
//
//void q4(int n)
//{
//    if (n > 0)
//    {
//        star(n);
//        --n;
//        cout << endl;
//        q4(n);
//
//    }
//}
//
////--------- Question-5 -----------
//
//void star2(int i, int n, int up)
//{
//    //static int up = UP;
//    static int N = n;
//    //int i = 1;
//    if (up <= N)
//    {
//        if (i <= up)
//        {
//            cout << "*";
//            star2(++i, n, up);
//        }
//    }
//
//}
//
//void spaces(int i)
//{
//    if (i > 0)
//    {
//        cout << " ";
//        i -= 1;
//        spaces(i);
//    }
//}
//
//void diamond_pattern(int n1, int n2)
//{
//    static int UP = 1;
//
//    if (n1 > 0)
//    {
//        spaces(n1 / 2);
//        star2(1, n2, UP);
//        spaces(n1 / 2);
//        n1 -= 2;
//        UP += 2;
//
//        cout << "\n";
//        diamond_pattern(n1, n2);
//
//        static int down = UP - 2;
//
//
//        down -= 2;
//        ++n1;
//        cout << " ";
//        spaces(n1 / 2);
//        star2(1, n2, down);
//        spaces(n1 / 2);
//
//        cout << endl;
//    }
//}


// Q-4:
void star4(int i)
{
    if (i > 0)
    {
        cout << "* ";
        star4(--i);
    }
}

void q4(int n)
{
    if (n > 0)
    {
        star4(n);
        cout << endl;
        q4(--n);
    }
}

//Q-5:

void space5(int i)
{
    if (i > 0)
    {
        cout << " ";
        space5(--i);
    }
}

void star5(int i)
{
    if (i > 0)
    {
        cout << "*";
        star5(--i);
    }
}

void diamond_pattern(int n1, int n2)
{
    if (n1 > 0)
    {
        space5(n1 / 2);
        star5(n2 - n1 + 1);
        cout << endl;
        n1 -= 2;
        diamond_pattern(n1, n2);
    }

    //cout << "\b\b\b\b\b\b";
    n1 += 4;

    space5(n1 / 2);
    if (n1 >= 0)
        star5(n2 - n1 + 1);
    cout << endl;

}