#include "WeaponMenu.h"

#include <sstream>


using namespace std;


WeaponMenu::WeaponMenu(Player &player, ConLib &console) : Menu("%#15;P%#10;u%#2;rchase %#15;W%#10;e%#2;apon", player, console)
{
	this->InitMenuItems();
}

WeaponMenu::~WeaponMenu()
{
}

void WeaponMenu::InitMenuItems()
{
	vector<WeaponInfo> weapons = Inventory::GetWeapons();
	
	for (UINT i = 0; i < weapons.size(); i++)
	{
		char index[100];
		ostringstream ostr;
		string temp;
		WeaponInfo wi = weapons.at(i);

		_itoa_s(i + 1, index, 10);

		temp.append("%#3;[%#10;").append(index).append("%#3;]%#15; ");
		if (i < 9)
			temp.append(" ");
		temp.append(wi.Name);
		temp.append(this->AddTab(temp));
		
		if (strlen(wi.Name) <= 10)
			temp.append(this->AddTab(temp));
		
		ostr << wi.Dice << "d" << wi.Faces;
		temp.append(ostr.str());
		temp.append(this->AddTab(temp));

		ostr.str("");
		ostr << "(";

		if (wi.CriticalMin == wi.CriticalMax)
			ostr << wi.CriticalMax;
		else
			ostr << wi.CriticalMin << "-" << wi.CriticalMax;
		
		ostr << "/x" << wi.AttackMultiplier << ")";
		temp.append(ostr.str());
		temp.append(this->AddTab(temp));

		if (ostr.str().size() <= 8)
			temp.append(this->AddTab(temp));

		ostr.str("");
		ostr << wi.Cost << "g";

		temp.append(ostr.str());

		this->AddItem(index, temp, bind(&WeaponMenu::PurchaseWeapon, this, placeholders::_1));
	}

	this->AddItem("b", "%#3;[%#10;B%#3;]%#15;ack to previous menu", bind(&WeaponMenu::Quit, this, placeholders::_1));
}

void WeaponMenu::InitSubMenus()
{
}

void WeaponMenu::RunMenu()
{
	this->DrawTitle();
	this->DrawMenu();

	this->HandleInput(2, true);
}

bool WeaponMenu::PurchaseWeapon(const string &text) const
{
	bool ret = false;
	int index = atoi(text.c_str());
	WeaponInfo wi = Inventory::GetWeapons().at(index - 1);

	if (this->m_Player.Gold() >= wi.Cost)
	{
		this->m_Player.PurchaseItem(wi);
		ret = true;
	}
	else
		this->DrawError("Not enough gold!");

	return ret;
}

bool WeaponMenu::Quit(const string &text) const
{
	return true;
}