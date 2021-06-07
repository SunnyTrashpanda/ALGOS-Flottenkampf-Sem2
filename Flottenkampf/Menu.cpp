#include "Menu.h"
#include "Teams.h"
#include "Ship.h"
#include "Hunter.h"
#include "Destroyer.h"
#include "Tank.h"

#include <iostream>
#include <time.h>

Menu::Menu()
{
	std::cout << "Hello and welcome to FLOTTENKAMPF" << std::endl;
	Teams team1 = setTeams();
	Teams team2 = setTeams();

	/*getStats(team1, 0);		Kann überprüfen ob team1 und team2 != NULL
	getStats(team2, 0);*/

	play(team1, 0, team2, 0);
}

Teams Menu::setTeams()
{
	Teams team;
	std::cout << "\nDeclare Team name:";
	std::cin >> team.teamName;
	std::cout << "Team is now called: " << team.teamName << std::endl;

	std::cout << "\nset up your ships:" << std::endl;
	std::cout << "\nselect up to 9 ships for your team!" << std::endl;
	team = createTeam(team);

	/*std::cout << "\nDeclare Team 2 name:";
	std::cin >> team2.teamName;
	std::cout << "Team 2 is now called: " << team2.teamName << std::endl;

	std::cout << "\nSet up your ships:" << std::endl;
	std::cout << "\nSelect up to 9 ships for your team!" << std::endl;
	createTeam(team2);*/

	return team;
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
			break;
		case 'd':
			tmpTeam.ships[arrPosition] = destroyer;
			break;
		case 't':
			tmpTeam.ships[arrPosition] = tank;
			break;
		default: std::cout << "no ship to give senpai TT^TT" << std::endl;
	}

	return tmpTeam;
}

Teams Menu::createTeam(Teams Team)
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
			return tmpTeam;
		}
		countShips++;
	}

	return tmpTeam;
}

void Menu::setTargetShip()
{

}

void Menu::getStats(Teams tmpTeam, int arrPosition)
{
	std::cout << "Team name: " << tmpTeam.teamName << std::endl;
	std::cout << "Ship type: " << tmpTeam.ships[arrPosition].getShipType() << std::endl;
	std::cout << "Ship size: " << tmpTeam.ships[arrPosition].getShipSize() << std::endl;
	std::cout << "Ship attak: " << tmpTeam.ships[arrPosition].getShipAtk() << std::endl;
	std::cout << "Ship defense: " << tmpTeam.ships[arrPosition].getShipDef() << std::endl;
}

char Menu::getShipType(Teams tmpShip, int arrPosition)
{
	return tmpShip.ships[arrPosition].getShipType();
}

int Menu::rollDice()
{
	int rolledNr = 0;
	srand(time(NULL));

	rolledNr = rand() % 10;

	return rolledNr;
}

void Menu::attakShip(Teams targetShip, int arrPosTargShip, int damage)
{
	targetShip.ships[arrPosTargShip].getDamage(damage);
}

//Teams Menu::destroyShip(Teams tmpShip, int arrPosition)
//{
//	/*Ship* delShip = new Ship;
//	delShip = tmpShip.ships[arrPosition];*/
//
//	//Ship delShip = tmpShip.ships[arrPosition];
//
//	delete &tmpShip.ships[arrPosition];
//}

void Menu::play(Teams atkShip, int arrPosAtkShip, Teams targetShip, int arrPosTargShip)
{
	int damage = atkShip.ships[arrPosAtkShip].getShipAtk();
	int chance = rollDice();
	int targetSize = targetShip.ships[arrPosTargShip].getShipSize();
	int type = getShipType(atkShip, arrPosAtkShip);

	if (type == 'D')
	{
		std::cout << "Ship is destroyer" << std::endl;
		chance += 2;
	}

	if (chance >= targetSize)
	{
		if (type == 'H')
		{
			std::cout << "Ship is hunter" << std::endl;

			if (chance <= 9)
			{
				std::cout << "Crit Hit" << std::endl;
				/*attakShip(targetShip, arrPosTargShip, damage*2);
				getStats(targetShip, arrPosTargShip);*/
			}
		}
		else if (type == 'T')
		{
			std::cout << "Ship is Tank" << std::endl;
			/*attakShip(targetShip, arrPosTargShip, damage);
			getStats(targetShip, arrPosTargShip);
			play(atkShip, arrPosAtkShip, targetShip, arrPosTargShip);*/
		}
		else
		{
			std::cout << "Normal attak" << std::endl;
			/*attakShip(targetShip, arrPosTargShip, damage);
			getStats(targetShip, arrPosTargShip);*/
		}
	}
	else
	{
		std::cout << "Attak failed - enemy attaks" << std::endl;
		/*attakShip(atkShip, arrPosAtkShip, damage);
		getStats(atkShip, arrPosAtkShip);*/
	}
}