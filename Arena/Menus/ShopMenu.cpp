#include "ShopMenu.h"


using namespace std;


ShopMenu::ShopMenu(Player &player, ConLib &console) : Menu("%#15;S%#10;h%#2;op", player, console)
{
	this->InitMenuItems();
	this->InitSubMenus();
}

ShopMenu::~ShopMenu()
{
	SAFE_DELETE(this->m_WeaponMenu);
	SAFE_DELETE(this->m_ArmorMenu);
}

void ShopMenu::InitMenuItems()
{
	this->AddItem("a", "%#3;[%#10;A%#3;]%#15;rmor", bind(&ShopMenu::BuyArmor, this, placeholders::_1));
	this->AddItem("w", "%#3;[%#10;W%#3;]%#15;eapons", bind(&ShopMenu::BuyWeapon, this, placeholders::_1));
	this->AddItem("h", "%#3;[%#10;H%#3;]%#15;eal (10hp/5g)", bind(&ShopMenu::Heal, this, placeholders::_1));
	this->AddItem("b", "%#3;[%#10;B%#3;]%#15;ack to Previous Menu", bind(&ShopMenu::Quit, this, placeholders::_1));
}

void ShopMenu::InitSubMenus()
{
	this->m_WeaponMenu = new WeaponMenu(this->m_Player, this->m_Console);
	this->m_ArmorMenu = new ArmorMenu(this->m_Player, this->m_Console);
}

void ShopMenu::RunMenu()
{
	this->DrawTitle();
	this->DrawMenu();

	this->HandleInput(1, true);
}

bool ShopMenu::BuyArmor(const string &text) const
{
	this->m_ArmorMenu->RunMenu();

	this->DrawTitle();
	this->DrawMenu();

	return false;
}

bool ShopMenu::BuyWeapon(const string &text) const
{
	this->m_WeaponMenu->RunMenu();

	this->DrawTitle();
	this->DrawMenu();

	return false;
}

bool ShopMenu::Heal(const string &text) const
{
	if (this->m_Player.Gold() < 5)
	{
		this->DrawError("Not enough gold!");
		return false;
	}

	if (this->m_Player.HP() >= this->m_Player.MaxHP())
	{
		this->DrawMessage("You are completely healed!");
		return false;
	}

	this->m_Player.Gold() -= 5;
	this->m_Player.Heal(10);
	this->m_Player.Save();

	this->DrawMessage("10hps have been healed.");

	return false;
}

bool ShopMenu::Quit(const string &text) const
{
	return true;
}

