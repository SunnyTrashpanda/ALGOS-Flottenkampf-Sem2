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
	srand(time(NULL));
	std::cout << "Hello and welcome to FLOTTENKAMPF" << std::endl;
	Teams team1 = setTeams();
	Teams team2 = setTeams();

	Teams* ptrT1 = &team1;
	Teams* ptrT2 = &team2;

	setTargetShip(ptrT1, ptrT2);

	std::cout << team1.targetShip << std::endl;
	std::cout << team2.targetShip << std::endl;

	char playerInput;
	std::cout << "Now let the battle start! \nPlease press s.";
	std::cin >> playerInput; 

	bool endGame = false;

	while(playerInput == 's')
	{
		endGame = oneRound(ptrT1, ptrT2);

		if (!endGame)
		{
			std::cout << "Press 's' to continue";
			std::cin >> playerInput;
		}
		else 
		{
			playerInput = 'x';
		}
	}

	if (team1.shipCount == 0)
	{
		endBattle(team2, team1);
	}
	else
	{
		endBattle(team1, team2);
	}
	
	
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
	std::cout << "Ship type: " << tmpTeam.ships[arrPosition].getShipAtk() << std::endl;
	std::cout << "Ship type: " << tmpTeam.ships[arrPosition].getShipDef() << std::endl;
	std::cout << "Ship defense: " << tmpTeam.ships[arrPosition].getShipDef() << std::endl;
	std::cout << "Ship count: " << tmpTeam.shipCount << std::endl;
	std::cout << "Ship target position: " << tmpTeam.targetShip << std::endl;
}

int Menu::rollDice()
{
	int rolledNr = 0;

	rolledNr = rand() % 10;

	std::cout << "\n----------------------------------------" << std::endl;
	std::cout << "You rolled " << rolledNr << " on hit chance!" << std::endl;

	return rolledNr;
}


bool Menu::attackShip(Teams *atkShip, int arrPosAtkShip, Teams *targetShip, int arrPosTargShip)
{
	Hunter h;
	Destroyer d;
	Tank t;

	int chance = rollDice();
	int atkType = atkShip->ships[arrPosAtkShip].getShipType();
	int targetType = atkShip->ships[arrPosAtkShip].getShipType();
	int damage = atkShip->ships[arrPosAtkShip].getShipAtk();
	int targetSize = targetShip->ships[arrPosTargShip].getShipSize();
	int targetDef = targetShip->ships[arrPosTargShip].getShipDef();

	if (atkType == 'D')
	{
		std::cout << "\nShip is destroyer -> +2 on roll" << std::endl;
		chance += 2;
	}

	if (chance >= targetSize)
	{
		atkShip->exp += 1;

		if (atkType == 'H')
		{
			std::cout << "\nShip is hunter" << std::endl;

			if (chance >= 9)
			{
				std::cout << "\nCrit Hit" << std::endl;
				if (atkShip->exp > 15)
				{
					targetShip->ships[arrPosTargShip].getDamage(h.megaCrit());
					std::cout << "\nMega Hit" << std::endl;
				}
				targetShip->ships[arrPosTargShip].getDamage(h.critHit());
				return false;
			}
			else
			{ 
				std::cout << "\nNormal attack" << std::endl;
				targetShip->ships[arrPosTargShip].getDamage(damage);
				return false;
			}

			if (atkShip->exp > 4) {
				atkShip->ships[arrPosAtkShip].addLife(h.heal());
			}
		}
		else if (atkType == 'T')
		{
			
			if (atkShip->exp > 1 && damage > 30)
			{
				std::cout << "\nAttack Debuff" << std::endl;
				atkShip->ships[arrPosAtkShip].atkDebuff(t.debuffAtk());
			}
			damage = atkShip->ships[arrPosAtkShip].getShipAtk();

			targetShip->ships[arrPosTargShip].getDamage(damage); 

			std::cout << "\nShip is Tank" << std::endl;
			if (targetShip->ships[arrPosTargShip].getShipDef() < 1)
			{
				return false;
			}
			else
			{
				attackShip(atkShip, arrPosAtkShip, targetShip, arrPosTargShip);
			}
			return false;
		}
		else
		{
			std::cout << "\nNormal attack" << std::endl;
			targetShip->ships[arrPosTargShip].getDamage(damage);
			return false;
		}
	}
	else
	{
		std::cout << "\nAttack failed - enemy turn of attack" << std::endl;
		return true;
	}

	/*h.aktDef(targetDef);
	d.aktDef(targetDef);
	t.aktDef(targetDef);

	if (atkType == 'D')
	{
		chance += 2;
	}
	if (chance >= targetSize)
	{
		switch (atkType)
		{
		case 'H':
			switch (targetType)
			{
			case 'H':
				if (chance <= 8)
				{
					h.getDamage(h.getShipAtk());
				}
				else
				{
					h.getDamage(h.critHit());
				}
				targetShip->ships[arrPosTargShip] = h;
				break;

			case 'D':
				if (chance <= 8)
				{
					d.getDamage(h.getShipAtk());
				}
				else
				{
					d.getDamage(h.critHit());
				}
				targetShip->ships[arrPosTargShip] = d;
				break;

			case 'T':
				if (chance <= 8)
				{
					t.getDamage(h.getShipAtk());
				}
				else
				{
					t.getDamage(h.critHit());
				}
				targetShip->ships[arrPosTargShip] = t;
				break;
			}
			return false;
			break;

		case 'D':
			switch (targetType)
			{
			case 'H':
				h.getDamage(d.getShipAtk());
				targetShip->ships[arrPosTargShip] = t;
				break;

			case 'D':
				d.getDamage(d.getShipAtk());
				targetShip->ships[arrPosTargShip] = t;
				break;

			case 'T':
				t.getDamage(d.getShipAtk());
				targetShip->ships[arrPosTargShip] = t;
				break;
			}
			return false;
			break;

		case 'T':
			switch (targetType)
			{
			case 'H':
				h.getDamage(t.getShipAtk());
				targetShip->ships[arrPosTargShip] = h;
				break;

			case 'D':
				d.getDamage(t.getShipAtk());
				targetShip->ships[arrPosTargShip] = d;
				break;

			case 'T':
				t.getDamage(t.getShipAtk());
				targetShip->ships[arrPosTargShip] = t;
				break;
			}
			return false;
			break;
		}
	}*/

}

void Menu::setTargetShip(Teams* tmpTeam1, Teams* tmpTeam2)
{
	int min = 300;
	int targetPosition = 10;
	int min1 = 300;
	int targetPosition1 = 10;

	for (int i = 0; i < tmpTeam2->shipCount; i++)
	{
		int shipDef = tmpTeam2->ships[i].getShipDef();

		if (min1 > shipDef)
		{
			min1 = shipDef;
			targetPosition1 = i;
		}
	}

	for (int i = 0; i < tmpTeam1->shipCount; i++)
	{
		int shipDef = tmpTeam1->ships[i].getShipDef();

		if (min > shipDef)
		{
			min = shipDef;
			targetPosition = i;
		}
	}

	tmpTeam1->targetShip = targetPosition1;
	tmpTeam2->targetShip = targetPosition;
}

bool Menu::oneRound(Teams *team1, Teams *team2)
{

	bool enemyTurn1 = false;
	bool enemyTurn2 = false;
	int i1 = 0;
	int i2 = 0;
	int roundT1 = team1->shipCount;
	int roundT2 = team2->shipCount;

	std::cout << "\n=== Team " << team1->teamName << " is attacking . . . ===" << std::endl;
	do 
	{
		enemyTurn1 = attackShip(team1, i1, team2, team1->targetShip);
		if(!enemyTurn1)
		{
			enemyTurn1 = (i1 < roundT1 - 1) ? false : true;
		}
		i1++;
	} while (enemyTurn1 != true);

	roundT2 = team2->shipCount;

	if (team2->ships[team1->targetShip].getShipDef() < 1)
	{
		std::cout << team2->ships[team1->targetShip].getShipType() << " got destroyed by Team " << team1->teamName << std::endl;
		destroyShip(team2, team1->targetShip);

		setTargetShip(team1, team2);
	}

	roundT2 = team2->shipCount;

	std::cout << "\n=== Team " << team2->teamName << " is attacking . . . ===" << std::endl;
	do
	{
		enemyTurn2 = attackShip(team2, i2, team1, team2->targetShip);
		if (!enemyTurn2)
		{
			enemyTurn2 = (i2 < roundT2 - 1) ? false : true;
		}
		i2++;
	} while (enemyTurn2 != true);

	roundT1 = team1->shipCount;

	if (team1->ships[team2->targetShip].getShipDef() < 1)
	{
		std::cout << team1->ships[team2->targetShip].getShipType() << " got destroyed by Team " << team2->teamName << std::endl;
		destroyShip(team1, team2->targetShip);
		setTargetShip(team1, team2);
	}

	roundT1 = team1->shipCount;

	std::cout << "\n\nTarget stats after Team " << team1->teamName << " attacked: " << std::endl;
	getStats(*team2, team1->targetShip);
	std::cout << "\n\nTarget stats after Team " << team2->teamName << " attack:" << std::endl;
	getStats(*team1, team2->targetShip);

	
	if (roundT1 == 0 || roundT2 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Menu::destroyShip(Teams* tmpShip, int arrPosition)
{
	tmpShip->ships[arrPosition].destroyShip();
	for (int i = arrPosition; i < tmpShip->shipCount-1; i++)
	{
		tmpShip->ships[i] = tmpShip->ships[i+1];
		tmpShip->ships[i+1].destroyShip();
	}
	tmpShip->shipCount -= 1;
}

void Menu::endBattle(Teams teamWin, Teams teamLose)
{
	std::cout << "\n\n\n		Team " << teamWin.teamName << " winns!! :3" << std::endl;
}

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