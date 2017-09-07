#pragma once
#ifndef FIGHTMENU_H
#define FIGHTMENU_H

#include "Menu.h"
#include "BattleMenu.h"


using namespace std;


class FightMenu : public Menu
{
public:
	FightMenu(Player &player, ConLib &console);
	virtual ~FightMenu();

	void RunMenu();


private:
	BattleMenu *m_BattleMenu;

	void InitSubMenus();
	void InitMenuItems();

	bool Fight(const string &text);
	bool Quit(const string &text) const;
};

#endif