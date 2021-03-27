Player_GetName(playerid) {
    new 
        name[MAX_PLAYER_NAME]
    ;
    GetPlayerName(playerid, name, sizeof name);
    return name;
}

Player_GetIP(playerid) {
    new 
        IP[16]
    ;
    GetPlayerIp(playerid, IP, sizeof IP);
    return IP;
}

Player_Kick(playerid, time = 500) {
    SetTimerEx("Player_Kicked", time, false, "d", playerid);
    return 1;
}

forward Player_Kicked(playerid);
public Player_Kicked(playerid) {
    Kick(playerid);
    return 1;
}

ClearPlayerChat(playerid, lines) {
    for(new i = 0; i <= lines; i++)
    {
        SendClientMessage(playerid, COLOR_WHITE, "");
    }
    return 1;
}