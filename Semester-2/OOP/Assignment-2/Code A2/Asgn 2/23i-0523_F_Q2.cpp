/*
        Your Name: Muhammad Moiz Ansari
        Your Roll#: 23i-0523
        Your Section: BS(CS)-F
        Assignment # 2
*/

#include "23i-0523_F_Q2.h"
using namespace std;

String::String()
{
    s = NULL;
}

String::String(const char* str)
{
    int size = 0;
    
    for (; str[size] != '\0'; ++size);

    ++size;

    s = new char[size];
    
    for (int i = 0; i < size; ++i)
        s[i] = str[i];
}

String::String(const String& strc)
{   
    int size = 0;

    for (; strc[size] != '\0'; ++size);

    ++size;

    s = new char[size];

    for (int i = 0; i < size; ++i)
        s[i] = strc[i];
}

String::String(int x)
{
    s = new char[x];
    *s = '\0';
}

char* String::getdata()
{
    return s;
}

const char String::operator[](int i) const
{
    int size = 0;
    char* temp = s;

    for (; s[size] != '\0'; ++size);

    for (; i < 0; i += size);

    return s[i];
}

String String::operator+(const String& str)
{
    int s1 = 0, s2 = 0, Size = 0, index = 0;
    char* temp = NULL;

    for (; s[s1] != '\0'; ++s1);
    for (; str.s[s2] != '\0'; ++s2);

    Size = s1 + s2 + 1;
    temp = s;

    s = new char[Size];

    for (int i = 0; temp[i] != '\0'; ++i)
        s[index++] = temp[i];

    delete[] temp;

    for (int i = 0; str.s[i] != '\0'; ++i)
        s[index++] = str.s[i];

    s[index] = '\0';

    temp = NULL;

    return *this;
}

String String::operator+(const char& str)
{
    int s1 = 0, s2 = 1, Size = 0, index = 0;
    char* temp = NULL;

    for (; s[s1] != '\0'; ++s1);

    Size = s1 + s2 + 1;
    temp = s;

    s = new char[Size];

    for (int i = 0; temp[i] != '\0'; ++i)
        s[index++] = temp[i];

    s[index++] = str;
    s[index] = '\0';

    delete temp;

    return *this;
}

String String::operator+(const char* str)
{
    int s1 = 0, s2 = 0, Size = 0, index = 0;
    char* temp = NULL;

    for (; s[s1] != '\0'; ++s1);
    for (; str[s2] != '\0'; ++s2);

    Size = s1 + s2 + 1;
    temp = s;

    s = new char[Size];

    for (int i = 0; temp[i] != '\0'; ++i)
        s[index++] = temp[i];

    delete[] temp;

    for (int i = 0; str[i] != '\0'; ++i)
        s[index++] = str[i];

    s[index] = '\0';

    temp = NULL;

    return *this;
}

String String::operator-(const String& substr)
{
    int index = 0, size = 0;
    bool b = 0;
    char* temp = s, * temp2;
    const char* tstr = substr.s;

    for (; substr.s[size] != '\0'; ++size);

    for (int i = 0; *temp != '\0'; )
    {
        for (int i=0; substr.s[i] != '\0';++i)
        {
            if (temp[i] == substr.s[i])
                b = 1;
            else
            {
                b = 0;
                break;
            }
        }
        if (b)
        {
            index = i;
            temp2 = temp + size;

            for(int i=0; s[index] != '\0'; ++i)
                s[index++] = temp2[i];
        }
        else if (b)
        {
            temp += size;
            i += size;
        }
        else
        {
            ++temp;
            ++i;
        }
    }
    temp = NULL;
    temp2 = NULL;
    tstr = NULL;

    return *this;
}

String String::operator-(const char& str)
{
    int index = 0;
    char* temp = s;

    for (int i = 0; s[i] != '\0'; )
    {
        if (s[i] == str)
        {
            index = i;
            temp = (s+i) + 1;

            while (s[index] != '\0')
                s[index++] = *(temp++);
        }
        else
            ++i;
    }
    temp = NULL;

    return *this;
}

String String::operator-(const char* str)
{
    int index = 0, size = 0;
    bool b = 0;
    char* temp = s, * temp2;
    const char* tstr = str;

    for (; str[size] != '\0'; ++size);

    for (int i = 0; *temp != '\0'; )
    {
        for (int i = 0; str[i] != '\0'; ++i)
        {
            if (temp[i] == str[i])
                b = 1;
            else
            {
                b = 0;
                break;
            }
        }
        if (b)
        {
            index = i;
            temp2 = temp + size;

            for (int i = 0; s[index] != '\0'; ++i)
                s[index++] = temp2[i];
        }
        else if (b)
        {
            temp += size;
            i += size;
        }
        else
        {
            ++temp;
            ++i;
        }
    }
    temp = NULL;
    temp2 = NULL;
    tstr = NULL;

    return *this;
}

String& String::operator=(const String& Str)
{
    int size = 0;

    for (int i = 0; Str[i] != '\0'; ++size, ++i);
    ++size;

    if (s != NULL)
        delete[] s;

    s = new char[size];

    for (int i = 0; i < size; ++i)
        s[i] = Str[i];

    return *this;
}

String& String::operator=(char* Str)
{
    int size = 0;

    for (int i = 0; Str[i] != '\0'; ++size, ++i);
    ++size;

    if (s != NULL)
        delete[] s;

    s = new char[size];

    for (int i = 0; i < size; ++i)
        s[i] = Str[i];

    return *this;
}

bool String::operator==(const String& Str) const
{
    bool b = 0;

    for (int i=0; s[i] != '\0' || Str.s[i] != '\0'; ++i)
    {
        if (s[i] == Str.s[i])
            b = 1;
        else
        {
            b = 0;
            break;
        }
    }

    return b;
}

bool String::operator==(const char* Str) const
{
    bool b = 0;

    for (int i=0; s[i] != '\0' || Str[i] != '\0'; ++i)
    {
        if (s[i] == Str[i])
            b = 1;
        else
        {
            b = 0;
            break;
        }
    }

    return b;
}

bool String::operator!()
{
    if (*s == '\0' || s == NULL)
        return true;
    else
        return false;
}

int String::operator()(char c) const
{
    int index = -1;

    for (int i=0; s[i] != '\0'; ++i)
    {
        if (s[i] == c)
        {
            index = i;
            break;
        }
    }

    return index;
}

int String::operator()(const String& str) const
{
    int index = -1;
    bool b = 0;

    for (int i = 0; *(s+i) != '\0'; ++i)
    {
        for (int j = 0; str.s[j] != '\0'; ++j)
        {
            if (str.s[j] == *((s+i)+j))
                b = 1;
            else
            {
                b = 0;
                break;
            }
        }
        if(b)
        {
            index = i;
            break;
        }
    }

    return index;
}

int String::operator()(const char* str) const
{
    int index = -1;
    bool b = 0;

    for (int i = 0; *(s + i) != '\0'; ++i)
    {
        for (int j = 0; str[j] != '\0'; ++j)
        {
            if (str[j] == *((s + i) + j))
                b = 1;
            else
            {
                b = 0;
                break;
            }
        }
        if (b)
        {
            index = i;
            break;
        }
    }

    return index;
}

String::operator int() const
{
    int size = 0;

    for (; s[size] != '\0'; ++size);

    return size;
}

String::~String()
{
    delete[] s;
    s = NULL;
}

ostream& operator<<(ostream& output, const String& str)
{
    if (str.s == NULL)
        output << '\n';
    else
        output << str.s;

    return output;
}

istream& operator>>(istream& input, String& str)
{
    if (str.s != NULL)
        input >> str.s;

    return input;
}