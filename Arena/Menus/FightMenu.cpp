#include "FightMenu.h"

using namespace std;

FightMenu::FightMenu(Player &player, ConLib &console) : Menu("%#15;F%#10;i%#2;ght", player, console)
{
	this->InitSubMenus();
}

FightMenu::~FightMenu()
{
	SAFE_DELETE(this->m_BattleMenu);
}

void FightMenu::InitMenuItems()
{
	this->ClearItems();

	char level[100];
	string str;
	for (int i = 0; i < this->m_Player.HighestLevel() + 1; i++)
	{
		str.clear();
		_itoa_s(i + 1, level, 10);
		str.append("%#3;[%#10;").append(level).append("%#3;]%#15;  Level ").append(level);
		this->AddItem((char *)level, str, bind(&FightMenu::Fight, this, placeholders::_1));
	}

	this->AddItem("b", "%#3;[%#10;B%#3;]%#15;ack to Previous Menu", bind(&FightMenu::Quit, this, placeholders::_1));
}

void FightMenu::InitSubMenus()
{
	this->m_BattleMenu = new BattleMenu(this->m_Player, this->m_Console);
}

void FightMenu::RunMenu()
{
	this->InitMenuItems();
	this->DrawTitle();
	this->DrawMenu();

	this->HandleInput(2, true);
}

bool FightMenu::Fight(const string &text)
{
	bool ret = true;

	int level = atoi(text.c_str());
	this->m_BattleMenu->RunMenu(level);

	if (this->m_Player.IsAlive())
	{
		this->InitMenuItems();
		this->DrawTitle();
		this->DrawMenu();
		ret = false;
	}

	return ret;
}

bool FightMenu::Quit(const string &text) const
{
	return true;
}

