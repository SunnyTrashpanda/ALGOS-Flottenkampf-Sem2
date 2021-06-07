#pragma once
#include "Ship.h"
#include <string>

struct Teams
{
	std::string teamName;
	Ship ships[9];
	int shipCount;
	int targetShip;
};