#pragma once
#ifndef MENU_H
#define MENU_H

#include "Callback.h"
#include "..\Global.h"
#include "..\ConLib.h"
#include "..\Player.h"

#include <functional>
#include <map>
#include <vector>


using namespace std;


typedef function<bool(const string &)> HandlerCast;


class Menu
{
public:
	Menu(string title, Player &player, ConLib &console);
	virtual ~Menu();

	virtual void	RunMenu() = 0;
	void			ClearViewPort() const;
	void			DrawBorder() const;

	//ConLib *Console() const;
	//Player *Character() const;


protected:
	int				m_LargestItem;
	ConLib			&m_Console;
	Player			&m_Player;
	const string	m_Title;
	vector<string>  m_MenuItems;

	map<string, HandlerCast> m_Shortcuts;

	void			ReplaceTokens(string &text, const string &attacker, const string &weapon, const string &target, const string &damage) const;
	void			DrawTitle() const;
	void			DrawTitle(const string &title) const;
	void			AddItem();
	void			AddItem(const string &text);
	void			AddItem(const string &shortcut, const string &item, HandlerCast callback);
	void			DrawInput(const string &prompt, bool centered) const;
	void			DrawMenu() const;
	const string	HandleInput(int size, bool isExpected) const;
	void			ClearInput(bool clearAll) const;
	void			ClearTitle() const;
	void			DrawError(const string &error) const;
	void			DrawMessage(const string &msg) const;
	void			ClearError() const;
	void			SetInputPos() const;
	void			ClearItems();
	void			DrawText(const string &text) const;
	string			AddTab(const string &text);

	virtual void	InitSubMenus() = 0;
	virtual void	InitMenuItems() = 0;

private:
	const char BORDER = '\xb0';
};

#endif