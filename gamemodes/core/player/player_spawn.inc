#include <YSI_Coding\y_hooks>

forward OnPlayerFirstSpawn(playerid);

static
    bool:PlayerFirstSpawn[MAX_PLAYERS] = true
;

hook OnPlayerConnect(playerid) {
    PlayerFirstSpawn[playerid] = true;
    return 1;
}

hook OnPlayerLogin(playerid)
{
    defer ForceSpawnPlayer(playerid);
    return 1;
}

timer void:ForceSpawnPlayer[50](playerid) {
	SetSpawnInfo(playerid, 0, 264, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	TogglePlayerSpectating(playerid, false);
}

hook OnPlayerSpawn(playerid) {
    SetPlayerPos(playerid, 810.63520, -1340.0682, 13.5386);
    SetPlayerFacingAngle(playerid, 37.33070);
    SetCameraBehindPlayer(playerid);
    printf(
    "\
        UID: %d | DATE: %s | TIME: %s | IP: %s\
    ", 
        Player_GetAccountID(playerid), 
        Player_GetAccountDate(playerid), 
        Player_GetAccountTime(playerid), 
        Player_GetAccountIP(playerid)
    );
    return 1;
}