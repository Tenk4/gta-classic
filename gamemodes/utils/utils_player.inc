stock Player_Name(playerid) {
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof name);
    return name;
}

stock Player_Ip(playerid) {
    new IP[16];
    GetPlayerIp(playerid, IP, sizeof IP);
    return IP;
}