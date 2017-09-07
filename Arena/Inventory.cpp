#include "Inventory.h"


vector<WeaponInfo>	Inventory::m_Weapons;
vector<ArmorInfo>	Inventory::m_Armor;


Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::Load()
{
	Inventory::m_Weapons.push_back(WeaponInfo("Unarmed Strike", 1, 3, 20, 20, 2, 0.0f));
	Inventory::m_Weapons.push_back(WeaponInfo("Brass Knuckles", 1, 4, 20, 20, 2, 1.0f));
	Inventory::m_Weapons.push_back(WeaponInfo("Dagger", 1, 4, 19, 20, 2, 2.0f));
	Inventory::m_Weapons.push_back(WeaponInfo("Mace", 1, 6, 20, 20, 2, 5.0f));
	Inventory::m_Weapons.push_back(WeaponInfo("Handaxe", 1, 6, 20, 20, 3, 6.0f));
	Inventory::m_Weapons.push_back(WeaponInfo("Shortsword", 1, 6, 19, 20, 2, 6.5f));
	Inventory::m_Weapons.push_back(WeaponInfo("Scimitar", 1, 6, 18, 20, 2, 7.0f));
	Inventory::m_Weapons.push_back(WeaponInfo("Morningstar", 1, 8, 20, 20, 2, 8.0f));
	Inventory::m_Weapons.push_back(WeaponInfo("Spear", 1, 8, 20, 20, 3, 9.0f));
	Inventory::m_Weapons.push_back(WeaponInfo("Longsword", 1, 8, 19, 20, 2, 9.5f));
	Inventory::m_Weapons.push_back(WeaponInfo("Greatclub", 1, 10, 20, 20, 2, 11.0f));
	Inventory::m_Weapons.push_back(WeaponInfo("Halberd", 1, 10, 20, 20, 3, 12.0f));
	Inventory::m_Weapons.push_back(WeaponInfo("Bastard Sword", 1, 10, 19, 20, 2, 12.5f));
	Inventory::m_Weapons.push_back(WeaponInfo("Greataxe", 1, 12, 20, 20, 3, 16.0f));
	Inventory::m_Weapons.push_back(WeaponInfo("Greatsword", 2, 6, 19, 20, 2, 20.0f));

	Inventory::m_Armor.push_back(ArmorInfo("Unarmed", 0, 100, 0.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Padded Armor", 1, 8, 5.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Leather Armor", 2, 6, 10.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Hide Armor", 3, 4, 15.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Studded Leather", 3, 5, 25.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Scale Mail", 4, 3, 50.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Chain Shirt", 4, 4, 100.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Chainmail", 5, 2, 150.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Breastplate", 5, 3, 200.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Splint Mail", 6, 0, 225.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Banded Mail", 6, 1, 250.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Half-Plate", 7, 0, 600.0f));
	Inventory::m_Armor.push_back(ArmorInfo("Full Plate", 8, 1, 1000.0f));
}

const vector<WeaponInfo> &Inventory::GetWeapons()
{
	return Inventory::m_Weapons;
}

const vector<ArmorInfo> &Inventory::GetArmor()
{
	return Inventory::m_Armor;
}