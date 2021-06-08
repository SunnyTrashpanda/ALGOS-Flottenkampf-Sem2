#include "Hunter.h"

Hunter::Hunter()
{
	type = 'H';
	size = 4;
	atk = 30;
	def = 75;
}

int Hunter::critHit()
{
	return atk*2;
}

int Hunter::megaCrit()
{
	return atk * 5;
}

int Hunter::heal()
{
	return def += 10;
}