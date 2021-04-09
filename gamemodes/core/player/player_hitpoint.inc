#include <YSI_Coding\y_hooks>

Player_HitpointLoad(playerid) {
    inline _LoadHitpoint() {
        new
            Float:armour,
            Float:health,
            rows
        ;

        cache_get_row_count(rows);

        if(rows) {
            cache_get_value_name_float(0, "armour", armour);
            cache_get_value_name_float(0, "health", health);

            if(health <= 0)
            {
                health = 100.0;
            }

            SetPlayerArmour(playerid, armour);
            SetPlayerHealth(playerid, health);
        }
    }

    static const query[] = "\
        SELECT \
            armour, \
            health \
        FROM \
            player_stats \
        WHERE \
            u_id = %d \
    ";

    MySQL_TQueryInline(MySQL_GetHandle(), using inline _LoadHitpoint, query, Player_GetAccountID(playerid));
}

Player_HitpointSave(playerid) {
    new
        Float:health,
        Float:armour;

    GetPlayerHealth(playerid, health);
    GetPlayerArmour(playerid, armour);

    new
        string[100]
    ;

    static const query[] = "\
        UPDATE \
            player_stats \
        SET \
            health = %.0f, \
            armour = %.0f \
        WHERE \
            u_id = %d \
    ";

    mysql_format(MySQL_GetHandle(), string, sizeof string, 
        query,
        health,
        Player_GetAccountID(playerid)
    );
    mysql_tquery(MySQL_GetHandle(), string);
}

hook OnPlayerFirstSpawn(playerid) {
    Player_HitpointLoad(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    Player_HitpointSave(playerid);
    return 1;
}

hook function SetPlayerHealth(playerid, Float:health) {
    va_SendClientMessage(playerid, -1, "hp change %.0f", health);
    
    new
        string[80]
    ;

    static const query[] = "\
        UPDATE \
            player_stats \
        SET \
            health = %.0f \
        WHERE \
            u_id = %d \
    ";

    mysql_format(MySQL_GetHandle(), string, sizeof string, 
        query,
        health,
        Player_GetAccountID(playerid)
    );
    mysql_tquery(MySQL_GetHandle(), string);

    return continue(playerid, health);
}

hook function SetPlayerArmour(playerid, Float:armour) {
    va_SendClientMessage(playerid, -1, "armour change %.0f", armour);
    
    new
        string[80]
    ;

    static const query[] = "\
        UPDATE \
            player_stats \
        SET \
            armour = %.0f \
        WHERE \
            u_id = %d \
    ";

    mysql_format(MySQL_GetHandle(), string, sizeof string, 
        query,
        armour,
        Player_GetAccountID(playerid)
    );
    mysql_tquery(MySQL_GetHandle(), string);

    return continue(playerid, armour);
}