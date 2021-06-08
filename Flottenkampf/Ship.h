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
	void aktDef(int newDef);
	void destroyShip();
	void addLife(int heal);
	void atkDebuff(int debuff);
};

