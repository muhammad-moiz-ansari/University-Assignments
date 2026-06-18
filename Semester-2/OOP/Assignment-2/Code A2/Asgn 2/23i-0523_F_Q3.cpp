/*
        Your Name: Muhammad Moiz Ansari
        Your Roll#: 23i-0523
        Your Section: BS(CS)-F
        Assignment # 2
*/

#include <iostream>
#include <string>
#include "23i-0523_F_Q3.h"
using namespace std;

//Default Constructor:
CAList::CAList()
{
    v_index = new int[ksize];
    values = new int[ksize];
    b_key = new bool[ksize];

    for (int i = 0; i < ksize; ++i)
    {
        v_index[i] = 1;
        b_key[i] = 0;
        values[i] = 0;
    }
}

//Copy Constructor:
CAList::CAList(const CAList& obj)
{
    k_index = obj.k_index;
    keys = obj.keys;
    v_index = new int[ksize];
    delete[] values;
    values = new int[ksize];
    delete[] b_key;
    b_key = new bool[ksize];

    for (int i = 0; i < ksize; ++i)
    {
        v_index[i] = obj.v_index[i];
        values[i] = obj.values[i];
        b_key[i] = obj.b_key[i];
    }

    if (arr != NULL)
        delete[] arr;

    arr = new string * [keys];
    for (int i = 0; i < keys; ++i)
    {
        arr[i] = new string[values[i] + 1]; // +1 for one memory for key name
        for (int j = 0; j < values[i] + 1; ++j)
        {
            arr[i][j] = obj.arr[i][j];
        }
    }
}

//Copying object operator:
CAList& CAList::operator=(CAList& obj)
{
    k_index = obj.k_index;
    keys = obj.keys;
    v_index = new int[ksize];
    delete[] values;
    values = new int[ksize];
    delete[] b_key;
    b_key = new bool[ksize];
 
    for (int i = 0; i < ksize; ++i)
    {
        v_index[i] = obj.v_index[i];
        values[i] = obj.values[i];
        b_key[i] = obj.b_key[i];
    }

    if (arr != NULL)
        delete[] arr;

    arr = new string * [keys];
    for (int i = 0; i < keys; ++i)
    {
        arr[i] = new string[values[i] + 1]; // +1 for one memory for key name
        for (int j = 0; j < values[i] + 1; ++j)
        {
            arr[i][j] = obj.arr[i][j];
        }
    }

    return *this;
}

CAList& CAList::operator[](string key)
{
    k_index = 0;
    int i = 0, size = keys;
    bool b1 = 1, b2 = 0;
    string** temp = arr;

    //Adding a new memory:
    if (keys < ksize)
    {
        if (arr != NULL)
        {
            for (int i = 0; i < keys; ++i)
            {
                if (values[i] > 0)
                    if (arr[i][0] == key)
                    {
                        b1 = 0;
                        break;
                    }
            }
        }
        if (b1)
        {
            arr = new string * [++keys];
            for (int i = 0; i < size; ++i)
                arr[i] = temp[i];
            arr[size] = new string[1];
            arr[size][0] = key;
            b2 = 1;
        }
        if (temp != NULL)
        {
            if (b2)
            {
                for (int i = 0; i < size; ++i)
                    temp[i] = NULL;
                delete[] temp;
            }
            temp = NULL;
        }
    }

    //Assigning key process
    for (; i < keys; ++i)
    {
        if (arr[i][0] == "\0")
        {
            k_index = i;
            break;
        }
        else if (arr[i][0] == key)
        {
            k_index = i;
            break;
        }
    }
    //Full size error
    if (!(i < ksize))
    {
        cout << "Error: Key space not available. Maximum number of keys attained. The key \"" << key << "\" can not be added." << endl << endl;
    }
    else
    {
        arr[k_index][0] = key;
        b_key[k_index] = 1;
    }

    return *this;
}

//Assigning value operator:
CAList& CAList::operator=(string value)
{
    int index = -1, size = values[k_index] + 1;
    bool b1 = 1, b2 = 0, bsame = 0;
    string* temp = arr[k_index];

    //To check if value already exists:
    for (int i = 0; i < values[k_index]; ++i)
        if (arr[k_index][i + 1] == value)
        {
            bsame = 1;
            b_key[k_index] = 0;
            break;
        }
    for (int i = 0; i < keys; ++i)
        if (b_key[i])
        {
            index = k_index;
            break;
        }

    if (keys <= ksize && index>=0)
    {
        //Adding a new memory:
        if (values[k_index] < vsize && !bsame)
        {
            if (arr[k_index] != NULL)
            {
                for (int i = 0; i < values[k_index]; ++i)
                {
                    if (values[i + 1] > 0)
                        if (arr[k_index][i + 1] == value)
                            b1 = 0;
                }
            }
            if (b1)
            {
                arr[k_index] = new string[++values[k_index] + 1];
                for (int i = 0; i < size; ++i)
                    arr[k_index][i] = temp[i];
                arr[k_index][size] = "";
                b2 = 1;
            }
            if (temp != NULL)
            {
                if (b2)
                    delete[] temp;
                temp = NULL;
            }
        }

        //Assigning value process:
        if (!bsame)
        {
            for (int i = 0; i < keys; ++i)
                if (b_key[i])
                {
                    index = k_index;
                    break;
                }

            if (b_key[k_index] && index >= 0)
            {
                if (v_index[index] <= vsize)
                {
                    arr[index][v_index[index]] = value;
                    if (v_index[index] <= vsize)
                        ++v_index[index];
                    b_key[index] = 0;
                }
                else
                {
                    cout << "Error: Value space not available. Maximum number of values attained in the key \"" << arr[index][0] << "\"."
                        << " The value \"" << value << "\" can not be added." << endl << endl;
                    b_key[k_index] = 0;
                }
            }
        }
        b_key[k_index] = 0;
    }
    return *this;
}

CAList& CAList::operator+=(string value)
{
    *this = value;
    return *this;
}

//Adding objects:
CAList& CAList::operator+(CAList obj2) //return obj1 + obj2;
{
    CAList* obj1 = new CAList();
    *obj1 = *this;

    string tkey = "", tval = "";
    int i1 = 0, i2 = 0;
    bool keysame = 0, valsame = 0;

    for (int ni = 0; ni < obj1->keys; ++ni)
    {
        keysame = 0;
        for (int i = 0; i < obj1->keys; ++i) //To check if any key of obj2 matches obj1 i(th) key
        {
            if (obj1->arr[ni][0] == obj2.arr[i][0])
            {
                keysame = 1;
                i1 = ni;
                i2 = i;
                break;
            }
        }
        if (keysame)
        {
            for (int i = 0; i < obj1->values[i1]; ++i)
            {
                for (int j = 0; j < obj2.values[i2]; ++j)
                {
                    if (obj1->arr[i1][i + 1] == obj2.arr[i2][j + 1]) //If a value matches, it is emptied
                    {
                        obj2.arr[i2][j + 1] = "";
                        break;
                    }
                }
            }
        }
    }

    //Adding the remaining keys and values of obj2 in obj1:
    for (int i = 0; i < obj2.keys; ++i) //Loop for keys
    {
        for (int j = 0; j < obj2.values[i]; ++j)    //Loop for values
        {
            if (obj2.arr[i][j + 1] != "")
            {
                tkey = obj2.arr[i][0];
                tval = obj2.arr[i][j + 1];
                (*obj1)[tkey] = tval;
            }
        }
    }

    return *obj1;
}

//Adding object in itself
CAList& CAList::operator+=(CAList obj2)
{
    *this = *this + obj2;
    return *this;
}

void CAList::remove_key(CAList& obj, int k)
{
    int index = 0;
    string** temp = obj.arr;

    obj.arr = new string * [obj.keys - 1];

    for (int i = 0; i < obj.keys; ++i)
    {
        if (i != k)
            obj.arr[index++] = temp[i];
    }
    --obj.keys;
    //Shifting info of next key to deleted key:
    for (int i = k; (i + 1) < ksize; ++i)
        obj.v_index[i] = obj.v_index[i + 1];
    for (int i = k; (i + 1) < ksize; ++i)
        obj.values[i] = obj.values[i + 1];

    delete[] temp[k];
    delete[] temp;
    temp = NULL;
}

void CAList::remove_value(CAList& obj, int k)
{
    int index = 0;
    string* temp = obj.arr[k];

    obj.arr[k] = new string[obj.values[k]];

    for (int i = 0; i < obj.values[k] + 1; ++i)
    {
        if (temp[i] != "")
            obj.arr[k][index++] = temp[i];
        else
            --obj.values[k];
    }
    
    delete[] temp;
    temp = NULL;
}

//Subtracting objects:
CAList& CAList::operator-(CAList obj2)
{
    CAList* obj1 = new CAList();
    *obj1 = *this;

    int i1 = 0, i2 = 0;
    bool keysame = 0, valsame = 0, keyfilled = 0;

    for (int ni = 0; ni < obj1->keys; ++ni)
    {
        keysame = 0;
        for (int i = 0; i < obj2.keys; ++i)    //To check if any key of obj2 matches obj1 i(th) key
        {
            if (obj1->arr[ni][0] == obj2.arr[i][0])
            {
                keysame = 1;
                i1 = ni;
                i2 = i;
                break;
            }
        }
        if (keysame)
        {
            for (int i = 0; i < obj1->values[i1]; ++i)
            {
                for (int j = 0; j < obj2.values[i2]; ++j)
                {
                    if (obj1->arr[i1][i + 1] == obj2.arr[i2][j + 1]) //If a value matches, it is emptied in obj1
                    {
                        obj1->arr[i1][i + 1] = "";
                        break;
                    }
                }
            }
        }
    }

    //Removing value:
    for (int i = 0; i < obj1->keys; ++i) //Loop for keys
    {
        for (int j = 0; j < obj1->values[i]; ++j)    //Loop for values
        {
            if (obj1->arr[i][j + 1] == "")
            {
                remove_value(*obj1, i);
            }
        }
    }

    //Removing key:
    for (int i = 0; i < obj1->keys; ++i)
    {
        keyfilled = 0;
        for (int j = 0; j < obj1->values[i]; ++j)
        {
            if (obj1->arr[i][j + 1] != "")
            {
                keyfilled = 1;
                break;
            }
        }
        if (!keyfilled)
            remove_key(*obj1, i);
    }

    return *obj1;
}

//Subtracting object in itself
CAList& CAList::operator-=(CAList obj)
{
    *this = *this - obj;
    return *this;
}

CAList& CAList::operator-=(string value)
{
    bool exists = 0, keyfilled = 0;

    //If a value matches, it is emptied
    for (int i = 0; i < values[k_index]; ++i)
        if (arr[k_index][i + 1] == value)
        {
            arr[k_index][i + 1] = "";
            exists = 1;
            break;
        }

    //Removing value::
    if (exists)
    {
        remove_value(*this, k_index);
    }
    else
    {
        cout << "Error: Value " << value << " does not exists in key " << arr[k_index][0] << endl << endl;
    }
    //Removing key:
    for (int i = 0; i < this->keys; ++i)
    {
        keyfilled = 0;
        for (int j = 0; j < this->values[i]; ++j)
        {
            if (this->arr[i][j + 1] != "" && this->values[i] != 0)
            {
                keyfilled = 1;
                break;
            }
        }
        if (!keyfilled)
            remove_key(*this, i);
    }

    this->b_key[k_index] = 0;

    return *this;
}

//Outputing object:
ostream& operator<<(ostream& output, const CAList& list)
{
    output << "[";
    for (int i = 0; i < list.keys; ++i)
    {
        if (list.arr[i][0] != "\0")
        {
            if (i != 0)
                output << " ";
            output << list.arr[i][0] << ":" << "{";
            for (int j = 1; j <= list.values[i]; ++j)
            {
                if (list.arr[i][j] != "\0")
                    output << list.arr[i][j];
                if (j < list.values[i])
                    output << ", ";
                else
                    break;
            }
            output << "}";
            if (i < list.keys - 1)
                output << ", \n";
        }
    }
    output << "]";

    output << endl << endl;

    return output;
}

//Destructor
CAList::~CAList()
{
    for (int i = 0; i < keys; ++i)
    {
        for (int j = 0; j < values[i]; ++j)
            arr[i][j] = "";

        if (arr[i] != NULL)
            delete[] arr[i];
        arr[i] = NULL;
    }
    delete[] arr;
    arr = NULL;

    for (int i = 0; i < ksize; ++i)
        v_index[i] = NULL;
    v_index = NULL;
    if (values != NULL)
        for (int i = 0; i < ksize; ++i)
            values[i] = NULL;
    delete[] values;
    values = NULL;
    if (b_key != NULL)
        for (int i = 0; i < ksize; ++i)
            b_key[i] = NULL;
    delete[] b_key;
    b_key = NULL;

}
