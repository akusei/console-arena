#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H

#define WIN32_LEAN_AND_MEAN

#include <SDKDDKVer.h>
#include "ConLib.h"
#include <windows.h>


#define SAFE_DELETE(x) delete x; x = NULL;


extern const char *GAMETITLE;
extern const char *WINDOWTITLE;
extern const char *HEROESFILE;
extern const char *PLAYERFILE;

const WORD BRIGHTWHITE = ConBlue | ConGreen | ConRed | ConIntensity;
const WORD BRIGHTRED = ConRed | ConIntensity;
const WORD GREEN = ConGreen;
const WORD BRIGHTGREEN = ConGreen | ConIntensity;

const int STARTPROMPT = 8;
const int STARTINPUT = STARTPROMPT + 11;
const int INPUTWIDTH = 63;
const int STARTINPUTBAR = 2;
const int INPUTBARWIDTH = 76;

const int TEXTWIDTH = 50;
const int MAXNAME = 16;
const int MAX_LEVEL = 20;
const int MIN_SKILL = 8;
const int MAX_SKILL = 20;
const int MAX_LEVEL_SHIFT = 5;
const int SCREENWIDTH = 80;
const int SCREENHEIGHT = 25;
const int VIEWPORTWIDTH = 78;
const int VIEWPORTHEIGHT = 21;

const int ATTACKSOUNDCOUNT = 1;
const int FINALBLOWCOUNT = 4;
const int RUNGOODCOUNT = 4;
const int RUNBADCOUNT = 3;
const int HITCOUNT = 3;
const int MISSCOUNT = 3;
const int CRITICALCOUNT = 4;

const int MONSTERCOUNT = 18;
const int SPLASHCOUNT = 2;

extern const char *TOKENATTACKER;
extern const char *TOKENWEAPON;
extern const char *TOKENTARGET;
extern const char *TOKENDAMAGE;

const int g_Experience[] = { 300, 150, 75, 35, 15, 5 };
const float g_Gold[] = { 25, 12, 6, 3, 1, 0.5 };
extern const char *g_MonsterNames[];
extern const char *g_RunSuccessful[];
extern const char *g_RunUnsuccessful[];
extern int g_RequiredExperience[MAX_LEVEL];
extern const char *g_SplashScreen[SPLASHCOUNT][SCREENHEIGHT];
extern const int g_AttackSounds[];

extern const char *g_HitStrings[];
extern const char *g_MissStrings[];
extern const char *g_CriticalStrings[];
extern const char *g_FinalBlow[];

#endif