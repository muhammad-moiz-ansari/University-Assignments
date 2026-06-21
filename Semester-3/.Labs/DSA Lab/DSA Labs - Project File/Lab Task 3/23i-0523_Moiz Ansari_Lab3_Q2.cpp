#include <iostream>
using namespace std;

const int numMatches = 10;

template <typename T>
T* inputPlayerData(T (&runs)[][numMatches], int numPlayers)
{
	cout << "Input Runs of Players:\n\n";
	for (int i = 0; i < numPlayers; ++i)
	{
		cout << "Player " << i + 1 << ":\n";
		for (int j = 0; j < numMatches; ++j)
		{
			cout << "Match " << j + 1 << ": ";
			cin >> runs[i][j];
		}
		cout << "\n";
	}

	return runs;
}

template <typename T>
T* computeStatistics(const T runs[][numMatches], const int numPlayers, T totalRuns[], T avgRuns[])
{
	//Total Runs:
	T sum = 0;
	for (int i = 0; i < numPlayers; ++i)
	{
		sum = 0;
		for (int j = 0; j < numMatches; ++j)
		{
			sum += runs[i][j];
		}
		totalRuns[i] = sum;
	}

	//Average Runs:
	for (int i = 0; i < numPlayers; ++i)
	{
		avgRuns[i] = totalRuns[i] / numMatches;
	}


	return totalRuns;
}

template <typename T>
int* sortPlayersByTotalRuns(T totalRuns[], int playerIndices[], int numPlayers)
{
	int size = numPlayers, k = 0;
	T max = 0, maxin = 0;

	T* runs=new T[numPlayers];
	for (int i = 0; i < size; ++i)
		runs[i] = totalRuns[i];

	for (int i = 0; i < size; ++i)
	{
		max = 0;
		maxin = 0;
		for (int j = 0; j < size; ++j)
		{
			if (runs[j] > max)
			{
				max = runs[j];
				maxin = j;
			}
		}
		playerIndices[k++] = maxin;
		runs[maxin] = -1;
	}

	return playerIndices;
}

template <typename T>
T printTop10Players(const T totalRuns[], const int playerIndices[], int numPlayers)
{
	//cout << "Runs of Top 10 Players:\n\n";
	for (int i = 0; i < numPlayers; ++i)
	{
		cout << "Player " << playerIndices[i] + 1 << ": ";
		cout << totalRuns[playerIndices[i]]<<" runs\n";
	}

	//T in = 0;
	return 0;
}


//int main()
//{
//
//
//
//	return 0;
//}