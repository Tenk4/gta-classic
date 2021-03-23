#include <YSI_Coding\y_hooks>

stock Account_PromptRegister(playerid) {
    inline const _response(pid, dialogid, response, listitem, string:inputtext[])
    {
        #pragma unused pid, dialogid, listitem
        if (response) {
            if (!(4 <= strlen(inputtext) <= 20)) {
                SendClientMessage(playerid, COLOR_RED, "รหัสผ่านต้องไม่ต่ำกว่า 4 และไม่มากกว่า 20 ตัวอักษร");
                SendClientMessage(playerid, COLOR_RED, "ช่วยเหลือ: การตั้งรหัสผ่านควรมีทั้งตัวอักษรและตัวเลขเพื่อความปลอดภัยของท่าน");
                Account_PromptRegister(playerid);
                return;
            }
            bcrypt_hash(playerid, "OnPasswordHash", inputtext, BCRYPT_COST);
        }
        else {
            Kick(playerid);
        }
    }

    static const caption[] = "\
        ยินดีต้อนรับเข้าสู่ "SERVER_NAME"\
        กรุณาใส่รหัสผ่านเพื่อลงทะเบียน\
    ";

    Dialog_ShowCallback(playerid,
        using inline _response, 
        DIALOG_STYLE_PASSWORD, 
        SERVER_NAME, 
        caption, 
        "ลงทะเบียน",
        "ออกจากเกม"
    );
}

forward OnPasswordHash(playerid);
public OnPasswordHash(playerid) {
    new 
        query[240],
        hash[62]
    ;

	bcrypt_get_hash(hash);

    mysql_format(MySQL_GetHandle(), query, sizeof query, 
    "\
        INSERT INTO `players` \
        (`username`, `password`, `date_reg`, `time_reg`, `ip`) \
        VALUES \
        ('%e', '%s', '%e', '%e', '%e')\
    ", 
        Player_GetName(playerid),
        hash,
        Date_Get(), 
        Time_Get(),
        Player_GetIP(playerid)
    );
    mysql_tquery(MySQL_GetHandle(), query, "Account_Create", "d", playerid);
}

forward Account_Create(playerid);
public Account_Create(playerid)
{
	Player_SetAccountID(playerid, cache_insert_id());
    CallLocalFunction("OnPlayerRegister", "i", playerid);
	Account_PromptLogin(playerid);
	return 1;
}