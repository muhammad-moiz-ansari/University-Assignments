/*    Problem 3

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 3

*/

#include <iostream>
#include <ctime>

using namespace std;
int main()
{
	const int num_of_w=100, wsize=17, nsize=25;
	char enter;
	
	char words[num_of_w][wsize]={{'g', 'a', 'm', 'i', 'n', 'g'}, {'c', 'o', 'd', 'e'}, {'c', 'o', 'n', 's', 'o', 'l', 'e'}, {'a', 'l', 'g', 'o', 'r', 'i', 't', 'h', 'm'}, {'l', 'e', 'v', 'e', 'l'}, {'d', 'e', 'b', 'u', 'g'}, {'c', 'o', 'n', 't', 'r', 'o', 'l', 'l', 'e', 'r'}, {'v', 'a', 'r', 'i', 'a', 'b', 'l', 'e'}, {'q', 'u', 'e', 's', 't'}, {'c', 'o', 'm', 'p', 'i', 'l', 'e'}, {'a', 'v', 'a', 't', 'a', 'r'}, {'s', 'c', 'r', 'i', 'p', 't'}, {'r', 'e', 's', 'p', 'a', 'w', 'n'}, {'l', 'o', 'o', 'p'}, {'s', 't', 'r', 'a', 't', 'e', 'g', 'y'}, {'p', 'i', 'x', 'e', 'l'}, {'e', 'n', 'g', 'i', 'n', 'e'}, {'m', 'u', 'l', 't', 'i', 'p', 'l', 'a', 'y', 'e', 'r'}, {'b', 'u', 'g'}, {'h', 'a', 'c', 'k'}, {'s', 'c', 'o', 'r', 'e'}, {'s', 'a', 'n', 'd', 'b', 'o', 'x'}, {'s', 'y', 'n', 't', 'a', 'x'}, {'t', 'u', 't', 'o', 'r', 'i', 'a', 'l'}, {'r', 'e', 'n', 'd', 'e', 'r'}, {'k', 'e', 'y', 'b', 'o', 'a', 'r', 'd'}, {'i', 'n', 'v', 'e', 'n', 't', 'o', 'r', 'y'}, {'c', 'p', 'u'}, {'l', 'a', 'n'}, {'v', 'r', 'b', 'o', 'x'}, {'s', 'c', 'r', 'i', 'p', 't', 'i', 'n', 'g'}, {'s', 'e', 'r', 'v', 'e', 'r'}, {'m', 'o', 'd'}, {'s', 'i', 'm', 'u', 'l', 'a', 't', 'i', 'o', 'n'}, {'c', 'o', 'd', 'e', 'b', 'a', 's', 'e'}, {'g', 'a', 'm', 'e', 'r'}, {'c', 'o', 'd', 'e', 'p', 'e', 'n'}, {'i', 'n', 't', 'e', 'r', 'f', 'a', 'c', 'e'}, {'d', 'e', 'b', 'u', 'g', 'g', 'i', 'n', 'g'}, {'p', 'r', 'o', 't', 'o', 't', 'y', 'p', 'e'}, {'s', 'h', 'e', 'h', 'r', 'e', 'y', 'a', 'r'}, {'a', 'r', 's', 'h', 'a', 'd'}, {'a', 'q', 'i', 'b'}, {'v', 'i', 's', 'u', 'a', 'l'}, {'f', 'o', 'r', 't', 'n', 'i', 't', 'e'}, {'m', 'i', 'n', 'e', 'c', 'r', 'a', 'f', 't'}, {'l', 'a', 'p', 't', 'o', 'p'}, {'c', 'o', 'm', 'p', 'u', 't', 'e', 'r'}, {'p', 'l', 'a', 'g', 'i', 'a', 'r', 'i', 's', 'm'}, {'l', 'e', 'c', 't', 'u', 'r', 'e'}, {'h', 'o', 'm', 'e', 'w', 'o', 'r', 'k'}, {'p', 'r', 'o', 'j', 'e', 'c', 't'}, {'c', 'o', 'm', 'p', 'i', 'l', 'e', 'r'}, {'d', 'a', 't', 'a', 'b', 'a', 's', 'e'}, {'n', 'e', 't', 'w', 'o', 'r', 'k'}, {'s', 'e', 'c', 'u', 'r', 'i', 't', 'y'}, {'e', 'n', 'c', 'r', 'y', 'p', 't', 'i', 'o', 'n'}, {'s', 'o', 'f', 't', 'w', 'a', 'r', 'e'}, {'h', 'a', 'r', 'd', 'w', 'a', 'r', 'e'}, {'p', 'r', 'o', 'g', 'r', 'a', 'm', 'm', 'i', 'n', 'g'}, {'c', 'o', 'd', 'i', 'n', 'g'}, {'s', 'c', 'r', 'i', 'p', 't', 'i', 'n', 'g'}, {'w', 'e', 'b', 'p', 'a', 'g', 'e'}, {'s', 'o', 'f', 't', 'w', 'a', 'r', 'e'}, {'d', 'e', 'v', 'e', 'l', 'o', 'p', 'm', 'e', 'n', 't'}, {'a', 'n', 'a', 'l', 'y', 's', 'i', 's'}, {'s', 'y', 's', 't', 'e', 'm'}, {'a', 'r', 'c', 'h', 'i', 't', 'e', 'c', 't', 'u', 'r', 'e'}, {'v', 'e', 'r', 's', 'i', 'o', 'n', 'i', 'n', 'g'}, {'r', 'e', 'p', 'o', 's', 'i', 't', 'o', 'r', 'y'}, {'o', 'b', 'j', 'e', 'c', 't'}, {'o', 'r', 'i', 'e', 'n', 't', 'e', 'd'}, {'p', 'r', 'o', 'g', 'r', 'a', 'm', 'm', 'i', 'n', 'g'}, {'f', 'r', 'a', 'm', 'e', 'w', 'o', 'r', 'k'}, {'i', 't', 'e', 'r', 'a', 't', 'i', 'o', 'n'}, {'c', 'o', 'n', 'd', 'i', 't', 'i', 'o', 'n', 'a', 'l'}, {'l', 'o', 'g', 'i', 'c'}, {'d', 'a', 't', 'a', 'b', 'a', 's', 'e'}, {'d', 'e', 's', 'i', 'g', 'n'}, {'a', 'u', 't', 'h', 'e', 'n', 't', 'i', 'c', 'a', 't', 'i', 'o', 'n'}, {'a', 'u', 't', 'h', 'o', 'r', 'i', 'z', 'a', 't', 'i', 'o', 'n'}, {'d', 'e', 'p', 'l', 'o', 'y', 'm', 'e', 'n', 't'}, {'v', 'i', 'r', 't', 'u', 'a', 'l', 'i', 'z', 'a', 't', 'i', 'o', 'n'}, {'c', 'y', 'b', 'e', 'r', 's', 'e', 'c', 'u', 'r', 'i', 't', 'y'}, {'e', 't', 'h', 'i', 'c', 's'}, {'c', 'l', 'o', 'u', 'd'}, {'c', 'o', 'm', 'p', 'u', 't', 'i', 'n', 'g'}, {'m', 'a', 'c', 'h', 'i', 'n', 'e'}, {'l', 'e', 'a', 'r', 'n', 'i', 'n', 'g'}, {'a', 'r', 't', 'i', 'f', 'i', 'c', 'i', 'a', 'l'}, {'i', 'n', 't', 'e', 'l', 'l', 'i', 'g', 'e', 'n', 'c', 'e'}, {'n', 'e', 't', 'w', 'o', 'r', 'k', 'i', 'n', 'g'}, {'i', 'n', 'n', 'o', 'v', 'a', 't', 'i', 'o', 'n'}, {'t', 'e', 'c', 'h', 'n', 'o', 'l', 'o', 'g', 'y'}, {'e', 'd', 'u', 'c', 'a', 't', 'i', 'o', 'n'}, {'c', 'y', 'b', 'e', 'r'}, {'p', 'h', 'y', 's', 'i', 'c', 'a', 'l'}, {'s', 'y', 's', 't', 'e', 'm', 's'}, {'d', 'a', 't', 'a'}, {'a', 'n', 'a', 'l', 'y', 's', 'i', 's'}};
	
	char word[wsize], fill[wsize], name[nsize], check[wsize], letter;
	int pos, wrong=0, correct=0, ch=0;
	bool w=0, repeat=0, n=0;
	
	cout<<"-----Welcome to HANGMAN Game!-----\n\n";
	
	cout<<"Rules:\n"
		<<"1. You have to guess a word by inputting a letter.\n"
		<<"2. You can only enter a letter once.\n"
		<<"3. Enter a letter once even if it occurs twice in a word.\n"
		<<"4. You will have total of seven lives.\n"
		<<"5. You will lose one life for every wrong letter.\n"
		<<"E n j o y !!\n\n";
		
	cout<<"Enter your name(in lower-cae only): ";
	cin.getline(name, nsize);
	cout<<endl;
	
	int nlength=0;
	for(int i=0; name[i]!='\0'; ++i)		//Checking name length
		++nlength;
	
	cout<<"Press E n t e r to Start the game: ";
	cin.get(enter);
	
	
	system("clear");
	cout<<endl;
	
	srand(time(0));
	int call=(rand()%99)+0;
	
	int length=0;
	for(int i=0; words[call][i]!='\0'; ++i)		//Checking word length
		++length;
	
	for(int i=0; i<length; ++i)		//Writting in word array
		word[i]=words[call][i];
	
	for(int i=0; i<length; ++i)		//Making dashes
		fill[i]='_';
	cout<<endl;
	
	while(wrong!=6 && correct==0)
	{
		cout<<"Word: \n";
		
		for(int i=0; i<length; ++i)		//Printing dash word
			cout<<fill[i]<<" ";
		cout<<endl;
		
		do
		{
			if(!repeat)
			  cout<<"Enter a letter: ";		//Inputting letter
			cin>>letter;
			
			while(!(letter>='a' && letter<='z'))	//Input validation
			{
				 cout<<"Enter only Lower-case Alphabets(a-z): ";
				 cin>>letter;
			}
			
			repeat=0;
			for(int i=0; i<26; ++i)		//Checking repeat again
			{
				if(check[i]==letter)
				{
				  repeat=1;
				  break;
				}
			}
			if(repeat)
			{
			  cout<<"You already entered this letter. 😡\n";
			  cout<<"Enter a letter again: ";
			}
			else
				break;
			
		}while(repeat);
		
		system("clear");
		
		check[ch]=letter;
		++ch;
		
		if(!repeat)
		{
			w=1;
			for(int i=0; i<length; ++i)		//Checking entered letter
			{
				if(letter==word[i])
				{
					fill[i]=letter;
					w=0;
				}
			}
			
			n=0;
			for(int i=0; i<nlength; ++i)
			{
				if(letter==name[i])
				  n=1;
			}
		}
		if(w)
		{
		  if(n)
		    wrong+=2;
		  else
		  	  ++wrong;
		}
		
		if(w==0 && n && wrong>0)
		  --wrong;
		
		if(wrong==0)
		{
			cout<<"\n  +---+\n"
				<<"  |   |\n"
				<<"      |\n"
				<<"      |\n"
				<<"      |\n"
				<<"      |\n"
				<<"=========\n\n";
		}
		
		if(wrong==1)
		{
			cout<<"\n  +---+\n"
				<<"  |   |\n"
				<<"  O   |\n"
				<<"      |\n"
				<<"      |\n"
				<<"      |\n"
				<<"=========\n\n";
		}
		
		if(wrong==2)
		{
			cout<<"\n  +---+\n"
				<<"  |   |\n"
				<<"  O   |\n"
				<<"  |   |\n"
				<<"      |\n"
				<<"      |\n"
				<<"=========\n\n";
		}
		
		if(wrong==3)
		{
			cout<<"\n  +---+\n"
				<<"  |   |\n"
				<<"  O   |\n"
				<<" /|   |\n"
				<<"      |\n"
				<<"      |\n"
				<<"=========\n\n";
		}
		
		if(wrong==4)
		{
			cout<<"\n  +---+\n"
				<<"  |   |\n"
				<<"  O   |\n"
				<<" /|\\  |\n"
				<<"      |\n"
				<<"      |\n"
				<<"=========\n\n";
		}
		
		if(wrong==5)
		{
			cout<<"\n  +---+\n"
				<<"  |   |\n"
				<<"  O   |\n"
				<<" /|\\  |\n"
				<<" /    |\n"
				<<"      |\n"
				<<"=========\n\n";
		}
		
		if(wrong==6)
		{
			cout<<"\n  +---+\n"
				<<"  |   |\n"
				<<"  O   |\n"
				<<" /|\\  |\n"
				<<" / \\  |\n"
				<<"      |\n"
				<<"=========\n\n";
		}
		
		
		correct=1;
		for(int i=0; i<length; ++i)		//Checking if word is complete
		{
			if(fill[i]=='_')
			{
				correct=0;
				break;
			}
		}
		
		if(correct==1)
		{
			for(int i=0; i<length; ++i)		//Printing dash word
				cout<<fill[i]<<" ";
			cout<<endl;
		}
		
		cout<<endl;
	}
	
	if(wrong==6)
	  cout<<"Oops!! You died.  ¯\\_(ツ)_/¯\n\nBetter luck next time...  ( ≖‿  ≖ )  \n\n";
	else
		cout<<"Congratulations!!🥳🎉\nYou won!   ৻( • ᗜ • ৻) \n\n";
	
	
	
	return 0;
}
