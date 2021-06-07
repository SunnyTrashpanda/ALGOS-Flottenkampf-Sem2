#include "Ship.h"
#include "Teams.h"


char Ship::getShipType()
{
	return type;
}

int Ship::getShipSize()
{
	return size;
}

int Ship::getShipAtk()
{
	return atk;
}

int Ship::getShipDef()
{
	return def;
}

void Ship::getDamage(int damage)
{
	def -= damage;
}

void Ship::destroyShip()
{
	type = NULL;
	size = NULL;
	atk = NULL;
	def = NULL;
}

//void Ship::damageTargetShip(Teams atkShip, int arrPosAtkShip, Teams targetShip, int arrPosTargShip)
//{
//	int atkShipAtk = getShipAtk(atkShip, arrPosAtkShip);
//	int targetShipdef = getShipDef(targetShip, arrPosTargShip);
//
//	targetShip.ships[arrPosTargShip].def = targetShipdef - atkShipAtk;
//
//	if (targetShip.ships[arrPosTargShip].def < 1)
//	{
//		destroyShip(targetShip, arrPosTargShip);
//	}
//}
//
//void getDamage(Teams tmpShip, int arrPosition, int damage)
//{}
//
//void Ship::destroyShip(Teams tmpShip, int arrPosition)
//{
//	tmpShip.ships[arrPosition].shipType = NULL;
//	tmpShip.ships[arrPosition].size = NULL;
//	tmpShip.ships[arrPosition].atk = NULL;
//	tmpShip.ships[arrPosition].def = NULL;
//}