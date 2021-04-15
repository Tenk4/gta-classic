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
        playerHash[62],
        playerDate[11],
        playerTime[9],
        playerIP[16],
        rows
    ;

    inline _PromptLogin() {
        cache_get_row_count(rows);

        if (!rows) {
            Player_Kick(playerid);
            return;
        }

        cache_get_value_name(0, "password", playerHash, sizeof(playerHash));
        cache_get_value_name(0, "date_reg", playerDate, sizeof(playerDate));
        cache_get_value_name(0, "time_reg", playerTime, sizeof(playerTime));
        cache_get_value_name(0, "ip", playerIP, sizeof(playerIP));

        Player_SetAccountDate(playerid, playerDate);
        Player_SetAccountTime(playerid, playerTime);
        Player_SetAccountIP(playerid, playerIP);

        inline const _response(pid, dialogid, response, listitem, string:inputtext[])
        {
            #pragma unused pid, dialogid, listitem
            if (response) {
                inline const OnPasswordVerify(bool: success) {
                    if(!success) {
                        PasswordAttempts[playerid] ++;
                        va_SendClientMessage(playerid, COLOR_RED, "รหัสผ่านไม่ถูกต้องครบ %d/3 ระบบจึงเตะคุณออกจากเซิร์ฟเวอร์", PasswordAttempts[playerid]);
                        if(PasswordAttempts[playerid] >= 3) {
                            SendClientMessage(playerid, COLOR_RED, "ช่วยเหลือ: /q ในการออกจากหน้าต่างเกม");
                            Player_Kick(playerid);
                            return;
                        }

                        Account_PromptLogin(playerid);
                        return;
                    }
                    PasswordAttempts[playerid] = 0;
                    CallLocalFunction("OnPlayerLogin", "i", playerid); // Used in other modules to load other data.
                }
                BCrypt_CheckInline(inputtext, playerHash, using inline OnPasswordVerify);
            //    bcrypt_verify(playerid, "OnPasswordVerify", inputtext, playerHash);
            }
            else {
                Kick(playerid);
            }
        }

        static const caption[] = "\
            ยินดีต้อนรับเข้าสู่ "SERVER_NAME"\
            กรุณาใส่รหัสผ่านเพื่อล็อคอิน\
        ";

        Dialog_ShowCallback(playerid, 
            using inline _response, 
            DIALOG_STYLE_PASSWORD, 
            SERVER_NAME, 
            caption, 
            "ล็อคอิน",
            "ออกจากเกม"
        ); 
    }

    static const query[] = "\
        SELECT \
            username, \
            password, \
            date_reg, \
            time_reg, \
            ip \
        FROM \
            players \
        WHERE \
            username = '%e'"
    ;
    
    MySQL_TQueryInline(MySQL_GetHandle(), using inline _PromptLogin, query, Player_GetName(playerid));
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