#include <YSI_Coding\y_hooks>

stock Account_CreateShow(playerid) {
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
        new 
            buffer[129],
            query[270];

        WP_Hash(buffer, sizeof(buffer), inputtext);
        mysql_format(MySQL_GetHandle(), query, sizeof query, 
        "\
            INSERT INTO `accounts` (`username`, `password`, `date_reg`, `time_reg`, `ip`) \
            VALUES \
            ('%e', '%s', '%e', '%e', '%e')\
        ", 
            Player_Name(playerid), 
            buffer, 
            Date_Get(), 
            Time_Get(),
            Player_Ip(playerid)
        );
        mysql_tquery(MySQL_GetHandle(), query, "Account_Create", "d", playerid);

        printf(query);
    }
    else {
        Kick(playerid);
    }
    return 1;
}

forward Account_Create(playerid);
public Account_Create(playerid)
{
	accData[playerid][ID] = cache_insert_id();
	Account_LoginShow(playerid);
	return 1;
}