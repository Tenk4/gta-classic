forward OnPlayerLogin(playerid);
forward OnPlayerRegister(playerid);

#include <account_stats>
#include <account_ban>
#include <account_create>
#include <account_login>

#include <YSI_Coding\y_hooks>

static
    PlayerUID[MAX_PLAYERS],
    PlayerDate[MAX_PLAYERS][11],
    PlayerTime[MAX_PLAYERS][9],
    PlayerIP[MAX_PLAYERS][16],
    PlayerHash[MAX_PLAYERS][62];

hook OnPlayerConnect(playerid) {
    PlayerUID[playerid]         = 0;
    PlayerDate[playerid][0]     = EOS;
    PlayerTime[playerid][0]     = EOS;
    PlayerIP[playerid][0]       = EOS;
    PlayerHash[playerid][0]     = EOS;
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

Player_GetAccountHash(playerid) {
    return PlayerHash[playerid];
}

Player_SetAccountHash(playerid, const hash[]) {
    return format(PlayerHash[playerid], 62, hash);
}