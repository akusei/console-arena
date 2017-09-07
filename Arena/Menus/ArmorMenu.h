#pragma once
#ifndef ARMORMENU_H
#define ARMORMENU_H

#include "Menu.h"


using namespace std;


class ArmorMenu : public Menu
{
public:
	ArmorMenu(Player &player, ConLib &console);
	virtual ~ArmorMenu();

	void RunMenu();


private:
	void InitSubMenus();
	void InitMenuItems();
	bool PurchaseArmor(const string &text) const;
	bool Quit(const string &text) const;
};

#endif