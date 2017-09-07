#include "MainMenu.h"

#include <conio.h>
#include <sstream>


using namespace std;


MainMenu::MainMenu(Player &player, ConLib &console) : Menu(GAMETITLE, player, console)
{
	this->InitMenuItems();
	this->InitSubMenus();
}

MainMenu::~MainMenu()
{
	SAFE_DELETE(this->m_CharacterMenu);
	SAFE_DELETE(this->m_ShopMenu);
	SAFE_DELETE(this->m_FightMenu);
	SAFE_DELETE(this->m_HeroesMenu);
}

void MainMenu::InitMenuItems()
{
	this->AddItem("c", "%#3;[%#10;C%#3;]%#15;reate Character", bind(&MainMenu::CreateCharacter, this, placeholders::_1));
	this->AddItem("h", "%#3;[%#10;H%#3;]%#15;all of Heroes", bind(&MainMenu::FallenHeroes, this, placeholders::_1));
	this->AddItem("s", "%#3;[%#10;S%#3;]%#15;hop", bind(&MainMenu::PurchaseEquipment, this, placeholders::_1));
	this->AddItem("v", "%#3;[%#10;V%#3;]%#15;iew Stats", bind(&MainMenu::ViewStats, this, placeholders::_1));
	this->AddItem("f", "%#3;[%#10;F%#3;]%#15;ight!", bind(&MainMenu::Fight, this, placeholders::_1));
	this->AddItem("q", "%#3;[%#10;Q%#3;]%#15;uit", bind(&MainMenu::Quit, this, placeholders::_1));
}

void MainMenu::InitSubMenus()
{
	this->m_CharacterMenu = new CharacterMenu(this->m_Player, this->m_Console);
	this->m_ShopMenu = new ShopMenu(this->m_Player, this->m_Console);
	this->m_FightMenu = new FightMenu(this->m_Player, this->m_Console);
	this->m_HeroesMenu = new HeroesMenu(this->m_Player, this->m_Console);
}

void MainMenu::RunMenu()
{
	this->DrawTitle();
	this->DrawMenu();

	this->HandleInput(1, true);
}

bool MainMenu::ViewStats(const string &text)
{
	if (!this->CheckPlayer())
		return false;

	char number[100];

	this->DrawTitle("%#15;C%#10;h%#2;aracter %#15;S%#10;t%#2;ats");

	this->ClearItems();

	string str;
	str.append("%#15;Name:           %#10;").append(this->m_Player.Name());
	this->AddItem(str);
	str.clear();

	_itoa_s(this->m_Player.Level(), number, 10);
	str.append("%#15;Level:          %#11;").append(number);
	this->AddItem(str);
	str.clear();

	_itoa_s(this->m_Player.Exp(), number, 10);
	str.append("%#15;Experience:     %#11;").append(number);
	this->AddItem(str);
	str.clear();

	_itoa_s(this->m_Player.Strength(), number, 10);
	str.append("%#15;Strength:       %#11;").append(number);
	this->AddItem(str);
	str.clear();

	_itoa_s(this->m_Player.Dexterity(), number, 10);
	str.append("%#15;Dexterity:      %#11;").append(number);
	this->AddItem(str);
	str.clear();

	_itoa_s(this->m_Player.Constitution(), number, 10);
	str.append("%#15;Constitution:   %#11;").append(number);
	this->AddItem(str);
	str.clear();

	string color = "%#11;";
	int percent = (this->m_Player.HP() * 100) / this->m_Player.MaxHP();
	if (percent <= 50)
		color = "%#9;";
	_itoa_s(this->m_Player.HP(), number, 10);
	str.append("%#15;Hit Points:     ").append(color).append(number);
	this->AddItem(str);
	str.clear();

	_itoa_s(this->m_Player.MaxHP(), number, 10);
	str.append("%#15;Max Hit Points: %#11;").append(number);
	this->AddItem(str);
	str.clear();

	ostringstream ostr;
	ostr << this->m_Player.Gold();
	str.append("%#15;Gold:           %#11;").append(ostr.str());
	this->AddItem(str);
	str.clear();

	str.append("%#15;Weapon:         %#10;").append(this->m_Player.Weapon().Name);
	this->AddItem(str);
	str.clear();

	str.append("%#15;Armor:          %#10;").append(this->m_Player.Armor().Name);
	this->AddItem(str);
	str.clear();

	this->DrawMenu();
	this->DrawInput("Press any key to continue...", true);

	_getch();

	this->ClearItems();
	this->InitMenuItems();
	this->DrawTitle();
	this->DrawMenu();

	return false;
}

bool MainMenu::CheckPlayer() const
{
	if (!this->m_Player.IsAlive())
		this->DrawError("No character has been created!");

	return this->m_Player.IsAlive();
}

bool MainMenu::CheckNoPlayer() const
{
	if (this->m_Player.IsAlive())
		this->DrawError("Character already exists!");

	return !this->m_Player.IsAlive();
}

bool MainMenu::CreateCharacter(const string &text) const
{
	if (this->CheckNoPlayer())
	{
		this->m_CharacterMenu->RunMenu();
		this->DrawTitle();
		this->DrawMenu();
	}

	return false;
}

bool MainMenu::FallenHeroes(const string &text) const
{
	this->m_HeroesMenu->RunMenu();
	this->DrawTitle();
	this->DrawMenu();

	return false;
}

bool MainMenu::PurchaseEquipment(const string &text) const
{
	if (this->CheckPlayer())
	{
		this->m_ShopMenu->RunMenu();
		this->DrawTitle();
		this->DrawMenu();
	}

	return false;
}

bool MainMenu::Fight(const string &text) const
{
	if (this->CheckPlayer())
	{
		this->m_FightMenu->RunMenu();
		this->DrawTitle();
		this->DrawMenu();
	}

	return false;
}

bool MainMenu::Quit(const string &text) const
{
	return true;
}