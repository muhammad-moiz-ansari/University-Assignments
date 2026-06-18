///*

#include<iostream>
using namespace std;

void funwords()
{
    char arr[] = "the shy student said that jinx rhythms with lynx.";
    int i = 0, k = 0;
    while (arr[i]) 
    {
        char tok[10] = {};
        int j = 0;
        bool aha = false;
        while (arr[i] != ' ' && arr[i] != '.') 
        {
            if (arr[i] == 'a' || arr[i] == 'e' || arr[i] == 'i' || arr[i] == 'o' || arr[i] == 'u')
                aha = true;
            tok[j++] = arr[i++];
        }
        if (aha == false)
            cout << tok[(k++) % j];
        i++;
    }
}
int main()
{
    funwords();
}

//*/
/*
#include<iostream>
using namespace std;

void funwordsagain() 
{
	char arr[] = { "the shy student said that jinx rhythms with lynx." };
	int i = 0, k = 0;
	char etc[] = { "aeoi" };
	char eg[] = { " ." }; // first char is a space, and second is a .
	while (arr[i]) 
	{
		char lynx[10] = {};	//lynx initialized
		int j = 0;
		bool jinx = false;
		while (arr[i] != eg[0] && arr[i] != eg[1]) 
		{
			if (arr[i] == etc[0] || arr[i] == etc[1] || arr[i] == etc[2] || 
			arr[i] == etc[3])
				jinx = true;
			lynx[j++] = arr[i++];
		}
		if (jinx == true)
			cout << lynx << endl;
		i++;
	}
}
int main()
{
    funwordsagain();
}
//
*/

/*
#include <iostream>
using namespace std;

const int RANGE = 255;
const int N = 16;

void WithNoCommenting(char arr[]){
	char flex[N];
	int wow[RANGE +1]={},i;
	for (i = 0; arr[i]; ++i) // Loop 1
		++wow[arr[i]];
	for (i = 1; i <= RANGE; ++i) // Loop 2
		wow[i] += wow[i-1];
	for (i = 0; arr[i]; ++i) // Loop 3
	{
		flex[wow[arr[i]] - 1] = arr[i];
		-- wow[arr[i]];
	}
	for (i = 0; arr[i]; ++i) // Loop 4
	arr[i] = flex[i];
}
int main(){
	// ASCII of space is 32, 'a' is 97, 'f' is 102,
	// |'p' is 112, etc. (you are reqruired to find others)
	char arr[N] ="programming fun";
	WithNoCommenting(arr);
	cout << arr;
	return 0;
}*/