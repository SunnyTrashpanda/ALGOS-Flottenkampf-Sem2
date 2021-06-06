#pragma once
class Menu
{
private:
	int diceNr;
	char team1Name; //std::string 
	char team2Name;

public:
	Menu();
	void rollDice();
	void setShips();
	void setTeamNames();
	void getStats();
};

