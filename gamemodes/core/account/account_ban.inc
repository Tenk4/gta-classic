#include <YSI_Coding\y_hooks>

forward OnPlayerPrepareToConnect(playerid);

hook OnPlayerConnect(playerid) {
    return 1;
}

hook OnPlayerRequestClass(playerid, classid) {
    if (!Player_IsLoggedIn(playerid)) {
        TogglePlayerSpectating(playerid, true);
        defer Ban_PrepareCheck(playerid);
    }
    else {
        Kick(playerid);
    }
    return 1;
}

timer Ban_PrepareCheck[500](playerid) {
	SetPlayerCameraPos(playerid, -1762.7764, 886.1344, 305.2547);
	SetPlayerCameraLookAt(playerid, -1762.0156, 885.4888, 304.5006);

	new 
        query[81];

	mysql_format(MySQL_GetHandle(), query, sizeof query, 
    "\
        SELECT * FROM `bans` WHERE `username` = '%e' LIMIT 1\
    ", 
        Player_GetName(playerid)
    );
	mysql_tquery(MySQL_GetHandle(), query, "OnPlayerBanned", "d", playerid);
}

forward OnPlayerBanned(playerid);
public OnPlayerBanned(playerid) {
    new
        rows,
        banIP[16],
        banName[MAX_PLAYER_NAME],
        banAdmin[MAX_PLAYER_NAME],
        banReason[MAX_BAN_REASON],
        banDate[11],
        banTime[9],
        string[400];

    cache_get_row_count(rows);

    if (rows) {
        cache_get_value_name(0, "username", banName, MAX_PLAYER_NAME);
        cache_get_value_name(0, "ip",  banIP, 16);
        cache_get_value_name(0, "admin", banAdmin, MAX_PLAYER_NAME);
        cache_get_value_name(0, "reason", banReason, MAX_BAN_REASON);
        cache_get_value_name(0, "date_ban", banDate, 11);
        cache_get_value_name(0, "time_ban", banTime, 9);

        format(string, sizeof(string), 
        "\
            "C_WHITE"ชื่อตัวละคร: "C_GREY"%s\n\
            "C_WHITE"ไอพีที่ถูกแบน: "C_GREY"%s\n\
            "C_WHITE"ไอพีปัจจุบัน: "C_GREY"%s\n\
            "C_WHITE"แบนโดยแอดมิน: "C_GREY"%s\n\
            "C_WHITE"สาเหตุการโดนแบน: "C_GREY"%s\n\
            "C_WHITE"วันที่โดนแบน: "C_GREY"%s\n\
            "C_WHITE"เวลาที่โดนแบน: "C_GREY"%s\
        ", 
            banName, 
            banIP, 
            Player_GetIP(playerid), 
            banAdmin, 
            banReason, 
            banDate, 
            banTime
        );
        Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, "ข้อมูลการโดนแบน", string, "ปิด", "");

        Player_Kick(playerid);
    }
    else {
        CallLocalFunction("OnPlayerPrepareToConnect", "d", playerid);
    }
    return 1;
}

public OnPlayerPrepareToConnect(playerid) {
    new 
        query[81];

	mysql_format(MySQL_GetHandle(), query, sizeof query, 
    "\
        SELECT * FROM `players` WHERE `username` = '%e' LIMIT 1\
    ", 
        Player_GetName(playerid)
    );
	mysql_tquery(MySQL_GetHandle(), query, "OnPlayerConnected", "d", playerid);
    return 1;
}

forward OnPlayerConnected(playerid);
public OnPlayerConnected(playerid) {
    new 
        rows,
        playerUID;

    cache_get_row_count(rows);
    
    if (rows) {
        cache_get_value_name_int(0, "u_id", playerUID);

        Player_SetAccountID(playerid, playerUID);

        Account_PromptLogin(playerid);
    } 
    else {
        Account_PromptRegister(playerid);
    }
    return 1;
}