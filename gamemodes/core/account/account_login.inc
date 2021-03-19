#include <YSI_Coding\y_hooks>

static 
    PasswordAttempts[MAX_PLAYERS],
    bool:Player_LoginStatus[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    PasswordAttempts[playerid]      = 0;
    Player_LoginStatus[playerid]    = false;
    return 1;
}

Account_PromptLogin(playerid) {
    new
        query[81],
        playerHash[62],
        playerDate[11],
        playerTime[9],
        playerIP[16];

	mysql_format(MySQL_GetHandle(), query, sizeof query, 
    "\
        SELECT * FROM `players` WHERE `username` = '%e' LIMIT 1\
    ", 
        Player_GetName(playerid)
    );
    mysql_query(MySQL_GetHandle(), query);

    cache_get_value_name(0, "password", playerHash, sizeof(playerHash));
    cache_get_value_name(0, "date_reg", playerDate, sizeof(playerDate));
    cache_get_value_name(0, "time_reg", playerTime, sizeof(playerTime));
    cache_get_value_name(0, "ip", playerIP, sizeof(playerIP));

    Player_SetAccountHash(playerid, playerHash);
    Player_SetAccountDate(playerid, playerDate);
    Player_SetAccountTime(playerid, playerTime);
    Player_SetAccountIP(playerid, playerIP);

    static 
        const caption[] = 
        "\
            ยินดีต้อนรับเข้าสู่ "SERVER_NAME"\
            กรุณาใส่รหัสผ่านเพื่อล็อคอิน\
        ";
    Dialog_ShowCallback(playerid,
        using public Account_Login<iiiis>, 
        DIALOG_STYLE_PASSWORD, 
        SERVER_NAME, 
        caption, 
        "ล็อคอิน",
        "ออกจากเกม");
    return 1;
}

forward Account_Login(playerid, dialogid, response, listitem, string:inputtext[]);
public Account_Login(playerid, dialogid, response, listitem, string:inputtext[]) {
    if (response) {
        bcrypt_verify(playerid, "OnPasswordVerify", inputtext, Player_GetAccountHash(playerid));
    }
    else {
        Kick(playerid);
    }
    return 1;
}

forward OnPasswordVerify(playerid, bool:success);
public OnPasswordVerify(playerid, bool:success) {
    if (success)
    {
        PasswordAttempts[playerid] = 0;
        CallLocalFunction("OnPlayerLogin", "d", playerid);
    }
    else
    {
        PasswordAttempts[playerid]++;
        if (PasswordAttempts[playerid] >= 3)
        {
            SendClientMessage(playerid, COLOR_RED, "รหัสผ่านไม่ถูกต้องครบ 3/3 ระบบจึงเตะคุณออกจากเซิร์ฟเวอร์");
            SendClientMessage(playerid, COLOR_RED, "ช่วยเหลือ: /q ในการออกจากหน้าต่างเกม");
            Kick_Message(playerid);
        }
        else
        {
            va_SendClientMessage(playerid, COLOR_RED, "รหัสผ่านไม่ถูกต้อง %d/3", PasswordAttempts[playerid]);
            SendClientMessage(playerid, COLOR_RED, "หากคุณใส่รหัสผ่านไม่ถูกต้องครบ 3 ครั้ง ระบบจะทำการเตะคุณออกจากเซิร์ฟเวอร์");
            Account_PromptLogin(playerid);
        }
    }
}

hook OnPlayerLogin(playerid) {
    ClearPlayerChat(playerid, 20);
    SendClientMessage(playerid, COLOR_YELLOW, "ยินดีต้อนรับเข้าสู่ "SERVER_NAME" เวอร์ชั่น: "SERVER_VERSION"");

    Player_SetLoginStatus(playerid, true);
    return 1;
}

Player_IsLoggedIn(playerid) {
    return Player_LoginStatus[playerid];
}

Player_SetLoginStatus(playerid, bool:status) {
    return Player_LoginStatus[playerid] = status;
}