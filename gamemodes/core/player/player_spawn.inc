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
    if(PlayerFirstSpawn[playerid]) {
        CallLocalFunction("OnPlayerFirstSpawn", "i", playerid);
        PlayerFirstSpawn[playerid] = false;
    }
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

Player_HitpointLoad(playerid) {
    inline _LoadHitpoint() {
        new
            Float:armour,
            Float:health,
            rows
        ;

        cache_get_row_count(rows);

        if(rows) {
            cache_get_value_name_float(0, "armour", armour);
            cache_get_value_name_float(0, "health", health);

            SetPlayerArmour(playerid, armour);
            SetPlayerHealth(playerid, health);
        }
    }

    static const query[] = "\
        SELECT \
            armour, \
            health \
        FROM \
            player_stats \
        WHERE \
            u_id = %d \
    ";

    MySQL_TQueryInline(MySQL_GetHandle(), using inline _LoadHitpoint, query, Player_GetAccountID(playerid));
}

public OnPlayerFirstSpawn(playerid) {
    Player_HitpointLoad(playerid);
    return 1;
}