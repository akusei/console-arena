#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>


using namespace std;


typedef struct WEAPONINFO
{
	int		Dice,
			Faces,
			CriticalMin,
			CriticalMax,
			AttackMultiplier;
	float	Cost;
	char	Name[15];

	WEAPONINFO() { }
	WEAPONINFO(const char *name, int dice, int faces, int criticalMin, int criticalMax, int attackMultiplier, float cost)
	{
		this->Dice = dice;
		this->Cost = cost;
		this->CriticalMax = criticalMax;
		this->CriticalMin = criticalMin;
		this->AttackMultiplier = attackMultiplier;
		this->Faces = faces;
		strcpy_s(this->Name, name);
	}
} WeaponInfo;

typedef struct ARMORINFO
{
	int		ArmorClass,
			DexModifier;
	float	Cost;
	char	Name[16];

	ARMORINFO() { }
	ARMORINFO(const char *name, int armorClass, int dexModifier, float cost)
	{
		this->ArmorClass = armorClass;
		this->DexModifier = dexModifier;
		this->Cost = cost;
		strcpy_s(this->Name, name);
	}
} ArmorInfo;


class Inventory
{
public:
	static void										Load();
	static const std::vector<WeaponInfo>	&GetWeapons();
	static const std::vector<ArmorInfo>		&GetArmor();


private:
	static std::vector<WeaponInfo>	m_Weapons;
	static std::vector<ArmorInfo>	m_Armor;

	Inventory();
	~Inventory();
};

#endif