#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

string bowler = "Bowler", batter = "Batter", allrounder = "All-Rounder";

class Player
{
public:
	int playerid;
	string name, playing_role;
	float batting_avg, strike_rate, bowling_avg, economy_rate, performance, current_form_index,
		runs_per_ball, wickets_per_ball,
		priority;

	int burst_time,		//balls played
		arrtime,
		qtime,
		pendingt,
		completion_time,		//on which ball they dismissed
		playtime;

	static int players_arrived;


	// Player Match Stats
	bool isdismissed, isdone;	//Batter

	int balls_faced,		//Batter
		balls_bowled;		//Bowler

	float runs_scored,		//Batter
		runs_conceded, wickets_taken;		//Bowler

	Player(int pid = 0, string n = "", float batavg = 0, float sr = 0, float bowlavg = 0, float er = 0, float per = 0, float cfi = 0, string pr = "")
	{
		playerid = pid;
		name = n;
		batting_avg = batavg;
		strike_rate = sr;
		bowling_avg = bowlavg;
		economy_rate = er;
		performance = per;
		current_form_index = cfi;
		playing_role = pr;

		runs_per_ball = 0;
		wickets_per_ball = 0;
		priority = 0;

		burst_time = 0;
		arrtime = 0;
		qtime = 0;
		completion_time = 0;
		playtime = 0;
		pendingt = 0;

		isdone = 0;
		isdismissed = 0;
		runs_scored = 0;
		balls_faced = 0;
		balls_bowled = 0;
		runs_conceded = 0;
		wickets_taken = 0;
	}

	void initializeBatter()
	{
		runs_per_ball = strike_rate / 100;
		burst_time = (batting_avg * 100) / strike_rate;
		pendingt = burst_time;
		priority = 1 / (batting_avg * 0.6 + strike_rate * 0.4);
	}

	void initializeBowler(int overs)
	{
		burst_time = ((float)overs / 4) * 6;
		pendingt = burst_time;
		balls_bowled = burst_time;
		runs_per_ball = economy_rate / 6;
		wickets_per_ball = 1 / ((bowling_avg * runs_per_ball) + (balls_bowled / 3));
		priority = 1 / ((wickets_per_ball * 0.5) + (100 - bowling_avg) * 0.3 + (100 - economy_rate * 10) * 0.2);
	}

};
int Player::players_arrived = 0;

void parseCSV(vector<Player> &players, string filename, vector<int> &playerids, vector<string> &pnames, vector<string> &proles)
{
	ifstream file(filename);

	string line, word;
	getline(file, line);		//Discard header

	int i = 0;
	while (getline(file, line))
	{
		stringstream ss(line);		//To read each word by splitting string with ','
		vector <string> row;

		while (getline(ss, word, ','))
			row.push_back(word);

		if (row.size() == 9)
		{
			players.emplace_back(stoi(row[0]), row[1], stof(row[2]), stof(row[3]), stof(row[4]), stof(row[5]), stof(row[6]), stof(row[7]), row[8]);
			playerids.push_back(stoi(row[0]));
			pnames.push_back(row[1]);
			proles.push_back(row[8]);
		}
	}
}

void sortball(vector<Player*>& vec, int n)
{
	bool swap, b = 0;
	for (int i = 0; i < n; ++i)
	{
		swap = 0;
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (vec[j]->economy_rate > vec[j + 1]->economy_rate)
				b = 1;
			else if (vec[j]->economy_rate == vec[j + 1]->economy_rate && vec[j]->bowling_avg > vec[j + 1]->bowling_avg)
				b = 1;
			else if (vec[j]->economy_rate == vec[j + 1]->economy_rate && vec[j]->bowling_avg == vec[j + 1]->bowling_avg && vec[j]->wickets_per_ball > vec[j + 1]->wickets_per_ball)
				b = 1;

			if(b)
			{
				Player* temp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;
				swap = 1;
				b = 0;
			}
		}
		if (!swap)
			break;
	}
}

void sortbat(vector<Player*>& vec, int n, string type)
{
	bool swap, b = 0;
	for (int i = 0; i < n; ++i)
	{
		swap = 0;
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (type == "SJF")
			{
				if (vec[j]->batting_avg < vec[j + 1]->batting_avg)
					b = 1;
				else if (vec[j]->batting_avg == vec[j + 1]->batting_avg && vec[j]->strike_rate < vec[j + 1]->strike_rate)
					b = 1;
			}
			else	// if (type == "SRTF")
			{
				if (vec[j]->burst_time > vec[j + 1]->burst_time)
					b = 1;
				else if (vec[j]->current_form_index < vec[j + 1]->current_form_index)
					b = 1;
			}

			if (b)
			{
				Player* temp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;
				swap = 1;
				b = 0;
			}
		}
		if (!swap)
			break;
	}
}

int main()
{
	///////////////// CSV Reading ///////////////
	vector <Player> players;
	vector <int> playerids;
	vector <string> pnames, proles;
	string filename = "Stats.csv";

	parseCSV(players, filename, playerids, pnames, proles);

	for (int i = 0; i < players.size(); ++i)
		cout << "Player " << players[i].playerid << ": " << players[i].name << "\n";

	/////////////// Schedule Type Input //////////////
	int choice = 0;
	string batshtype, bowlshtype;

	//For batter
	cout << "\nChoose the scheduling type for batter: \n1. SRTF\n2. SJF\nChoose: ";
	while (true)
	{
		cin >> choice;
		if (choice == 1 || choice == 2)
			break;
		cout << "Invalid input...Choose only 1 or 2: ";
	}
	if (choice == 1)
		batshtype = "SRTF";
	else
		batshtype = "SJF";

	//For bowler
	cout << "\nChoose the scheduling type for bowler: \n1. RR\n2. SJF\nChoose: ";
	while (true)
	{
		cin >> choice;
		if (choice == 1 || choice == 2)
			break;
		cout << "Invalid input...Choose only 1 or 2: ";
	}
	if (choice == 1)
		bowlshtype = "RR";
	else
		bowlshtype = "SJF";


	///////////////// Initialization ////////////////
	int minballs = 0, minovers, maxovers, players_arrived = 0;
	bool highbtime = 0;
	//Batters
	for (int i = 0; i < players.size(); ++i)
	{
		if (players[i].playing_role == batter || players[i].playing_role == allrounder)
		{
			players[i].initializeBatter();
			if (players[i].burst_time > 30)
				highbtime = 1;
		}
	}
	for (int i = 0; i < players.size(); ++i)
	{
		if (players[i].playing_role == batter || players[i].playing_role == allrounder)
		{
			if (highbtime)
			{
				players[i].burst_time = 0.5 * players[i].burst_time;
				players[i].pendingt = players[i].burst_time;
			}
			minballs += players[i].burst_time;
		}
	}
	minovers = ceil((float)minballs / 6);
	maxovers = minovers + 10;

	int overs = 0;
	cout << "Enter overs (" << minovers << "-" << maxovers << "): ";
	while (true)
	{
		cin >> overs;
		if (overs >= minovers && overs <= maxovers)
			break;
		cout << "Invalid input...Enter from " << minovers << " to " << maxovers << ": ";
	}
	int balls = overs * 6;

	//Bowlers
	for (int i = 0; i < players.size(); ++i)
	{
		if (players[i].playing_role == bowler)
			players[i].initializeBowler(overs);
	}



	////////////////// Process Scheduling //////////////////

	//Bowling
	vector<Player*> prbowler;
	for (int i = 0; i < players.size(); ++i)
		if (players[i].playing_role == bowler)
			prbowler.push_back(&players[i]);
	sortball(prbowler, prbowler.size());

	//Batting
	vector<Player*> prbatter;
	for (int i = 0; i < players.size(); ++i)
		if (players[i].playing_role == batter || players[i].playing_role == allrounder)
			prbatter.push_back(&players[i]);
	sortbat(prbatter, prbatter.size(), batshtype);
	vector<Player*> leftbatters;
	//if (batshtype == "SRTF")
		leftbatters = prbatter;
		

	queue<Player*> q1, q2;
	vector<Player*> seq1, seq2;
	int t1 = 0, t2 = 0;
	int overballs = 6;	//Quantum time
	bool start = 1, skip = 0;

	// Main Bowling Loop
	while (!q1.empty() || start)
	{
		start = 0;

		// Arrival of New Processes
		for (int i = 0; i < prbowler.size(); ++i)
		{
			if (prbowler[i]->arrtime >= t1 && prbowler[i]->arrtime == t1)
			{
				q1.push(prbowler[i]);
				if (bowlshtype == "RR")
					prbowler[i]->qtime = overballs;
				else
					prbowler[i]->qtime = 0;
				seq1.push_back(prbowler[i]);
				//cout << "Player-" << prbowler[i]->playerid << " arrived at " << t1 << endl;
			}
		}

		++t1;
		if (bowlshtype == "RR")
			q1.front()->qtime--;
		else
			q1.front()->qtime++;	//qtime is used as VRUNTIME here in SJF
		q1.front()->pendingt--;
		q1.front()->runs_conceded += q1.front()->runs_per_ball + (q1.front()->qtime / 6) * 0.1;
		q1.front()->wickets_taken += q1.front()->wickets_per_ball;
		//cout << "t " << t1 << ": " << "P" << q1.front()->playerid << " (" << q1.front()->qtime << ")    " << ((q1.front()->balls_bowled - q1.front()->pendingt - 1) / 6) + 1 << endl;

		if (q1.front()->pendingt <= 0)
		{
			q1.front()->completion_time = t1;
			//cout << "Player-" << q1.front()->playerid << " completed at " << t1 << endl;
			q1.pop();
			skip = 1;
		}
		if (bowlshtype == "RR" && skip == 0 && q1.front()->qtime <= 0)
		{
			skip = 0;
			q1.front()->qtime = overballs;
			q1.push(q1.front());
			seq1.push_back(q1.front());
			q1.pop();
		}
	}

	// Main Batting Loop

	start = 1;
	skip = 0;
	while ((!q2.empty() && (!leftbatters.empty() || batshtype == "SJF")) || start)
	{
		start = 0;

		// Arrival of New Processes
		for (int i = 0; i < leftbatters.size(); ++i)
		{
			if (!leftbatters[i]->isdone && leftbatters[i]->arrtime <= t2 && (leftbatters[i]->arrtime == t2 || batshtype == "SRTF") && (batshtype == "SJF" || q2.size() < 2))
			{
				q2.push(leftbatters[i]);
				leftbatters[i]->qtime = 0;
				seq2.push_back(leftbatters[i]);
				//cout << "Player-" << leftbatters[i]->playerid << " arrived at " << t2 << endl;
				leftbatters[i]->isdone = 1;
				players_arrived++;
				
				if (batshtype == "SRTF" && q2.back()->pendingt < q2.front()->pendingt)
				{
					q2.push(q2.front());
					q2.pop();
					q2.front()->pendingt = q2.front()->pendingt * (1 - 0.2 * q2.front()->current_form_index);
					q2.front()->runs_per_ball = q2.front()->runs_per_ball / (1 - 0.2 * q2.front()->current_form_index);
					seq2.push_back(q2.front());
				}
				
			}
		}
		if (batshtype == "SRTF" && q2.back()->pendingt < q2.front()->pendingt)
		{
			q2.push(q2.front());
			q2.pop();
			seq2.push_back(q2.front());
		}


		++t2;
		if (batshtype == "SRTF")
			q2.front()->qtime++;/////////////
		else	// if (batshtype == "SJF")
			q2.front()->qtime++;	//qtime is used as VRUNTIME here in SJF
		q2.front()->pendingt--;
		q2.front()->balls_faced++;
		q2.front()->runs_scored += q2.front()->runs_per_ball;
		//cout << "t " << t2 << ": " << "P" << q2.front()->playerid << " (" << q2.front()->qtime << ")    " << ((q2.front()->balls_faced - 1) / 6) + 1 << endl;

		if (q2.front()->pendingt <= 0)
		{
			q2.front()->completion_time = t2;
			q2.front()->isdismissed = 1;
			//cout << "Player-" << q2.front()->playerid << " completed at " << t2 << endl;
			q2.pop();
			skip = 1;
		}
	}


	//Making them int
	for (int i = 0; i < prbowler.size(); ++i)
	{
		// Bowler
		if (prbowler[i]->wickets_taken - (int)prbowler[i]->wickets_taken >= 0.5)
			prbowler[i]->wickets_taken = ceil(prbowler[i]->wickets_taken);
		else
			prbowler[i]->wickets_taken = floor(prbowler[i]->wickets_taken);

		if (prbowler[i]->runs_conceded - (int)prbowler[i]->runs_conceded >= 0.5)
			prbowler[i]->runs_conceded = ceil(prbowler[i]->runs_conceded);
		else
			prbowler[i]->runs_conceded = floor(prbowler[i]->runs_conceded);

		// Batter
		if (prbatter[i]->runs_scored - (int)prbatter[i]->runs_scored >= 0.5)
			prbatter[i]->runs_scored = ceil(prbatter[i]->runs_scored);
		else
			prbatter[i]->runs_scored = floor(prbatter[i]->runs_scored);
	}


	/////// Player Bowling Sequence ///////

	cout << "\n\nUsing " << bowlshtype << ":\nBowler Sequence:\nPlayer IDs: ";
	for (int i = 0; i < seq1.size(); ++i)
		cout << seq1[i]->playerid << "  ";

	cout << "\n\nBowlers Stats:\nPid\tRuns\tW\tBalls\n";
	for (int i = 0; i < prbowler.size(); ++i)
		cout << prbowler[i]->playerid << "\t" << prbowler[i]->runs_conceded << "\t" << prbowler[i]->wickets_taken << "\t" << prbowler[i]->balls_bowled << "\n";



	/////// Player Batting Sequence ///////

	cout << "\n\nUsing " << batshtype << ":\nBatter Sequence:\nPlayer IDs: ";
	for (int i = 0; i < seq2.size(); ++i)
		cout << seq2[i]->playerid << "  ";

	cout << "\n\nBatters Stats:\nPid\tRuns\tBalls\tOut?\n";
	for (int i = 0; i < prbatter.size(); ++i)
		cout << prbatter[i]->playerid << "\t" << prbatter[i]->runs_scored << "\t" << prbatter[i]->balls_faced << "\t" << prbatter[i]->isdismissed << "\n";

	/////////////////// Uploading Data ///////////////////

	vector<float> Batting_Avg, Strike_Rate, Bowling_Avg, Economy_Rate, Performance, Current_Form_Index;
	int runs_conceded, balls_bowled, wickets_taken, runs_scored, balls_faced, isdismissed;

	char ch;
	cout << "\nDo you want to update the new data? (Y/N) : ";
	cin.ignore();
	ch = getchar();
	if (ch == 'y' || ch == 'Y')
	{
		for (int i = 0; i < players.size(); ++i)
		{
			string newline, line, word, filenametemp = players[i].name + ".csv";
			vector<string> rows;
			if (players[i].playing_role == bowler)
			{
				newline = to_string((int)players[i].runs_conceded) + "," + to_string(players[i].balls_bowled) + "," + to_string((int)players[i].wickets_taken);

				fstream file(filenametemp, ios::in);
				if (!file)
				{
					fstream file(filenametemp, ios::out);

					file << "Runs_Conceded,Balls_Bowled,Wickets_Taken\n";
					file << newline;
				}
				else
				{
					getline(file, line);
					rows.push_back(line);
					rows.push_back(newline);
					for (int i = 0; i < 9 && getline(file, line); ++i)
						rows.push_back(line);

					runs_conceded = 0;
					balls_bowled = 0;
					wickets_taken = 0;

					fstream file(filenametemp, ios::out);
					file << rows[0] << endl;
					for (int i = 1; i < rows.size(); ++i)
					{
						file << rows[i] << endl;
						if (i > 0)
						{
							stringstream ss(rows[i]);
							vector <string> row;

							while (getline(ss, word, ','))
								row.push_back(word);

							runs_conceded += stoi(row[0]);
							balls_bowled += stoi(row[1]);
							wickets_taken += stoi(row[2]);
						}
					}
				}
				file.close();

				int overs_bowled = balls_bowled / 6,
					wicket_avg = wickets_taken / overs_bowled,
					standard_economy = runs_conceded / overs_bowled;
				Batting_Avg.push_back(0);
				Strike_Rate.push_back(0);
				Bowling_Avg.push_back((float)runs_conceded / wickets_taken);
				Economy_Rate.push_back((float)runs_conceded / overs_bowled);
				Performance.push_back((((wicket_avg * 0.7) / Bowling_Avg[i]) + ((Economy_Rate[i] * 0.3) / standard_economy)) * 10000);
				Current_Form_Index.push_back(((float)wickets_taken / balls_bowled) * Economy_Rate[i] * 0.01);
			}
			else	//Batter
			{
				newline = to_string((int)players[i].runs_scored) + "," + to_string(players[i].balls_faced) + "," + to_string((int)players[i].isdismissed);

				fstream file(filenametemp, ios::in);
				if (!file)
				{
					fstream file(filenametemp, ios::out);

					file << "Runs_Scored,Balls_Faced,Is_Dismissed\n";
					file << newline;
				}
				else
				{
					getline(file, line);
					rows.push_back(line);
					rows.push_back(newline);
					for (int i = 0; i < 9 && getline(file, line); ++i)
						rows.push_back(line);

					runs_scored = 0;
					balls_faced = 0;
					isdismissed = 0;

					fstream file(filenametemp, ios::out);
					for (int i = 0; i < rows.size(); ++i)
					{
						file << rows[i] << endl;
						if (i > 0)
						{
							stringstream ss(rows[i]);
							vector <string> row;

							while (getline(ss, word, ','))
								row.push_back(word);

							runs_scored += stoi(row[0]);
							balls_faced += stoi(row[1]);
							isdismissed += stoi(row[2]);
						}
					}
				}
				file.close();

				Batting_Avg.push_back((float)runs_scored / isdismissed);
				Strike_Rate.push_back(((float)runs_scored / balls_faced) * 100);
				Bowling_Avg.push_back(0);
				Economy_Rate.push_back(0);
				Performance.push_back((Batting_Avg[i] * 0.6) + (Strike_Rate[i] * 0.4));
				Current_Form_Index.push_back(((float)runs_scored / balls_faced) * Strike_Rate[i] * 0.01);
			}
		}
		fstream file(filename, ios::out);
		string line = "PlayerID,Name,Batting_Avg,Strike_Rate,Bowling_Avg,Economy_Rate,Performance,Current_Form_Index,Playing_Role\n";
		file << line;
		for (int i = 0; i < players.size(); ++i)
		{
			line = to_string(playerids[i]) + "," + pnames[i] + "," + to_string(Batting_Avg[i]) + "," + to_string(Strike_Rate[i]) + "," + to_string(Bowling_Avg[i]) + "," + to_string(Economy_Rate[i]) + "," + to_string(Performance[i]) + "," + to_string(Current_Form_Index[i]) + "," + proles[i];
			file << line << endl;
		}
		file.close();

		cout << "\nData Updated...\n";
	}
	else
		cout << "\nExiting Program...\n";

	return 0;
}


void parseCSV(vector<Player>& players, string filename)
{
	ifstream file(filename);

	string line, word;
	getline(file, line);		//Discard header

	while (getline(file, line))
	{
		stringstream ss(line);		//To read each word by splitting string with ','
		vector <string> row;

		while (getline(ss, word, ','))
			row.push_back(word);

		if (row.size() == 9)
			players.emplace_back(stoi(row[0]), row[1], stof(row[2]), stof(row[3]), stof(row[4]), stof(row[5]), stof(row[6]), stof(row[7]), row[8]);
	}
}