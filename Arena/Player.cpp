#include "Global.h"
#include "Player.h"
#include "Dice.h"
#include "resource.h"

#include <fstream>
#include <mmsystem.h>
#include <string>


using namespace std;


//This should be used to create monsters only
Player::Player(const string &name, int level)
{
	UINT maxArmor = (UINT)level;
	if (maxArmor > Inventory::GetArmor().size())
		maxArmor = (UINT)Inventory::GetArmor().size();

	UINT maxWeapon = (UINT)level;
	if (maxWeapon > Inventory::GetArmor().size())
		maxWeapon = (UINT)Inventory::GetArmor().size();

	this->m_Armor = Inventory::GetArmor().at(Dice::Random(0, maxArmor - 1));
	this->m_Weapon = Inventory::GetWeapons().at(Dice::Random(0, maxWeapon - 1));

	this->m_Name = name;
	this->Roll();
	this->m_Level = level;
	this->m_IsAlive = true;
	this->m_IsNPC = true;

	for (int i = 0; i < level - 1; i++)
	{
		int roll = Dice::Roll(1, 10);
		this->m_MaxHP += roll + this->Modifier(this->m_Constitution);
	}

	this->m_HP = this->m_MaxHP;
	this->m_LastDamage = 0;
}

Player::Player()
{
	this->m_Armor = Inventory::GetArmor().at(0);
	this->m_Weapon = Inventory::GetWeapons().at(0);
	this->Roll();
	this->m_IsAlive = false;
	this->m_IsNPC = false;
	this->m_LastDamage = 0;
}

Player::~Player()
{
}

void Player::PurchaseItem(const WeaponInfo &weapon)
{
	this->m_Gold -= weapon.Cost;
	this->m_Weapon = weapon;
	this->Save();
}

void Player::PurchaseItem(const ArmorInfo &armor)
{
	this->m_Gold -= armor.Cost;
	this->m_Armor = armor;
	this->Save();
}

Player::AttackType Player::Attack(Player &target) const
{
	AttackType ret = Player::Hit;

	int attackRoll = this->GetAttackRoll();
	int armorCheck = target.GetArmorCheck();
	int naturalRoll = attackRoll - this->m_Level - this->Modifier(this->m_Strength);
	
	if (armorCheck > attackRoll)
	{
		PlaySound(MAKEINTRESOURCE(IDR_MISS1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
		return Player::Miss;
	}

	int damage = Dice::Roll(this->m_Weapon.Dice, this->m_Weapon.Faces);
	damage += this->Modifier(this->m_Strength);
	if (naturalRoll >= this->m_Weapon.CriticalMin && naturalRoll <= this->m_Weapon.CriticalMax)
	{
		ret = Player::Critical;
		damage *= this->m_Weapon.AttackMultiplier;
	}

	target.TakeDamage(damage);

	if (!this->m_IsNPC && !target.IsAlive())
	{
		PlaySound(MAKEINTRESOURCE(IDR_WIN), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
		return ret;
	}
	
	PlaySound(MAKEINTRESOURCE(IDR_ATTACK1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

	return ret;
}

void Player::TakeDamage(int damage)
{
	this->m_LastDamage = damage;
	this->m_HP -= damage;
	if (this->m_HP <= 0)
	{
		this->m_IsAlive = false;
		this->Roll();
		this->m_Armor = Inventory::GetArmor().at(0);
		this->m_Weapon = Inventory::GetWeapons().at(0);
		this->Save();
	}
}

void Player::Heal(int health)
{
	int newHealth = this->m_HP + health;
	if (newHealth > this->m_MaxHP)
	{
		this->m_HP = this->m_MaxHP;
		return;
	}

	this->m_HP = newHealth;
}

void Player::Load()
{
	ifstream *file = new ifstream("player.dat", ios::binary);

	if (!file->is_open())
	{
		SAFE_DELETE(file);
		return;
	}

	file->read((char *)&this->m_Constitution, sizeof(this->m_Constitution));
	file->read((char *)&this->m_Dexterity, sizeof(this->m_Dexterity));
	file->read((char *)&this->m_Exp, sizeof(this->m_Exp));
	file->read((char *)&this->m_Gold, sizeof(this->m_Gold));
	file->read((char *)&this->m_HighestLevel, sizeof(this->m_HighestLevel));
	file->read((char *)&this->m_HP, sizeof(this->m_HP));
	file->read((char *)&this->m_IsAlive, sizeof(this->m_IsAlive));
	file->read((char *)&this->m_Level, sizeof(this->m_Level));
	file->read((char *)&this->m_MaxHP, sizeof(this->m_MaxHP));
	file->read((char *)&this->m_Strength, sizeof(this->m_Strength));
	
	char name[MAXNAME];
	file->read((char *)&name, MAXNAME);
	this->m_Name = name;

	file->read((char *)&this->m_Weapon, sizeof(WeaponInfo));
	file->read((char *)&this->m_Armor, sizeof(ArmorInfo));
	
	file->close();
	SAFE_DELETE(file);

	if (!this->m_IsAlive)
		this->Roll();
}

void Player::Save() const
{
	if (this->m_IsNPC)
		return;

	ofstream *file = new ofstream("player.dat", ios::trunc | ios::binary);

	file->write((char *)&this->m_Constitution, sizeof(this->m_Constitution));
	file->write((char *)&this->m_Dexterity, sizeof(this->m_Dexterity));
	file->write((char *)&this->m_Exp, sizeof(this->m_Exp));
	file->write((char *)&this->m_Gold, sizeof(this->m_Gold));
	file->write((char *)&this->m_HighestLevel, sizeof(this->m_HighestLevel));
	file->write((char *)&this->m_HP, sizeof(this->m_HP));
	file->write((char *)&this->m_IsAlive, sizeof(this->m_IsAlive));
	file->write((char *)&this->m_Level, sizeof(this->m_Level));
	file->write((char *)&this->m_MaxHP, sizeof(this->m_MaxHP));
	file->write((char *)&this->m_Strength, sizeof(this->m_Strength));

	UINT oldSize = (UINT)this->m_Name.size();
	//this->m_Name.resize(MAXNAME);
	file->write(this->m_Name.c_str(), MAXNAME);
	//this->m_Name.resize(oldSize);

	file->write((char *)&this->m_Weapon, sizeof(WeaponInfo));
	file->write((char *)&this->m_Armor, sizeof(ArmorInfo));

	file->flush();
	file->close();

	delete file;
}

void Player::Roll()
{
	this->m_Constitution = Dice::Random(MIN_SKILL, MAX_SKILL);
	this->m_Dexterity = Dice::Random(MIN_SKILL, MAX_SKILL);
	this->m_Level = (this->m_IsNPC) ? this->m_Level : 1;
	this->m_Strength = Dice::Random(MIN_SKILL, MAX_SKILL);
	this->m_Exp = 0;
	this->m_MaxHP = 10 + this->Modifier(this->m_Constitution);
	this->m_HP = this->m_MaxHP;
	this->m_Gold = 0;
	this->m_HighestLevel = 0;
}

bool Player::LevelUp(int experience, float gold, int level)
{
	this->m_Exp += experience;
	this->m_Gold += gold;
	if (level > this->m_HighestLevel)
		this->m_HighestLevel = level;

	if (this->m_Level == MAX_LEVEL || this->m_Exp < g_RequiredExperience[this->m_Level])
	{
		this->Save();
		return false;
	}

	this->m_Level++;
	int roll = Dice::Roll(1, 10);
	this->m_MaxHP += roll + this->Modifier(this->m_Constitution);
	this->m_HP = this->m_MaxHP;

	this->Save();

	return true;
}

int Player::Modifier(int attribute) const
{
	int ret = (attribute - 10) / 2;
	if (ret < 0 || ret > 100)
		ret = 0;

	return ret;
}

int Player::GetAttackRoll() const
{
	int roll = Dice::Roll(1, 20);
	return roll + this->m_Level + this->Modifier(this->m_Strength);
}

int Player::GetInitiative() const
{
	int roll = Dice::Roll(1, 20);
	return roll + this->Modifier(this->m_Dexterity);
}

int Player::GetArmorCheck() const
{
	int dexMod = this->Modifier(this->m_Dexterity);
	if (dexMod > this->m_Armor.DexModifier)
		dexMod = this->m_Armor.DexModifier;

	return 10 + this->m_Armor.ArmorClass + dexMod;
}

const bool Player::IsAlive() const
{
	return this->m_IsAlive;
}

bool &Player::IsAlive()
{
	return this->m_IsAlive;
}

const WeaponInfo &Player::Weapon() const
{
	return this->m_Weapon;
}

const ArmorInfo &Player::Armor() const
{
	return this->m_Armor;
}

const int Player::Level() const
{
	return this->m_Level;

}

string &Player::Name()
{
	return this->m_Name;
}

const string &Player::Name() const
{
	return this->m_Name;
}

const float Player::Gold() const
{
	return this->m_Gold;
}

float &Player::Gold()
{
	return this->m_Gold;
}

const int Player::HighestLevel() const
{
	return this->m_HighestLevel;
}

const int Player::MaxHP() const
{
	return this->m_MaxHP;
}

const int Player::HP() const
{
	return this->m_HP;
}

const int Player::Exp() const
{
	return this->m_Exp;
}

const int Player::Constitution() const
{
	return this->m_Constitution;
}

const int Player::Dexterity() const
{
	return this->m_Dexterity;
}

const int Player::Strength() const
{
	return this->m_Strength;
}

const int Player::DamageTaken() const
{
	return this->m_LastDamage;
}