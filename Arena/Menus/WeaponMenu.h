#pragma once
#ifndef WEAPONMENU_H
#define WEAPONMENU_H

#include "Menu.h"


using namespace std;


class WeaponMenu : public Menu
{
public:
	WeaponMenu(Player &player, ConLib &console);
	virtual ~WeaponMenu();

	void RunMenu();


private:
	void InitSubMenus();
	void InitMenuItems();
	bool PurchaseWeapon(const string &text) const;
	bool Quit(const string &text) const;
};

#endif