#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"
#include "CharacterMenu.h"
#include "FightMenu.h"
#include "HeroesMenu.h"
#include "ShopMenu.h"


using namespace std;


class MainMenu : public Menu
{
public:
	MainMenu(Player &player, ConLib &console);
	virtual ~MainMenu();

	void RunMenu();


private:
	CharacterMenu	*m_CharacterMenu;
	FightMenu		*m_FightMenu;
	ShopMenu		*m_ShopMenu;
	HeroesMenu		*m_HeroesMenu;

	void InitSubMenus();
	void InitMenuItems();
	bool CheckPlayer() const;
	bool CheckNoPlayer() const;

	bool CreateCharacter(const string &text) const;
	bool FallenHeroes(const string &text) const;
	bool ViewStats(const string &text);
	bool PurchaseEquipment(const string &text) const;
	bool Fight(const string &text) const;
	bool Quit(const string &text) const;
};

#endif