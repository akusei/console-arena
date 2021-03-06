#include "Global.h"
#include "resource.h"


const char *GAMETITLE = "%#15;C%#10;o%#2;nsole %#15;A%#10;r%#2;ena";
const char *WINDOWTITLE = "Console Arena";
const char *HEROESFILE = "heroes.dat";
const char *PLAYERFILE = "player.dat";

const char *TOKENATTACKER = "%attacker";
const char *TOKENWEAPON = "%weapon";
const char *TOKENTARGET = "%target";
const char *TOKENDAMAGE = "%damage";

const char *g_MissStrings[] =
{
	"%#11;%attacker %#14;attempts to strike %target, but the %weapon was too heavy... %attacker falls over backwards!",
	"%#11;%attacker %#14;lifts his %weapon into the air... and drops it on his toe!",
	"%#11;%attacker %#14;swings his %weapon, but only manages to split a few hairs on %target's head."
};

const char *g_HitStrings[] =
{
	"%#11;%attacker %#10;swings his %weapon at his opponent and strikes %target for %#11;%damage %#10;damage.",
	"%#10;%target is grazed by %#11;%attacker's %#10; %weapon causing %#11;%damage %#10;damage.",
	"%#11;%attacker %#10;lunges at %target, but it was merely a %#11;%damage %#10;damage flesh wound."
};

const char *g_CriticalStrings[] =
{
	"%#11;%attacker %#9;swings his %weapon at his opponent and critically wounds %target for %#11;%damage %#9;damage!",
	"%#11;%attacker %#9;has severed a limb from %target's body causing a massive %#11;%damage %#9;points of damage!",
	"%#9;Blood pours from %target as %#11;%attacker %#9; slices through %#11;%damage %#9;layers of flesh!",
	"%#11;%attacker %#9;skewers %target's organs with his %weapon dealing a critical %#11;%damage %#9;points of damage!"
};

const char *g_RunSuccessful[] =
{
	"%#10;You make a running start and slide underneath %target's legs for a graceful escape!",
	"%#10;%target's attention turns to an attractive young lady, and you get away.",
	"%#10;You yell and point in a direction \"Hey, what's that!\", then run the other way.",
	"%#10;%target is blinded by the dirt you so shamefully threw in his eyes!"
};

const char *g_RunUnsuccessful[] = 
{
	"%#9;You Slipped on a hotdog in an attempt to run away!",
	"%#9;You attempt to escape but %target is blocking the way!",
	"%#9;You turn to make an escape... only to be hit in the face by a brick wall!"
};

const char *g_FinalBlow[] =
{
	"%#10;%attacker raises his %weapon and crushes %#11;%target's %#10;skull like a grape!",
	"%#10;By pure luck, %attacker manages to overpower %#11;%target %#10;and issue a final and deadly blow!",
	"%#11;%target's %#10;life was cut short by %attacker's %weapon!",
	"%#10;Every bone in %#11;%target's %#10;body has been crushed!"
};

const char *g_MonsterNames[] =
{
	"An Orc",
	"A Goblin",
	"A Dark Elf",
	"A Snake",
	"A Cyclops",
	"The Fat Stick",
	"A Swamp Monster",
	"A Vampire",
	"A Troll",
	"An Imp",
	"Flava Flav",
	"A Fishman",
	"A Red Slime",
	"A Wyvern",
	"Dr. Mad",
	"Lassic",
	"A Basalisk",
	"Kefka"
};

int g_RequiredExperience[MAX_LEVEL];

const int g_AttackSounds[] = 
{
	IDR_ATTACK1
};

const char *g_SplashScreen[SPLASHCOUNT][SCREENHEIGHT] =
{
	{ "%#10;                               :                                           \r\n",
	"                               ;;                                          \r\n",
	"                              / |                                          \r\n",
	"                             /  |                                          \r\n",
	"                           .'   :                                          \r\n",
	"                        .-'     '                                          \r\n",
	"                    _.-'       /                                           \r\n",
	"                .-*\"          /                                %#15;_%#10;          \r\n",
	"             .-'            .'                            %#15;_.-*?'%#10;           \r\n",
	"           .'             .'                           %#15;.-\"  .'    __%#10;      \r\n",
	"         .'      ,     .-'                           .-+.%#15;  .' _.-*\".'%#10;     \r\n",
	"        /        \\  .-'         _.--**\"\"**-.     .-'  _.y-:%#15;-\"   .'%#10;     \r\n",
	"       :          `+.       .*\"\"*.          `.  :-. -.     \\  %#15;.'%#10;        \r\n",
	"       ;        .--*\"\"*--. / __   `  _.--.    \\ |%#9;@%#10;| -.`   -.;%#15;/%#10; _.-+.    \r\n",
	"       :      .'          :*\"  \"*..*\"          y`-' %#9;@%#10;|      ;*\"  _(    \r\n",
	"        \\    /      %#11;+----%#10;/ / .'.%#11;-%#10;'%#11;---+%#10;  .-._.+' `.  -'_.--. :- \"_(       \r\n",
	"         `*-:       %#11;|    %#15;\\/\\/\\/%#11;      | %#10;/%#8;)%#10;     `     .'___   ' \"_(      \r\n",
	"            ;    `._%#11;|                %#11;|%#10; \\  %#8;)%#10;`      .'.'   `./_\" (         \r\n",
	"            :      \\%#11;|    %#9;CONSOLE%#10;     %#11;|%#10; (`._..--**\" : .-    ; `\"'        \r\n",
	"             \\      %#11;|                %#11;|%#10;  `----**%#15;\"T%#10;\"\" \" `+.  |          \r\n",
	"              `.    %#11;|     %#9;ARENA%#10;      %#11;|%#10;         %#15;'%#10;     .'    :               \r\n",
	"            _.-*\"*- %#11;|                %#11;|%#10;            / /      '              \r\n",
	"        .-*\" _      %#11;|                %#11;|%#10;      __..-'\\       /              \r\n",
	"         \"+,'___..--%#11;|                %#11;|%#10;--**\"\"       `-.__.'              \r\n",
	"           \"\"       %#11;+----------------+                                       " },
	{ "%#15;                   .7                                                      \r\n",
	"                 .'/                                                       \r\n",
	"                / /                                                        \r\n",
	"               / /                                                         \r\n",
	"              / /                                      %#9;C O N S O L E%#15;       \r\n",
	"             / /                                                           \r\n",
	"            / /                                                            \r\n",
	"           / /                                           %#9;A R E N A%#15;         \r\n",
	"          / /                                                              \r\n",
	"         / /                                                               \r\n",
	"       __|/                                                                \r\n",
	"     ,-\\__\\                                                              \r\n",
	"     |f-\"Y\\|                                                             \r\n",
	"     \\()7L/                                                               \r\n",
	"      cgD                            __ _                                  \r\n",
	"      |\\(                          .'  Y '>,                              \r\n",
	"       \\ \\                        / _   _   \\                           \r\n",
	"        \\\\\\                       )(%#9;@%#15;) (%#9;@%#15;)(|}                           \r\n",
	"         \\\\\\                      {  %#8;4A%#15;   } /                           \r\n",
	"          \\\\\\                      \\%#8;uLuJJ%#15;/\\l                          \r\n",
	"           \\\\\\                     |%#8;3    p%#15;)/                            \r\n",
	"            \\\\\\___ __________      /%#8;nnm_n%#15;//                             \r\n",
	"            c7___-__,__-)\\,__)(\".  \\_>-<_/D                             \r\n",
	"                       //V     \\_\"-._.__G<D     __                       \r\n",
	"                       (       \\ \"-._\"> G<D-_.-\"_=)_                       " }
};