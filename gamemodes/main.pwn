#define YSI_NO_HEAP_MALLOC
#define YSI_NO_OPTIMISATION_MESSAGE
#define YSI_NO_CACHE_MESSAGE
#define YSI_NO_MODE_CACHE
#define YSI_NO_VERSION_CHECK

/*
	Inspiration by https://github.com/PatrickGTR/gta-open
*/

#include <a_samp>

#include <constants>

// Libraries
#include <a_mysql>
#include <zcmd>
#include <Pawn.RakNet>
#include <cec>


native WP_Hash(buffer[], len, const str[]);

// YSI
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_iterate>
#include <YSI_Visual\y_dialog>

// Gamemodes Scripts
#include <init>

#include <utils>
#include <account>

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