#pragma once
//#include "TeamShips.h"
#include "Ship.h"
#include <string>

/*struct TeamShips
{
	char shipType;
	int size;
	int def;
	int atk;
};*/

struct Teams
{
	std::string teamName;
	//TeamShips ships[9];
	Ship ships[9];
};