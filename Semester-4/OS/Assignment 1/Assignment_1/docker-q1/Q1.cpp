#include <iostream>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<string> weapons = {"Pistol", "Revolver"};
vector<int> damages = {25, 50};

class Player
{
public:
	int health, damage, x, y;
	string weapon;
	// bool isAlive;

	Player(int h = 100, int weaponNum = 0, int X = 0, int Y = 0)
	{
		health = h;
		weapon = weapons[weaponNum];
		damage = damages[weaponNum];
		x = X;
		y = Y;
		// isAlive = 1;
	}
	Player(const Player &p)
	{
		health = p.health;
		weapon = p.weapon;
		damage = p.damage;
		x = p.x;
		y = p.y;
		// isAlive = p.isAlive;
	}

	bool isalive()
	{
		if (health > 0)
			return true;
		else
			return false;
	}
};

class Zombie
{
public:
	int health, damage, x, y;

	Zombie(int h = 50, int d = 10, int X = 0, int Y = 0)
	{
		health = h;
		damage = d;
		x = X;
		y = Y;
	}
	bool isalive()
	{
		if (health > 0)
			return true;
		else
			return false;
	}
};

int main()
{
	srand(time(0));
	int zombie_count = (523 * ((rand() % 10) + 1)) % 20,
		WeaponAssign1 = rand() % weapons.size(), WeaponAssign2 = WeaponAssign1,
		player_health = 100, zombie_health = 50, zombie_damage = 10;
	int zombieAliveCount = zombie_count;

	while (WeaponAssign1 == WeaponAssign2)
		WeaponAssign2 = rand() % weapons.size();

	cout << "\n"
		 << " --------------------------------------------------\n"
		 << " |                                                |\n"
		 << " |               🙎 MAN VS ZOMBIES 🧟             |\n" // 🙎🏿‍♂️ 🧟
		 << " |                                                |\n"
		 << " --------------------------------------------------\n\n"

		 << "Player 1: [Health: " << player_health << "]\t[Weapon: " << weapons[WeaponAssign1] << "]\n"
		 << "Player 2: [Health: " << player_health << "]\t[Weapon: " << weapons[WeaponAssign2] << "]\n"
		 << "Zombies:  " << zombie_count << "\t\t[Health: " << zombie_health << "]\n\n"
		 << "Let the GaMe BEGINNN!!!\n\n\n";

	pid_t managerId = fork(), player1id, player2id;
	bool spawnplayers = 0, spawnzombies = 0, ArePlayersAlive = 1;

	// Declaring classes
	// Player player1(player_health, WeaponAssign1, 15, 7),
	//	player2(player_health, WeaponAssign2, 15, 2);
	// vector<Zombie> zombies;

	// Declaring pipes
	int pp1[2], pp2[2], pm1[2], pm2[2];
	pipe(pp1);
	pipe(pp2);
	pipe(pm1);
	pipe(pm2);
	vector<int *> zp;
	for (int i = 0; i < zombie_count; ++i)
	{
		int *arr = new int[2];
		zp.push_back(arr);
	}
	vector<pid_t> zombiesId(zombie_count);
	bool turn = 0; // 0: Players, 1: Zombies
	while (ArePlayersAlive && zombieAliveCount > 0)
	{
		if (managerId > 0) // Parent
		{
			Player player1, player2;
			vector<Zombie> zombies;
			if (spawnplayers == 0)
			{
				Player tempp1(player_health, WeaponAssign1, 15, 7),
					tempp2(player_health, WeaponAssign2, 15, 2);

				player1 = tempp1;
				player2 = tempp2;
				for (int i = 0; i < zombie_count; ++i)
				{
					zombies.emplace_back(zombie_health, zombie_damage, 0, i);
				}

				spawnplayers = 1;
			}
			else
			{
				if (turn == 0) // Player's turn
				{
					close(pp1[1]);
					close(pp2[1]);
					char action1, action2;
					if (player1.isalive())
					{
						read(pp1[0], &action1, sizeof(action1));
						if (action1 == 'a' || action1 == 'A')
						{
							player1.x--;
						}
						else if (action1 == 'w' || action1 == 'W')
						{
							player1.y--;
						}
						else if (action1 == 's' || action1 == 'S')
						{
							player1.y++;
						}
						else if (action1 == 'd' || action1 == 'D')
						{
							player1.x++;
						}
						else if (action1 == '1')
						{
							for (int i = 0; i < zombie_count; ++i)
							{
								if (zombies[i].isalive())
								{
									zombies[i].health -= player1.damage;
									if (zombies[i].health <= 0)
										--zombieAliveCount;
									break;
								}
							}
						}
						else if (action1 == '2')
						{
							player1.health = 0;
						}
					}

					if (player2.isalive())
					{
						read(pp2[0], &action2, sizeof(action2));
						if (action2 == 'a' || action2 == 'A')
						{
							player2.x--;
						}
						else if (action2 == 'w' || action2 == 'W')
						{
							player2.y--;
						}
						else if (action2 == 's' || action2 == 'S')
						{
							player2.y++;
						}
						else if (action2 == 'd' || action2 == 'D')
						{
							player2.x++;
						}
						else if (action2 == '1')
						{
							for (int i = 0; i < zombie_count; ++i)
							{
								if (zombies[i].isalive())
								{
									zombies[i].health -= player2.damage;
									if (zombies[i].health <= 0)
										--zombieAliveCount;
									break;
								}
							}
						}
						else if (action2 == '2')
						{
							player2.health = 0;
						}
					}
				}
				else // Zombies' Turn
				{
					close(pm1[0]);
					close(pm2[0]);
					bool p1dead = 0, p2dead = 0;
					for (int i = 0; i < zombie_count; ++i)
					{
						if (player1.isalive())
						{
							bool ver = 1, hor = 1;
							if (player1.x - zombies[i].x == 0)
								hor = 0;
							else if (player1.x - zombies[i].x > 0)
								zombies[i].x++;
							else
								zombies[i].x--;

							if (player1.y - zombies[i].y == 0)
								ver = 0;
							else if (player1.y - zombies[i].y > 0)
								zombies[i].y++;
							else
								zombies[i].y--;

							if (!ver && !hor)
								player1.health -= zombies[i].damage;
						}
						else

						{
							bool ver = 1, hor = 1;
							if (player2.x - zombies[i].x == 0)
								hor = 0;
							else if (player2.x - zombies[i].x > 0)
								zombies[i].x++;
							else
								zombies[i].x--;

							if (player2.y - zombies[i].y == 0)
								ver = 0;
							else if (player2.y - zombies[i].y > 0)
								zombies[i].y++;
							else
								zombies[i].y--;

							if (!ver && !hor)
								player2.health -= zombies[i].damage;
						}
						if (player1.isalive() == 0)
							p1dead = 1;
						if (player2.isalive() == 0)
							p2dead = 1;
						write(pm1[1], &p1dead, sizeof(p1dead));
						write(pm2[1], &p2dead, sizeof(p2dead));
					}
				}
			}

			waitpid(player1id, NULL, 0);
			waitpid(player2id, NULL, 0);

			for (int i = 0; i < zombie_count; ++i)
			{
				waitpid(zombiesId[i], NULL, 0);
			}
		}
		else if (managerId == 0) // Child
		{
			if (spawnzombies == 0)
			{
				player1id = fork();
				player2id = fork();

				
				for (int i = 0; i < zombie_count; ++i)
				{
					zombiesId[i] = fork();
				}
				spawnzombies = 1;
			}
			else
			{
				if (turn == 0) // Players Turn
				{
					bool p1dead = 0, p2dead = 0;
					read(pm1[0], &p1dead, sizeof(p1dead));
					read(pm2[0], &p2dead, sizeof(p2dead));
					if (player1id > 0 && !p1dead)
					{
						close(pp1[0]);
						close(pm1[1]);
						int choice;
						cout << "Do you want to attack or move:\n1. Attack\n2. Move\n3. KYS\n";
						while (true)
						{
							cout << "Choose: ";
							cin >> choice;
							if (choice == 1 || choice == 2 || choice == 3)
								break;
							cout << "Invalid input...Enter only 1, 2 or 3: ";
						}

						char inp1;
						if (choice == 1)
						{
							inp1 = '1'; // Attack
						}
						else if (choice == 3)
						{
							inp1 = '2'; // Self Kill
						}
						else
						{

							cout << "Enter your move (A, W, S, D):\n";
							while (true)
							{
								cout << "Enter: ";
								cin >> inp1;
								if (inp1 == 'a' || inp1 == 'w' || inp1 == 's' || inp1 == 'd' || inp1 == 'A' || inp1 == 'W' || inp1 == 'S' || inp1 == 'D')
									break;
								cout << "Invalid input...Enter only (A, W, S, D): ";
							}
						}
						write(pp1[1], &inp1, sizeof(inp1));

						wait(NULL);
					}
					else
					{
					}

					if (player2id > 0 && !p2dead)
					{
						close(pp2[0]);
						close(pm2[1]);
						int choice;
						cout << "Do you want to attack or move:\n1. Attack\n2. Move\n3. KYS\n";
						while (true)
						{
							cout << "Choose: ";
							cin >> choice;
							if (choice == 1 || choice == 2 || choice == 3)
								break;
							cout << "Invalid input...Enter only 1, 2 or 3: ";
						}

						char inp2;
						if (choice == 1)
						{
							inp2 = '1'; // Attack
						}
						else if (choice == 3)
						{
							inp2 = '2'; // Self Kill
						}
						else
						{

							cout << "Enter your move (A, W, S, D):\n";
							while (true)
							{
								cout << "Enter: ";
								cin >> inp2;
								if (inp2 == 'a' || inp2 == 'w' || inp2 == 's' || inp2 == 'd' || inp2 == 'A' || inp2 == 'W' || inp2 == 'S' || inp2 == 'D')
									break;
								cout << "Invalid input...Enter only (A, W, S, D): ";
							}
						}
						write(pp2[1], &inp2, sizeof(inp2));

						wait(NULL);
					}
					else
					{
					}
					if (p1dead && p2dead)
						ArePlayersAlive = 0;
					turn = 1;
				}
				else // Zombies Turn
				{
					// No input its AI
					turn = 0;
				}
			}
		}
		else
			cout << "\nError in Game Manager Forking!\n";
	}
	if (ArePlayersAlive)
		cout << "\n\nCongratulations!! The PLAYERS Won!!\n";
	else
		cout << "\n\nR.I.P Humans...The Zombies Won!!";

	return 0;
}
