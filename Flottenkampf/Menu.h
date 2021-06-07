#pragma once
#include "Teams.h"
class Menu
{
private:

public:
	Menu();
	Teams setTeams();
	Teams createTeam(Teams Team);
	Teams addShip(char shipType, Teams tmpTeam, int arrPosition);
	void getStats(Teams tmpTeam, int arrPositio);
	int rollDice();
	bool attackShip(Teams *atkShip, int arrPosAtkShip, Teams *targetShip, int arrPosTargShip);
	int setTargetShip(Teams team1, Teams team2);
	void oneRound(Teams *team1, Teams *team2);

	//void attakShip(Teams targetShip, int arrPosTargShip, int damage);
	//Teams destroyShip(Teams tmpShip, int arrPosition);
};

