#pragma once
#ifndef HEROESMENU_H
#define HEROESMENU_H

#include "..\Heroes.h"
#include "Menu.h"


using namespace std;


class HeroesMenu : public Menu
{
public:
	HeroesMenu(Player &player, ConLib &console);
	virtual ~HeroesMenu();

	void RunMenu();


private:
	const int	PAGE_SIZE = 12;
	int			m_CurrentPage;
	int			m_TotalPages;

	bool Quit(const string &text) const;
	bool Back(const string &text);
	bool Next(const string &text);

	void InitSubMenus();
	void InitMenuItems();

	void FormatHeroes(const vector<HeroInfo> &heroes);
};

#endif