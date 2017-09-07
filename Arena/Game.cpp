#define _USE_32BIT_TIME_T

#include "Global.h"
#include "Game.h"
#include "Dice.h"

#include <time.h>


Game::Game()
{
	this->m_Console = new ConLib(SCREENWIDTH, SCREENHEIGHT);
	this->m_Player = NULL;
}

Game::~Game()
{
	SAFE_DELETE(this->m_MainMenu);
	SAFE_DELETE(this->m_Console);
	SAFE_DELETE(this->m_Player);
}

void Game::Initialize()
{
	this->m_Console->SetTitle(WINDOWTITLE);

	Inventory::Load();

	this->m_Player = new Player();
	this->m_Player->Load();

	g_RequiredExperience[0] = 0;
	for (int i = 1; i < MAX_LEVEL; i++)
	{
		int level = i;
		g_RequiredExperience[i] = (level * 1000) + g_RequiredExperience[i - 1];
	}

	this->m_MainMenu = new MainMenu(*this->m_Player, *this->m_Console);
}

void Game::Run() const
{
	//Show Splash Screen
	int splash = Dice::Random(0, SPLASHCOUNT - 1);
	for (int i = 0; i < SCREENHEIGHT; i++)
		*this->m_Console << g_SplashScreen[splash][i];

	Sleep(4000);
	
	this->m_MainMenu->DrawBorder();
	this->m_MainMenu->RunMenu();
}