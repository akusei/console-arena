#pragma once
#ifndef HEROES_H
#define HEROES_H

#include "Global.h"
#include "Player.h"

#include <string>
#include <vector>


typedef struct HEROINFO
{
	char	Name[MAXNAME];
	char	Enemy[MAXNAME];
	char	EnemyWeapon[MAXNAME];
	int		HeroLevel;
	int		EnemyLevel;
	int		Round;

	HEROINFO() { }
	HEROINFO(const Player &player, const Player &enemy, int round)
	{
		memset(this->Name, 0, MAXNAME);
		memset(this->Enemy, 0, MAXNAME);
		memset(this->EnemyWeapon, 0, MAXNAME);

		string name = enemy.Name();
		if (name.compare(0, 2, "A ") == 0)
			name.erase(0, 2);
		else if (name.compare(0, 3, "An ") == 0)
			name.erase(0, 3);
		else if (name.compare(0, 4, "The ") == 0)
			name.erase(0, 4);

		strcpy_s(this->Name, player.Name().c_str());
		strcpy_s(this->Enemy, name.c_str());
		strcpy_s(this->EnemyWeapon, enemy.Weapon().Name);

		this->HeroLevel = player.Level();
		this->EnemyLevel = enemy.Level();
		this->Round = round;
	}
} HeroInfo;


class Heroes
{
public:
	static std::vector<HeroInfo>	Load(const std::string &filename);
	static void						Save(const std::string &filename, const HeroInfo &hero);

private:
	Heroes();
	virtual ~Heroes();
};

#endif
