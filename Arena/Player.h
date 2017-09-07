#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"


class Player
{
public:
	enum AttackType
	{
		Miss,
		Hit,
		Critical
	};

	Player(const string &name, int level);
	Player();
	virtual ~Player();

	void		Roll();
	AttackType	Attack(Player &target) const;
	void		TakeDamage(int damage);
	void		Heal(int health);
	void		Load();
	void		Save() const;
	void		PurchaseItem(const WeaponInfo &weapon);
	void		PurchaseItem(const ArmorInfo &armor);
	void		PurchaseItem(float cost);
	bool		LevelUp(int experience, float gold, int level);
	
	int					GetInitiative() const;
	int					GetArmorCheck() const;
	const WeaponInfo	&Weapon() const;
	const ArmorInfo		&Armor() const;

	const bool		IsAlive() const;
	bool			&IsAlive();
	const int		Level() const;
	const string	&Name() const;
	string			&Name();
	const float		Gold() const;
	float			&Gold();
	const int		HighestLevel() const;
	const int		MaxHP() const;
	const int		HP() const;
	const int		Exp() const;
	const int		Constitution() const;
	const int		Dexterity() const;
	const int		Strength() const;
	const int		DamageTaken() const;


private:
	int			m_Level,
				m_Strength,
				m_Dexterity,
				m_Constitution,
				m_HP,
				m_Exp,
				m_MaxHP,
				m_HighestLevel,
				m_LastDamage;
	bool		m_IsAlive;
	float		m_Gold;
	string		m_Name;
	WeaponInfo	m_Weapon;
	ArmorInfo	m_Armor;
	bool		m_IsNPC;

	int Modifier(int attribute) const;
	int GetAttackRoll() const;
};

#endif