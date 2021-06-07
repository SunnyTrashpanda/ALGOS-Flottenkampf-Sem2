#pragma once

class Ship
{
private:

protected:
	char type;
	int size;
	int atk;
	int def;


public:
	int getShipAtk();
	int getShipSize();
	int getShipDef();
	char getShipType();
	void getDamage(int damage);
	void destroyShip();
	
	/*void damageTargetShip(Teams atkShip, int arrPosAtkShip, Teams targetShip, int arrPosTargShip);
	void destroyShip(Teams tmpShip, int arrPosition);*/
};

