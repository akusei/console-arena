#pragma once
#ifndef BATTLEMENU_H
#define BATTLEMENU_H

#include "Menu.h"


using namespace std;


class BattleMenu : public Menu
{
public:
	BattleMenu(Player &player, ConLib &console);
	virtual ~BattleMenu();

	void RunMenu();
	void RunMenu(int level);


private:
	int		m_Round;
	bool	m_BattleDone;
	Player	*m_Monster;

	void InitSubMenus();
	void InitMenuItems();

	void DoAttack(const Player &attacker, Player &target) const;
	void DoWin(int level);
	void DoDeath();

	bool Battle(const string &text);
	bool Run(const string &text);
};

#endif