#pragma once
#ifndef GAME_H
#define GAME_H

#include "ConLib.h"
#include "Player.h"
#include "Menus\MainMenu.h"


class Game
{
public:
	Game();
	virtual ~Game();

	void Initialize();
	void Run() const;


private:
	ConLib		*m_Console;
	Player		*m_Player;
	MainMenu	*m_MainMenu;

	//bool DisplayNoPlayer();
	//bool DisplayPlayer();
};

#endif