#define YSI_NO_HEAP_MALLOC
#define YSI_NO_OPTIMISATION_MESSAGE
#define YSI_NO_CACHE_MESSAGE
#define YSI_NO_MODE_CACHE
#define YSI_NO_VERSION_CHECK


/*
	Inspired by https://github.com/PatrickGTR/gta-open without mysql-prepare & inline
*/

#include <a_samp>

#include <constants>

// Libraries
#include <a_mysql>
#include <samp_bcrypt>
#include <zcmd>
#include <Pawn.RakNet>
#include <cec>

// YSI
#include <YSI_Extra\y_inline_mysql>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_iterate>
#include <YSI_Visual\y_dialog>

// Gamemodes Scripts
#include <init>

#include <utils>
#include <anti-cheat>
#include <account>
#include <player>

main () {}

public OnGameModeInit()
{
	SetGameModeText("Classic");
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

CMD:te1(playerid, params) {
	GivePlayerMoney(playerid, 500);
	return 1;
}

CMD:te2(playerid, params) {
	GivePlayerMoney(playerid, -250);
	return 1;
}

CMD:te3(playerid, params) {
	SetPlayerHealth(playerid, 50);
	return 1;
}

CMD:te4(playerid, params) {
	SetPlayerHealth(playerid, 100);
	return 1;
}

CMD:te5(playerid, params) {
	SetPlayerArmour(playerid, 50);
	return 1;
}

CMD:te6(playerid, params) {
	SetPlayerArmour(playerid, 100);
	return 1;
}