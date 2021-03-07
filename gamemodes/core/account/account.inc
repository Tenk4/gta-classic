forward OnPlayerLogin(playerid);

#include <account_ban>
#include <account_create>
#include <account_login>

#include <YSI_Coding\y_hooks>

static
    Player_UID[MAX_PLAYERS],
    Player_DateReg[MAX_PLAYERS][11],
    Player_TimeReg[MAX_PLAYERS][9],
    Player_IPReg[MAX_PLAYERS][16];

hook OnPlayerConnect(playerid) {
    Player_UID[playerid]            = 0;
    Player_DateReg[playerid][0]     = EOS;
    Player_TimeReg[playerid][0]     = EOS;
    Player_IPReg[playerid][0]       = EOS;
    return 1;
}

stock Player_SetAccountID(playerid, value) {
    return Player_UID[playerid] = value;
}

stock Player_GetAccountID(playerid) {
    return Player_UID[playerid];
}

stock Player_GetDateReg(playerid) {
    return Player_DateReg[playerid];
}

stock Player_SetDateReg(playerid, const date[]) {
    return format(Player_DateReg[playerid], 11, date);
}

stock Player_GetTimeReg(playerid) {
    return Player_TimeReg[playerid];
}

stock Player_SetTimeReg(playerid, const time[]) {
    return format(Player_TimeReg[playerid], 9, time);
}

stock Player_GetIPReg(playerid) {
    return Player_IPReg[playerid];
}

stock Player_SetIPReg(playerid, const ip[]) {
    return format(Player_IPReg[playerid], 16, ip);
}