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
	void setTargetShip(Teams *tmpTeam1, Teams *tmpTeam2);
	bool oneRound(Teams *team1, Teams *team2);
	void destroyShip(Teams *tmpShip, int arrPosition);
	void endBattle(Teams team1, Teams team2);
};

