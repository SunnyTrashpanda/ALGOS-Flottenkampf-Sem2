#include "Menu.h"
#include "Teams.h"
#include "Ship.h"
#include "Hunter.h"
#include "Destroyer.h"
#include "Tank.h"

#include <iostream>

Menu::Menu()
{
	std::cout << "Hello and welcome to FLOTTENKAMPF" << std::endl;
	setTeams();
}

void Menu::setTeams()
{
	Teams team1;
	Teams team2;

	Hunter h1;
	Hunter h2;
	Destroyer d1;
	Tank t1;

	/*team1.ships[0] = h1;
	team1.ships[1] = d1;

	team2.ships[0] = h2;
	team2.ships[1] = t1;*/

	std::cout << "\nDeclare Team 1 name:";
	std::cin >> team1.teamName;
	std::cout << "Team 1 is now called: " << team1.teamName << std::endl;

	std::cout << "\nset up your ships:" << std::endl;
	std::cout << "\nselect up to 9 ships for your team!" << std::endl;
	createTeam(team1);

	/*team1.ships[0].shipType = 'h';
	team1.ships[0].size = 4;
	team1.ships[0].atk = 30;
	team1.ships[0].def = 75;

	team1.ships[1].shipType = 'd';
	team1.ships[1].size = 6;
	team1.ships[1].atk = 60;
	team1.ships[1].def = 150;*/

	std::cout << "\nDeclare Team 2 name:";
	std::cin >> team2.teamName;
	std::cout << "Team 2 is now called: " << team2.teamName << std::endl;

	std::cout << "\nSet up your ships:" << std::endl;
	std::cout << "\nSelect up to 9 ships for your team!" << std::endl;
	createTeam(team2);

	/*team2.ships[0].shipType = 'h';
	team2.ships[0].size = 4;
	team2.ships[0].atk = 30;
	team2.ships[0].def = 75;

	team2.ships[1].shipType = 'd';
	team2.ships[1].size = 6;
	team2.ships[1].atk = 60;
	team2.ships[1].def = 150;*/
}

Teams Menu::addShip(char shipType, Teams tmpTeam, int arrPosition)
{
	Hunter hunter;
	Destroyer destroyer;
	Tank tank;

	switch (shipType)
	{
		case 'h':
			tmpTeam.ships[arrPosition] = hunter;
			/*tmpTeam.ships[arrPosition].shipType = shipType;
			tmpTeam.ships[arrPosition].size = 4;
			tmpTeam.ships[arrPosition].atk = 30;
			tmpTeam.ships[arrPosition].def = 75;*/
			break;
		case 'd':
			tmpTeam.ships[arrPosition] = destroyer;
			/*tmpTeam.ships[arrPosition].shipType = shipType;
			tmpTeam.ships[arrPosition].size = 6;
			tmpTeam.ships[arrPosition].atk = 60;
			tmpTeam.ships[arrPosition].def = 150;*/
			break;
		case 't':
			tmpTeam.ships[arrPosition] = tank;
			/*tmpTeam.ships[arrPosition].shipType = shipType;
			tmpTeam.ships[arrPosition].size = 8;
			tmpTeam.ships[arrPosition].atk = 50;
			tmpTeam.ships[arrPosition].def = 250;*/
			break;
		default: std::cout << "no ship to give senpai TT^TT" << std::endl;
	}

	return tmpTeam;
}

void Menu::createTeam(Teams Team)
{
	char playerInput = 'a';
	int countShips = 0;
	Teams tmpTeam = Team;

	while (playerInput != 'x' || countShips == 9)
	{
		std::cout << "\nYou have " << countShips << " ships in your Team ..." << std::endl;
		std::cout << "h - Hunter | d - Destroyer | t - Tank | x - no more ships" << std::endl;

		std::cin >> playerInput;

		while (playerInput != 'h' && playerInput != 'd' && playerInput != 't' && playerInput != 'x')
		{
			std::cout << "Invalid input. Please try again:" << std::endl;
			std::cin >> playerInput;
		}

		if (playerInput != 'x')
		{
			tmpTeam = addShip(playerInput, tmpTeam, countShips);
			getStats(tmpTeam, countShips);
		}
		else
		{
			return;
		}
		countShips++;
	}
}

void Menu::getStats(Teams tmpTeam, int arrPosition)
{
	std::cout << "Team name: " << tmpTeam.teamName << std::endl;
	std::cout << "Ship type: " << tmpTeam.ships[arrPosition].getShipType() << std::endl;
	std::cout << "Ship size: " << tmpTeam.ships[arrPosition].getShipSize() << std::endl;
	std::cout << "Ship attak: " << tmpTeam.ships[arrPosition].getShipAtk() << std::endl;
	std::cout << "Ship defense: " << tmpTeam.ships[arrPosition].getShipDef() << std::endl;
	/*std::cout << "Team name: " << tmpTeam.teamName << std::endl;
	std::cout << "Ship type: " << tmpTeam.ships[arrPosition].shipType << std::endl;
	std::cout << "Ship size: " << tmpTeam.ships[arrPosition].size << std::endl;
	std::cout << "Ship attak: " << tmpTeam.ships[arrPosition].atk << std::endl;
	std::cout << "Ship defense: " << tmpTeam.ships[arrPosition].def << std::endl;*/
}

char Menu::getShipType(Teams tmpShip, int arrPosition)
{
	return tmpShip.ships[arrPosition].getShipType();
	//return tmpShip.ships[arrPosition].shipType;
}

Teams Menu::destroyShip(Teams tmpShip, int arrPosition)
{
	/*Ship* delShip = new Ship;
	delShip = tmpShip.ships[arrPosition];*/

	//Ship delShip = tmpShip.ships[arrPosition];

	delete &tmpShip.ships[arrPosition];
}