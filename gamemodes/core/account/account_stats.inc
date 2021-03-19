#include <YSI_Coding\y_hooks>

static
    PlayerAdmin[MAX_PLAYERS],
    Float:PlayerArmour[MAX_PLAYERS],
    Float:PlayerHealth[MAX_PLAYERS],
    PlayerKills[MAX_PLAYERS],
    PlayerDeaths[MAX_PLAYERS],
    PlayerWantedLevel[MAX_PLAYERS],
    PlayerMoney[MAX_PLAYERS],
    PlayerSkin[MAX_PLAYERS];

Account_LoadStats(playerid) {
    new
        query[64];

    format(query, sizeof query, 
    "\
        SELECT * FROM `player_stats` WHERE `u_id` = '%e' LIMIT 1\
    ",
        Player_GetAccountID(playerid)
    );
    mysql_tquery(MySQL_GetHandle(), query, "Player_StatsLoaded", "d", playerid);
}

forward Player_StatsLoaded(playerid);
public Player_StatsLoaded(playerid) {
    new
        rows;
    
    cache_get_row_count(rows);

    if(rows) {
        cache_get_value_name_int(0, "admin_level", PlayerAdmin[playerid]);
        cache_get_value_name_float(0, "armour", PlayerArmour[playerid]);
        cache_get_value_name_float(0, "health", PlayerHealth[playerid]);
        cache_get_value_name_int(0, "kills", PlayerKills[playerid]); 
        cache_get_value_name_int(0, "deaths", PlayerDeaths[playerid]);
        cache_get_value_name_int(0, "wanted_level", PlayerWantedLevel[playerid]);    
        cache_get_value_name_int(0, "money", PlayerMoney[playerid]); 
        cache_get_value_name_int(0, "skin", PlayerSkin[playerid]);   
    }
    return 1;
}

hook OnPlayerLogin(playerid) {
    Account_LoadStats(playerid);
    return 1;
}

hook OnPlayerRegister(playerid) {
    new
        query[60];

    format(query, sizeof query, 
    "\
        INSERT INTO `player_stats` \
            (`u_id`) \
        VALUES \
            ('%d')\
    ", 
        Player_GetAccountID(playerid)
    );
    mysql_tquery(MySQL_GetHandle(), query);
    return 1;
}

stock Player_GiveAdmin(playerid, level, bool:save = false) {
    new
        currentLevel = Player_GetAdmin(playerid),
        newLevel = currentLevel + level;
        
    PlayerAdmin[playerid] = newLevel;
    
    if(save) {
        new 
            query[64];

        mysql_format(MySQL_GetHandle(), query, sizeof query, 
        "\
            UPDATE \
                player_stats \
            SET \
                admin_level = %d \
            WHERE \
                u_id = %d \
        ",
            newLevel,
            Player_GetAccountID(playerid)
        );
        mysql_tquery(MySQL_GetHandle(), query);
    }
}

stock Player_GetAdmin(playerid) {
    return PlayerAdmin[playerid];
}

stock Player_GiveKill(playerid, kills, bool:save = false) {
    new
        currentKills = Player_GetKills(playerid),
        newKills = currentKills + kills;

    PlayerKills[playerid] = newKills;

    if(save) {
        new 
            query[64];

        mysql_format(MySQL_GetHandle(), query, sizeof query, 
        "\
            UPDATE \
                player_stats \
            SET \
                kills = %d \
            WHERE \
                u_id = %d \
        ",
            newLevel,
            Player_GetAccountID(playerid)
        );
        mysql_tquery(MySQL_GetHandle(), query);
    }
}

stock Player_GetKills(playerid) {
    return PlayerKills[playerid];
}

stock Player_GiveDeath(playerid, kills, bool:save = false) {
    new
        currentDeaths = Player_GetDeaths(playerid),
        newDeaths = currentDeaths + deaths;

    PlayerDeaths[playerid] = newDeaths;
    
    if(save) {
        new 
            query[64];

        mysql_format(MySQL_GetHandle(), query, sizeof query, 
        "\
            UPDATE \
                player_stats \
            SET \
                deaths = %d \
            WHERE \
                u_id = %d \
        ",
            newLevel,
            Player_GetAccountID(playerid)
        );
        mysql_tquery(MySQL_GetHandle(), query);
    }
}

stock Player_GetDeaths(playerid) {
    return PlayerDeaths[playerid];
}