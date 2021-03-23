#include <YSI_Coding\y_hooks>

static
    PlayerAdmin[MAX_PLAYERS],
    PlayerKills[MAX_PLAYERS],
    PlayerDeaths[MAX_PLAYERS],
    PlayerWantedLevel[MAX_PLAYERS],
    PlayerSkin[MAX_PLAYERS];

Account_LoadStats(playerid) {
    inline _LoadStats() {
        new
            adminlevel,
            kills,
            deaths,
            wantedlevel,
            money,
            skin,
            rows
        ;

        cache_get_row_count(rows);

        if(rows) {
            cache_get_value_name_int(0, "admin_level", adminlevel);
            cache_get_value_name_int(0, "kills", kills);
            cache_get_value_name_int(0, "deaths", deaths);
            cache_get_value_name_int(0, "wanted_level", wantedlevel);
            cache_get_value_name_int(0, "money", money);
            cache_get_value_name_int(0, "skin", skin);

            Player_GiveAdmin(playerid, adminlevel);

            Player_GiveKill(playerid, kills);
            Player_GiveDeath(playerid, deaths);

            defer DelayGiveMoney(playerid, money);
        }
    }

    static const query[] = "\
        SELECT \
            admin_level, \
            kills, \
            deaths, \
            wanted_level, \
            money, \
            skin \
        FROM \
            player_stats \
        WHERE \
            u_id = %d \
    ";

    MySQL_TQueryInline(MySQL_GetHandle(), using inline _LoadStats, query, Player_GetAccountID(playerid));
}

timer DelayGiveMoney[100](playerid, money){
    GivePlayerMoney(playerid, money);
}

hook OnPlayerLogin(playerid) {
    Account_LoadStats(playerid);
    return 1;
}

hook OnPlayerRegister(playerid) {
    new
        string[64]
    ;

    static const query[] = "\
        INSERT INTO `player_stats` \
            (`u_id`) \
        VALUES \
            ('%d') \
    ";

    format(string, sizeof string, 
        query,
        Player_GetAccountID(playerid)
    );
    mysql_tquery(MySQL_GetHandle(), string);
    return 1;
}

stock Player_GiveAdmin(playerid, level, bool:save = false) {
    new
        currentLevel = Player_GetAdmin(playerid),
        newLevel = currentLevel + level,
        string[70]
    ;
        
    PlayerAdmin[playerid] = newLevel;
    
    if(save) {
        static const query[] = "\
            UPDATE \
                player_stats \
            SET \
                admin_level = %d \
            WHERE \
                u_id = %d \
        ";

        mysql_format(MySQL_GetHandle(), string, sizeof string, 
            query,
            newLevel,
            Player_GetAccountID(playerid)
        );
        mysql_tquery(MySQL_GetHandle(), string);
    }
}

stock Player_GetAdmin(playerid) {
    return PlayerAdmin[playerid];
}

stock Player_GiveKill(playerid, kills, bool:save = false) {
    new
        currentKills = Player_GetKills(playerid),
        newKills = currentKills + kills,
        string[71]
    ;

    PlayerKills[playerid] = newKills;

    if(save) {
        static const query[] = "\
            UPDATE \
                player_stats \
            SET \
                kills = %d \
            WHERE \
                u_id = %d \
        ";

        mysql_format(MySQL_GetHandle(), string, sizeof string, 
            query,
            newKills,
            Player_GetAccountID(playerid)
        );
        mysql_tquery(MySQL_GetHandle(), string);
    }
}

stock Player_GetKills(playerid) {
    return PlayerKills[playerid];
}

stock Player_GiveDeath(playerid, deaths, bool:save = false) {
    new
        currentDeaths = Player_GetDeaths(playerid),
        newDeaths = currentDeaths + deaths,
        string[71]
    ;

    PlayerDeaths[playerid] = newDeaths;
    
    if(save) {
        static const query[] = "\
            UPDATE \
                player_stats \
            SET \
                deaths = %d \
            WHERE \
                u_id = %d \
        ";

        mysql_format(MySQL_GetHandle(), string, sizeof string, 
            query,
            newDeaths,
            Player_GetAccountID(playerid)
        );
        mysql_tquery(MySQL_GetHandle(), string);
    }
}

stock Player_GetDeaths(playerid) {
    return PlayerDeaths[playerid];
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