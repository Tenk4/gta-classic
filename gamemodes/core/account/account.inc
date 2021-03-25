forward OnPlayerLogin(playerid);
forward OnPlayerRegister(playerid);

#include <account_stats>
#include <account_ban>
#include <account_create>
#include <account_login>
#include <account_vip>

#include <YSI_Coding\y_hooks>

static
    PlayerUID[MAX_PLAYERS],
    PlayerDate[MAX_PLAYERS][11],
    PlayerTime[MAX_PLAYERS][9],
    PlayerIP[MAX_PLAYERS][16];

hook OnPlayerConnect(playerid) {
    PlayerUID[playerid]         = 0;
    PlayerDate[playerid][0]     = EOS;
    PlayerTime[playerid][0]     = EOS;
    PlayerIP[playerid][0]       = EOS;
    return 1;
}

public OnPlayerMoneyChange(playerid, previous, current) {
    va_SendClientMessage(playerid, -1, "money change %d", current);
    
    new
        string[80]
    ;

    static const query[] = "\
        UPDATE \
            player_stats \
        SET \
            money = %d \
        WHERE \
            u_id = %d \
    ";

    mysql_format(MySQL_GetHandle(), string, sizeof string, 
        query,
        current,
        Player_GetAccountID(playerid)
    );
    mysql_tquery(MySQL_GetHandle(), string);
    return 1;
}

Player_SetAccountID(playerid, value) {
    return PlayerUID[playerid] = value;
}

Player_GetAccountID(playerid) {
    return PlayerUID[playerid];
}

Player_GetAccountDate(playerid) {
    return PlayerDate[playerid];
}

Player_SetAccountDate(playerid, const date[]) {
    return format(PlayerDate[playerid], 11, date);
}

Player_GetAccountTime(playerid) {
    return PlayerTime[playerid];
}

Player_SetAccountTime(playerid, const time[]) {
    return format(PlayerTime[playerid], 9, time);
}

Player_GetAccountIP(playerid) {
    return PlayerIP[playerid];
}

Player_SetAccountIP(playerid, const ip[]) {
    return format(PlayerIP[playerid], 16, ip);
}