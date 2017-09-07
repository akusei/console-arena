#include "ArmorMenu.h"

#include <sstream>


using namespace std;


ArmorMenu::ArmorMenu(Player &player, ConLib &console) : Menu("%#15;P%#10;u%#2;rchase %#15;A%#10;r%#2;mor", player, console)
{
	this->InitMenuItems();
	this->InitSubMenus();
}

ArmorMenu::~ArmorMenu()
{
}

void ArmorMenu::InitMenuItems()
{
	vector<ArmorInfo> armor = Inventory::GetArmor();
	
	for (UINT i = 0; i < armor.size(); i++)
	{
		char index[100];
		ostringstream ostr;
		string temp;
		ArmorInfo ai = armor.at(i);

		_itoa_s(i + 1, index, 10);

		temp.append("%#3;[%#10;").append(index).append("%#3;]%#15; ");
		if (i < 9)
			temp.append(" ");

		temp.append(ai.Name);
		temp.append(this->AddTab(temp));
		if (strlen(ai.Name) <= 10)
			temp.append(this->AddTab(temp));

		temp.append("AC: ");

		if (ai.ArmorClass >= 0)
			temp.append("+");
		ostr << ai.ArmorClass;
		temp.append(ostr.str());
		ostr.str("");

		temp.append(this->AddTab(temp));
		temp.append("Max Dex: ");

		if (ai.DexModifier >= 100)
		{
			temp.append("INF");
			temp.append(this->AddTab(temp));
		}
		else
		{
			if (ai.DexModifier >= 0)
				temp.append("+");
			ostr << ai.DexModifier;
			temp.append(ostr.str());
			temp.append(this->AddTab(temp));
			ostr.str("");
		}

		ostr << ai.Cost << "g";
		temp.append(ostr.str());

		this->AddItem(index, temp, bind(&ArmorMenu::PurchaseArmor, this, placeholders::_1));
	}

	this->AddItem("b", "%#3;[%#10;B%#3;]%#15;ack to previous menu", bind(&ArmorMenu::Quit, this, placeholders::_1));
}

void ArmorMenu::InitSubMenus()
{
}

void ArmorMenu::RunMenu()
{
	this->DrawTitle();
	this->DrawMenu();

	this->HandleInput(2, true);
}

bool ArmorMenu::PurchaseArmor(const string &text) const
{
	bool ret = false;

	int index = atoi(text.c_str());
	ArmorInfo ai = Inventory::GetArmor().at(index - 1);

	if (this->m_Player.Gold() >= ai.Cost)
	{
		this->m_Player.PurchaseItem(ai);
		ret = true;
	}
	else
		this->DrawError("Not enough gold!");

	return ret;
}

bool ArmorMenu::Quit(const string &text) const
{
	return true;
}

