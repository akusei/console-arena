#pragma once
#ifndef SHOPMENU_H
#define SHOPMENU_H

#include "Menu.h"
#include "ArmorMenu.h"
#include "WeaponMenu.h"


using namespace std;


class ShopMenu : public Menu
{
public:
	ShopMenu(Player &player, ConLib &console);
	virtual ~ShopMenu();

	void RunMenu();


private:
	ArmorMenu	*m_ArmorMenu;
	WeaponMenu	*m_WeaponMenu;

	void InitSubMenus();
	void InitMenuItems();

	bool BuyArmor(const string &text) const;
	bool BuyWeapon(const string &text) const;
	bool Heal(const string &text) const;
	bool Quit(const string &text) const;
};

#endif