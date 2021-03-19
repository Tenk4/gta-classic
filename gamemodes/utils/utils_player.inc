Player_GetName(playerid) {
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof name);
    return name;
}

Player_GetIP(playerid) {
    new IP[16];
    GetPlayerIp(playerid, IP, sizeof IP);
    return IP;
}