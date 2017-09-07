#include "BattleMenu.h"
#include "..\Dice.h"
#include "..\Heroes.h"

#include <conio.h>
#include <sstream>


using namespace std;


BattleMenu::BattleMenu(Player &player, ConLib &console) : Menu("%#15;F%#10;i%#2;ght!", player, console)
{
	this->m_Monster = NULL;
	this->m_Round = 1;
}

BattleMenu::~BattleMenu()
{
	SAFE_DELETE(this->m_Monster);
}

void BattleMenu::InitMenuItems()
{
	this->ClearItems();

	char round[100];
	char hp[100];
	string color;
	string str;

	int percent = (this->m_Player.HP() * 100) / this->m_Player.MaxHP();

	_itoa_s(this->m_Round, round, 10);
	_itoa_s(this->m_Player.HP(), hp, 10);
	if (percent <= 50)
		color = "%#9;";
	else
		color = "%#11;";

	str.append("Round ").append(round).append(": ");
	str.append(color).append(hp).append(" %#15;remaining.");

	this->AddItem(str);
	this->AddItem();
	this->AddItem("a", "%#3;[%#10;A%#3;]%#15;ttack", bind(&BattleMenu::Battle, this, placeholders::_1));
	this->AddItem("r", "%#3;[%#10;R%#3;]%#15;un like a sissy back to town!", bind(&BattleMenu::Run, this, placeholders::_1));
}

void BattleMenu::InitSubMenus()
{
}

void BattleMenu::RunMenu()
{
	this->RunMenu(1);
}

void BattleMenu::RunMenu(int level)
{
	this->m_Round = 0;
	this->m_BattleDone = false;

	string title;
	const char *monsterName = g_MonsterNames[Dice::Random(0, MONSTERCOUNT)];
	title.append("%#15;Y%#10;o%#2;u %#15;A%#10;r%#2;e %#15;F%#10;i%#2;ghting ").append("%#9;").append(monsterName);
	this->DrawTitle(title);

	SAFE_DELETE(this->m_Monster);
	this->m_Monster = new Player(monsterName, level);
	
	while (!this->m_BattleDone)
	{
		this->m_Round++;
		this->InitMenuItems();
		this->DrawMenu();

		this->HandleInput(1, true);
	}

	//Check if this player has died and save him to the hall of heroes
	if (!this->m_Player.IsAlive())
	{
		HeroInfo hero(this->m_Player, *this->m_Monster, this->m_Round);
		Heroes::Save(HEROESFILE, hero);
	}

	SAFE_DELETE(this->m_Monster);
}

bool BattleMenu::Battle(const string &text)
{
	Player *attack1 = NULL;
	Player *attack2 = NULL;

	if (this->m_Player.GetInitiative() >= this->m_Monster->GetInitiative())
	{
		attack1 = &this->m_Player;
		attack2 = this->m_Monster;
	}
	else
	{
		attack1 = this->m_Monster;
		attack2 = &this->m_Player;
	}

	this->DoAttack(*attack1, *attack2);
	if (!this->m_Player.IsAlive())
	{
		this->DoDeath();
		return true;
	}
	if (!this->m_Monster->IsAlive())
	{
		this->DoWin(this->m_Monster->Level());
		return true;
	}

	this->DoAttack(*attack2, *attack1);
	if (!this->m_Player.IsAlive())
	{
		this->DoDeath();
		return true;
	}
	if (!this->m_Monster->IsAlive())
	{
		this->DoWin(this->m_Monster->Level());
		return true;
	}

	return true;
}

void BattleMenu::DoAttack(const Player &attacker, Player &target) const
{
	string info;
	Player::AttackType type = type = attacker.Attack(target);
	
	switch (type)
	{
	case Player::Hit:
		info = g_HitStrings[Dice::Random(0, HITCOUNT - 1)];
		break;

	case Player::Miss:
		info = g_MissStrings[Dice::Random(0, MISSCOUNT - 1)];
		break;

	case Player::Critical:
		info = g_CriticalStrings[Dice::Random(0, CRITICALCOUNT - 1)];
		break;
	}

	char number[100];
	int damage = target.DamageTaken();
	_itoa_s(damage, number, 10);

	if (!target.IsAlive())
		info = g_FinalBlow[Dice::Random(0, FINALBLOWCOUNT - 1)];

	this->ReplaceTokens(info, attacker.Name(), attacker.Weapon().Name, target.Name(), number);
	this->DrawText(info);

	Sleep(3000);
}

bool BattleMenu::Run(const string &text)
{
	string info;
	if (this->m_Player.GetInitiative() >= this->m_Monster->GetInitiative())
	{
		this->m_Player.Save();
		this->m_BattleDone = true;
		info = g_RunSuccessful[Dice::Random(0, RUNGOODCOUNT - 1)];

		this->ReplaceTokens(info, this->m_Player.Name(), "", this->m_Monster->Name(), "");
		this->DrawText(info);
		
		this->DrawTitle("%#15;C%#10;O%#2;WARD!");
		this->DrawInput("Press any key to continue...", true);

		_getch();

		return true;
	}

	info = g_RunUnsuccessful[Dice::Random(0, RUNBADCOUNT - 1)];

	this->ReplaceTokens(info, this->m_Player.Name(), "", this->m_Monster->Name(), "");
	this->DrawText(info);

	Sleep(3000);

	this->DoAttack(*this->m_Monster, this->m_Player);
	if (!this->m_Player.IsAlive())
	{
		this->DoDeath();
		return true;
	}
	if (!this->m_Monster->IsAlive())
	{
		this->DoWin(this->m_Monster->Level());
		return true;
	}

	return true;
}

void BattleMenu::DoDeath()
{
	this->m_BattleDone = true;

	this->DrawText("You have died! This character is no more, and you will need to create a new character from the Main Menu.");
	this->DrawTitle("%#9;Don't fear the Reaper!");
	this->DrawInput("Press any key to continue...", true);

	_getch();
}

void BattleMenu::DoWin(int level)
{
	this->m_BattleDone = true;

	int levelShift = this->m_Player.Level() - level;

	if (levelShift < 0)
		levelShift = 0;
	else if (levelShift > MAX_LEVEL_SHIFT)
		levelShift = MAX_LEVEL_SHIFT;

	int exp = g_Experience[levelShift];
	float gold = g_Gold[levelShift];

	string info;
	ostringstream ostr;

	ostr << exp;
	string experience = ostr.str();
	ostr.str("");

	ostr << gold;
	string g = ostr.str();
	ostr.str("");

	info.append(this->m_Player.Name()).append(" earns ").append(experience);
	info.append("xp and ").append(g).append("g.");

	if (this->m_Player.LevelUp(exp, gold, level))
	{
		ostr << this->m_Player.MaxHP();
		string hp = ostr.str();
		info.append("\n\n");
		info.append("You have advanced to the next level... Your new max HP is now ");
		info.append(hp).append(".");
	}

	this->DrawText(info);
	this->DrawTitle("%#15;C%#10;O%#2;NGRATULATIONS!");
	this->DrawInput("Press any key to continue...", true);

	_getch();
}