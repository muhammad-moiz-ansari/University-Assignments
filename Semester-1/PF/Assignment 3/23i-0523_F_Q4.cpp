/*    Problem 4

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 3

*/

#include <iostream>
using namespace std;

int main()
{
	const int size = 500, wsize = 25; // Word size
	char para[size] = "\0", newpara[size] = "\0",
		 find[wsize] = "\0", replace[wsize] = "\0", tempfind[wsize] = "\0";
	int pospara[wsize];
	string Para[size];
	cout << "----------\"Find/Replace\" Tool----------\n\n";

	cout << "Please Enter the text(500 Characters Max): \n   ";

	cin.getline(para, size); // Inputting paragraph

	int psize = 0;
	for (int i = 0; para[i] != '\0'; ++i)
		++psize;

	bool f = 1;
	while (1)
	{
		cout << "Please Enter the word to  F i n d (Enter five dots to exit): ";
		cin >> find;	//Word to find
		
		//for(int i=0; i<wsize; ++i)
			//cin.getline(find[i], wsize);
		
	
	
		int fsize = 0;
		for (int i = 0; find[i] != '\0'; ++i)
			++fsize;
		
		if(find[0]=='.' && find[1]=='.' && find[2]=='.' && find[3]=='.' && find[4]=='.')
			  break;

		for (int i = 0; i < fsize; ++i)
			if (find[i] == ' ' || find[i] == '\n')
				break;

		cout << "Please Enter the word to  R e p l a c e : ";
		cin >> replace;
		

		int rsize = 0;
		for (int i = 0; replace[i] != '\0'; ++i)
			++rsize;


		int p_c = 0;
		int i = 0;

		for (i = 0; i < psize; i++)
		{
			bool found = false;
			if (para[i] == find[0])
			{
				found = true;
				for (int j = 0; find[j] != '\0'; j++)
				{
					if (para[i + j] != find[j])
					{
						found = false;
						break;
					}
				}

				if (found)
					i += fsize - 1;
			}

			if (found)
			{
				for (int j = 0; replace[j] != '\0'; j++)
				{
					newpara[p_c] = replace[j];
					p_c++;
				}
			}
			else
			{
				newpara[p_c] = para[i];
				p_c++;
			}

			
		}
		
		cout<<"\nBefore Editing: \n";
		for (int k = 0; k < i; k++)
			cout << para[k];

		cout<<endl;

		cout<<"After Editing: \n";
		for (int k = 0; k < p_c; k++)
			cout << newpara[k];

		cout << endl << endl;

		for (int k = 0; k < i; k++)
			para[k] = '\0';

		for (int k = 0; k < rsize; ++k)
			replace[k] = '\0';

		for (int k = 0; k < p_c; k++)
			para[k] = newpara[k];

		psize = 0;
		for (int i = 0; para[i] != '\0'; ++i)
			++psize;

	}

	return 0;
}
