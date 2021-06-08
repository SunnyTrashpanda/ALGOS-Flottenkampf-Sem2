#include "Tank.h"

Tank::Tank()
{
	type = 'T';
	size = 8;
	atk = 50;
	def = 250;
}

int Tank::debuffAtk()
{
	return 5;
}