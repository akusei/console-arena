#include "HeroesMenu.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <sstream>


using namespace std;


HeroesMenu::HeroesMenu(Player &player, ConLib &console) : Menu("%#15;H%#10;a%#2;ll of %#15;H%#10;e%#2;roes", player, console)
{
}

HeroesMenu::~HeroesMenu()
{
}

void HeroesMenu::FormatHeroes(const vector<HeroInfo> &heroes)
{
	ostringstream ostr;

	ostr << "LVL " << std::left << std::setw(MAXNAME) << "Hero" << " Slain By";
	this->AddItem(ostr.str());
	this->AddItem();

	int startItem = (this->m_CurrentPage - 1) * HeroesMenu::PAGE_SIZE;
	int endItem = startItem + HeroesMenu::PAGE_SIZE;
	for (int i = startItem; i < endItem; i++)
	{
		if (i >= heroes.size())
			break;

		ostr.str(string());
		HeroInfo hero = heroes.at(i);

		ostr << "%#11;" << std::right << std::setw(3) << hero.HeroLevel << " %#10;";
		ostr << std::left << std::setw(MAXNAME) << hero.Name << " %#15;";
		ostr << "Level " << "%#11;" << hero.EnemyLevel << " %#9;" << hero.Enemy << " %#15;in round ";
		ostr << "%#11;" << hero.Round;

		this->AddItem(ostr.str());
	}
}

void HeroesMenu::InitMenuItems()
{
	this->ClearItems();

	vector<HeroInfo> heroes = Heroes::Load(HEROESFILE);

	this->m_TotalPages = ceil((double)heroes.size() / HeroesMenu::PAGE_SIZE);
	if (this->m_CurrentPage > this->m_TotalPages)
		this->m_CurrentPage = this->m_TotalPages;

	if (heroes.size() <= 0)
		this->AddItem("No lives have been taken by the arena");
	else
		this->FormatHeroes(heroes);

	this->AddItem();

	if (this->m_CurrentPage < this->m_TotalPages)
		this->AddItem("n", "%#3;[%#10;N%#3;]%#15;ext page", bind(&HeroesMenu::Next, this, placeholders::_1));
	if (this->m_CurrentPage > 1)
		this->AddItem("p", "%#3;[%#10;P%#3;]%#15;revious page", bind(&HeroesMenu::Back, this, placeholders::_1));

	this->AddItem("b", "%#3;[%#10;B%#3;]%#15;ack to previous menu", bind(&HeroesMenu::Quit, this, placeholders::_1));
}

void HeroesMenu::InitSubMenus()
{
}

void HeroesMenu::RunMenu()
{
	this->m_CurrentPage = 1;
	this->InitMenuItems();

	this->DrawTitle();
	this->DrawMenu();

	this->HandleInput(1, true);
}

bool HeroesMenu::Next(const string &text)
{
	this->m_CurrentPage++;
	this->InitMenuItems();
	this->DrawMenu();

	return false;
}

bool HeroesMenu::Back(const string &text)
{
	this->m_CurrentPage--;
	if (this->m_CurrentPage < 1)
		this->m_CurrentPage = 1;

	this->InitMenuItems();
	this->DrawMenu();

	return false;
}

bool HeroesMenu::Quit(const string &text) const
{
	return true;
}