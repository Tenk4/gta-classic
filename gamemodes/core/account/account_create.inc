#include <YSI_Coding\y_hooks>

stock Account_PromptRegister(playerid) {
    static 
        const caption[] = 
        "\
            ยินดีต้อนรับเข้าสู่ "SERVER_NAME"\
            กรุณาใส่รหัสผ่านเพื่อลงทะเบียน\
        ";
    Dialog_ShowCallback(playerid,
        using public Account_InsertToDatabase<iiiis>, 
        DIALOG_STYLE_PASSWORD, 
        SERVER_NAME, 
        caption, 
        "ลงทะเบียน",
        "ออกจากเกม");
}

forward Account_InsertToDatabase(playerid, dialogid, response, listitem, string:inputtext[]);
public Account_InsertToDatabase(playerid, dialogid, response, listitem, string:inputtext[]) {
    if (response) {
        bcrypt_hash(playerid, "OnPasswordHash", inputtext, BCRYPT_COST);
    }
    else {
        Kick(playerid);
    }
    return 1;
}

forward OnPasswordHash(playerid);
public OnPasswordHash(playerid) {
    new 
        query[240],
        hash[62];

	bcrypt_get_hash(hash);

    mysql_format(MySQL_GetHandle(), query, sizeof query, 
    "\
        INSERT INTO `players` (`username`, `password`, `date_reg`, `time_reg`, `ip`) \
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