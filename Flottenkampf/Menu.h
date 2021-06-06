#pragma once
#include "Teams.h"
class Menu
{
private:
	int diceNr;

public:
	Menu();
	void rollDice();
	void setTeams();
	void createTeam(Teams Team);
	Teams addShip(char shipType, Teams tmpTeam, int arrPosition);
	void getStats(Teams tmpTeam, int arrPositio);
};

