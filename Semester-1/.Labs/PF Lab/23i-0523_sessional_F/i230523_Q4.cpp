/*
Name : Moiz ansari
Roll no : 23i=0523
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int RollDice();
int MovePlayer(int player, int currentPosition, int diceRoll);
int CheckForLadder(int square);
int CheckForSnake(int square);
void DisplayBoard(int player1Pos, int player2Pos);
void PlayLudoSnakeLadderGame();

int main()
{
	PlayLudoSnakeLadderGame();
	
	return 0;
}
void PlayLudoSnakeLadderGame()
{
	player1Pos=1;
	player2Pos=1;
	cout<<"Welcome to Ludo, Snake, Ladder Game!\n\n\n";
	DisplayBoard(player1Pos, player2Pos);
	
}
void DisplayBoard(int player1Pos, int player2Pos)
{
	player1Pos=1;
	player2Pos=1;
	
	srand(time(0));
	int n=100;
	for(int i=1; i<=10; ++i)
	{
		for(int j=1; j<=10; ++j)
		{
			cout<<"["<<n<<"]  ";
			--n;
		}
		cout<<endl;
	}
	
	cout<<"\n\nLadder: \n";
	for(int i=1; i<=4; ++i)
	{
		int l_low[4], l_high[4];
		l_low[i-1]=(rand()%100)-1;
		l_high[i-1]=l_low[i-1]-1;
		while(!(l_low[i-1]<l_high[i-1]))
		{
			l_high[i-1]=(rand()%100)-1;
		}
		cout<<l_low[i-1]<<" -> "<<l_high[i-1]<<"(Climb up)\n";
	}
	cout<<"\n\nSnake: \n";
	for(int i=1; i<=4; ++i)
	{
		int s_low[4], s_high[4];
		s_low[i-1]=(rand()%100)-1;
		s_high[i-1]=s_low[i-1]-1;
		while(!(s_low[i-1]<s_high[i-1]))
		{
			s_high[i-1]=(rand()%100)-1;
		}
		cout<<s_high[i-1]<<" -> "<<s_low[i-1]<<"(Slide down)\n";
	}
	cout<<"\n\n";
	
	cout<<"Player 1(P1) is at square "<<
}
int RollDice()
{
	player1Pos=(rand%6)+1;
	player2Pos=(rand%6)+1;
}








