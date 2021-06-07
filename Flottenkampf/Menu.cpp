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

	/*getStats(team1, 0);		
	getStats(team2, 0);*/
	//kann überprüfen ob team1 und team2 != null

	team1.targetShip = setTargetShip(team2, team1);
	team2.targetShip = setTargetShip(team1, team2);

	std::cout << team1.targetShip << std::endl;
	std::cout << team2.targetShip << std::endl;

	Teams* ptrT1 = &team1;
	Teams* ptrT2 = &team2;

	oneRound(ptrT1, ptrT2);
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
			tmpTeam.shipCount = countShips+1;
		}
		else
		{
			return tmpTeam;
		}
		countShips++;
	}

	return tmpTeam;
}



void Menu::getStats(Teams tmpTeam, int arrPosition)
{
	std::cout << "Team name: " << tmpTeam.teamName << std::endl;
	std::cout << "Ship type: " << tmpTeam.ships[arrPosition].getShipType() << std::endl;
	std::cout << "Ship size: " << tmpTeam.ships[arrPosition].getShipSize() << std::endl;
	std::cout << "Ship attak: " << tmpTeam.ships[arrPosition].getShipAtk() << std::endl;
	std::cout << "Ship defense: " << tmpTeam.ships[arrPosition].getShipDef() << std::endl;
	std::cout << "Ship count: " << tmpTeam.shipCount << std::endl;
	std::cout << "Ship target position: " << tmpTeam.targetShip << std::endl;
}

int Menu::rollDice()
{
	int rolledNr = 0;
	srand(time(NULL));

	rolledNr = rand() % 10;

	std::cout << "\nYou rolled " << rolledNr << " on hit chance!" << std::endl;

	return rolledNr;
}


bool Menu::attackShip(Teams *tmpAtkShip, int arrPosAtkShip, Teams *tmpTargetShip, int arrPosTargShip)
{
	Teams atkShip = *tmpAtkShip;
	Teams targetShip = *tmpTargetShip;

	int damage = atkShip.ships[arrPosAtkShip].getShipAtk();
	int chance = rollDice();
	int targetSize = targetShip.ships[arrPosTargShip].getShipSize();
	int type = atkShip.ships[arrPosAtkShip].getShipType();

	if (type == 'D')
	{
		std::cout << "\nShip is destroyer -> +2 on roll" << std::endl;
		chance += 2;
	}

	if (chance >= targetSize)
	{
		if (type == 'H')
		{
			std::cout << "\nShip is hunter" << std::endl;

			if (chance >= 9)
			{
				std::cout << "\nCrit Hit" << std::endl;
				targetShip.ships[arrPosTargShip].getDamage(damage*2);

				/*attakShip(targetShip, arrPosTargShip, damage*2);
				getStats(targetShip, arrPosTargShip);*/

				return false;
			}
			else
			{ 
				std::cout << "\nNormal attack" << std::endl;

				return false;
			}
		}
		else if (type == 'T')
		{
			std::cout << "\nShip is Tank" << std::endl;
			targetShip.ships[arrPosTargShip].getDamage(damage);

			/*attakShip(targetShip, arrPosTargShip, damage);
			getStats(targetShip, arrPosTargShip);
			play(atkShip, arrPosAtkShip, targetShip, arrPosTargShip);*/

			return false;
		}
		else
		{
			std::cout << "\nNormal attack" << std::endl;
			targetShip.ships[arrPosTargShip].getDamage(damage);

			/*attakShip(targetShip, arrPosTargShip, damage);
			getStats(targetShip, arrPosTargShip);*/
			return false;
		}
	}
	else
	{
		std::cout << "\nAttack failed - enemy turn of attack" << std::endl;
		return true;
	}
}

int Menu::setTargetShip(Teams team1, Teams team2)
{
	int min = 300;
	int targetPosition = 10;

	for (int i = 0; i < team1.shipCount; i++)
	{
		int shipDef = team1.ships[i].getShipDef();
		min = (min > shipDef) ? shipDef : min;
		targetPosition = (min > shipDef) ? i : 0;
	}

	return targetPosition;
}

void Menu::oneRound(Teams *tmpTeam1, Teams *tmpTeam2)
{
	Teams team1 = *tmpTeam1;
	Teams team2 = *tmpTeam2;

	bool enemyTurn1 = false;
	bool enemyTurn2 = false;
	int i1 = 0;
	int i2 = 0;
	int roundT1 = team1.shipCount;
	int roundT2 = team2.shipCount;

	do 
	{
		enemyTurn1 = attackShip(tmpTeam1, i1, tmpTeam2, team1.targetShip);
		std::cout << enemyTurn1;
		enemyTurn1 = (i1 < roundT1 - 1) ? false : true;
		i1++;
	} while (enemyTurn1 != true);
	std::cout << "\n\nTarget stats after Team " << team2.teamName << "attack:" << std::endl;
	getStats(team2, team1.targetShip);

	do
	{
		enemyTurn2 = attackShip(tmpTeam2, i2, tmpTeam1, team2.targetShip);
		std::cout << enemyTurn2;
		enemyTurn2 = (i2 < roundT2 - 1) ? false : true;
		i2++;
	} while (enemyTurn2 != true);
	std::cout << "\n\nTarget stats after Team " << team1.teamName << "attack:" << std::endl;
	getStats(team1, team2.targetShip);
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

//void Menu::setTargetShip(Teams tmpTeam)
//{
//	int playerInput;
//
//	std::cout << "\nSelect one Ship you want to attack: " << std::endl;
//
//	for (int i = 0; i < tmpTeam.shipCount - 1; i++)
//	{
//		std::cout << "[ " << i << "-" << tmpTeam.ships[i].getShipType() << " ] ";
//	}
//
//	std::cout << "Please select a number: ";
//	std::cin >> playerInput;
//}