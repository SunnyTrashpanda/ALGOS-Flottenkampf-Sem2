#pragma once
#include "Ship.h"

class Hunter : public Ship
{
private:

public:
	Hunter();
	int critHit();
	int megaCrit();
	int heal();
};

