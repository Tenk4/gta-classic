#include <YSI_Coding\y_hooks>

static
    Player_VIPLevel[MAX_PLAYERS]
;

hook OnPlayerLogin(playerid)
{
    inline _LoadVIP()
    {
        new 
            expire, 
            expiry_date[35],
            rows
        ;

        cache_get_row_count(rows);

        if(rows) {
            cache_get_value_name_int(0, "vip_level", Player_VIPLevel[playerid]);
            cache_get_value_name(0, "expiry", expiry_date, sizeof(expiry_date));
            cache_get_value_name_int(0, "expire", expire);

            if (expire <= 0) {
                VIP_RemovePlayer(playerid);
                va_SendClientMessage(playerid, COLOR_RED, "VIP ของคุณหมดอายุแล้ว %s!", expiry_date);
                Player_VIPLevel[playerid] = 0;
                return;
            }
            va_SendClientMessage(playerid, COLOR_RED, "คุณคือ VIP ระดับ %d * จะหมดอายุในอีก {FFFFFF}%s", VIP_GetPlayerLevel(playerid), expiry_date);
        }
    }
    static const query[] = "\
        SELECT \
            vip_level, \
            DATE_FORMAT(vip_expire_date, '"SQL_DATETIME_FORMAT"') as expiry, \
            TIMESTAMPDIFF(SECOND, CURRENT_TIMESTAMP(), vip_expire_date) as expire \
        FROM \
            vips \
        WHERE \
            u_id = %d\
    ";

    MySQL_TQueryInline(MySQL_GetHandle(), using inline _LoadVIP, query, Player_GetAccountID(playerid));
}

stock VIP_GivePlayer(playerid, level, interval_type, duration) {
    new 
        interval[6],
        string[260]
    ;

    interval = interval_type == 0 ? ("MONTH") : ("YEAR");

    static const query[] = "\
        INSERT INTO \
            vips (u_id, vip_level, vip_expire_date) \
        VALUES \
            (%d, %d, DATE_ADD(CURRENT_TIMESTAMP(), INTERVAL %d %s))"
    ;

    mysql_format(MySQL_GetHandle(), string, sizeof string, 
        query,
        Player_GetAccountID(playerid),
        level,
        duration,
        interval
    );
    mysql_tquery(MySQL_GetHandle(), string);
    Player_VIPLevel[playerid] = level;
}

stock VIP_RemovePlayer(playerid) {
    new
        string[70]
    ;

    static const query[] = "\
        DELETE FROM \
            vips \
        WHERE \
            u_id = %d\
    ";

    mysql_format(MySQL_GetHandle(), string, sizeof string, 
        query,
        Player_GetAccountID(playerid)
    );
    mysql_tquery(MySQL_GetHandle(), string);
}

stock VIP_GetPlayerLevel(playerid) {
    return Player_VIPLevel[playerid];
}