#include "CharacterMenu.h"

using namespace std;

CharacterMenu::CharacterMenu(Player &player, ConLib &console) : Menu("%#15;C%#10;r%#2;eate %#15;C%#10;h%#2;aracter", player, console)
{
	this->InitMenuItems();
}

CharacterMenu::~CharacterMenu()
{
}

void CharacterMenu::InitMenuItems()
{
	this->ClearItems();
	this->AddItem("%#15;What would you like to name your character?");
}

void CharacterMenu::InitSubMenus()
{
}

void CharacterMenu::RunMenu()
{
	this->InitMenuItems();
	this->DrawTitle();
	this->DrawMenu();
	
	string str = this->HandleInput(MAXNAME, false);
	this->m_Player.Name() = str;

	this->DrawTitle("%#15;R%#10;o%#2;ll %#15;F%#10;o%#2;r %#15;S%#10;t%#2;ats");
	this->Roll("");
	this->HandleInput(1, true);
}

bool CharacterMenu::Roll(const string &text)
{
		this->ClearItems();
		this->m_Player.Roll();

		char number[100];
		string str;

		str.append("%#15;Name:         %#10;").append(this->m_Player.Name());
		this->AddItem(str);
		str.clear();

		_itoa_s(this->m_Player.Strength(), number, 10);
		str.append("%#15;Strength:     %#11;").append(number);
		this->AddItem(str);
		str.clear();

		_itoa_s(this->m_Player.Dexterity(), number, 10);
		str.append("%#15;Dexterity:    %#11;").append(number);
		this->AddItem(str);
		str.clear();

		_itoa_s(this->m_Player.Constitution(), number, 10);
		str.append("%#15;Constitution: %#11;").append(number);
		this->AddItem(str);
		str.clear();

		_itoa_s(this->m_Player.MaxHP(), number, 10);
		str.append("%#15;Hit Points:   %#11;").append(number);
		this->AddItem(str);
		str.clear();

		this->AddItem("");
		this->AddItem("r", "%#3;[%#10;R%#3;]%#15;oll again", bind(&CharacterMenu::Roll, this, placeholders::_1));
		this->AddItem("k", "%#3;[%#10;K%#3;]%#15;eep character", bind(&CharacterMenu::Quit, this, placeholders::_1));
		this->DrawMenu();

		return false;
}

bool CharacterMenu::Quit(const string &text) const
{
	this->m_Player.IsAlive() = true;
	this->m_Player.Save();

	return true;
}