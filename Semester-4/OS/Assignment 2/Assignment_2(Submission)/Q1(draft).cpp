#include <iostream>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

vector<string> weapons = {"Knife", "Pistol"};

class Player
{
public:
	int health;
	string weapon;
	bool isAlive;

	Player(int h = 100, int weaponNum = 0)
	{
		health = h;
		weapon = weapons[weaponNum];
		isAlive = 1;
	}
};

int main()
{
	srand(time(0));
	int zombie_count = (523 * ((rand() % 10) + 1)) % 20,
		WeaponAssign1 = rand() % weapons.size(), WeaponAssign2 = WeaponAssign1,
		player_health = 100, zombie_health = 50;

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

	while (ArePlayersAlive && zombie_count > 0)
	{
		if (managerId > 0) // Parent
		{
			if (spawnplayers == 0)
			{
				player1id = fork();
				player2id = fork();

				Player player1(player_health, WeaponAssign1),
					player2(player_health, WeaponAssign2);
				spawnplayers = 1;
			}
			else
			{
				if (player1id > 0)
					cout << "Player 1: " << getpid() << endl;
				else
					cout << "Player 1(In Child): " << getppid() << "\n\n";
			}
			wait(NULL);
		}
		else if (managerId == 0) // Child
		{
			if (spawnzombies == 0)
			{
				vector<pid_t> zombiesId(zombie_count);
				for (int i = 0; i < zombie_count; ++i)
				{
					// zombiesId[i] = fork();
				}
				spawnzombies = 1;
			}
			else
			{
			}
			
		}
		else
			cout << "\nError in Game Manager Forking!\n";
	}

	return 0;
}
