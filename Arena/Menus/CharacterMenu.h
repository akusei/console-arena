#pragma once
#ifndef CHARACTERMENU_H
#define CHARACTERMENU_H

#include "Menu.h"


using namespace std;


class CharacterMenu : public Menu
{
public:
	CharacterMenu(Player &player, ConLib &console);
	virtual ~CharacterMenu();

	void RunMenu();


private:
	bool Roll(const string &text);
	bool Quit(const string &text) const;
	void InitSubMenus();
	void InitMenuItems();
};

#endif