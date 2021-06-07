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
	void setTargetShip();
	void getStats(Teams tmpTeam, int arrPositio);
	char getShipType(Teams tmpShip, int arrPosition);
	int rollDice();
	void attakShip(Teams targetShip, int arrPosTargShip, int damage);
	//Teams destroyShip(Teams tmpShip, int arrPosition);
	void play(Teams atkShip, int arrPosAtkShip, Teams targetShip, int arrPosTargShip);
};

