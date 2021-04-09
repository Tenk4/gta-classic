#include <YSI_Coding\y_hooks>

static
    PlayerSkin[MAX_PLAYERS] = -1,
    bool:PlayerNew[MAX_PLAYERS] = false;

hook OnPlayerRegister(playerid) {
    PlayerNew[playerid] = true;
    return 1;
}

hook OnPlayerConnect(playerid) {
    PlayerSkin[playerid] = -1;
    PlayerNew[playerid] = false;
    return 1;
}

hook OnPlayerLogin(playerid) {
    Player_SkinLoad(playerid);
    return 1;
}

hook OnPlayerFirstSpawn(playerid) {

    new
        skinid = Player_GetSkin(playerid);

    SetPlayerSkin(playerid, skinid);

    if(PlayerNew[playerid]) {
        Player_SetSkin(playerid, skinid, true);
    }
    return 1;
}

Player_SkinLoad(playerid) {
    inline _LoadSkin() {
        new
            playerSkin,
            rows
        ;

        cache_get_row_count(rows);

        if(rows) {
            cache_get_value_name_int(0, "skin", playerSkin);

            Player_SetSkin(playerid, playerSkin);
        }
    }

    static const query[] = "\
        SELECT \
            skin \
        FROM \
            player_stats \
        WHERE \
            u_id = %d \
    ";

    MySQL_TQueryInline(MySQL_GetHandle(), using inline _LoadSkin, query, Player_GetAccountID(playerid));
}

stock Player_SetSkin(playerid, skinid, bool:save = false) {

	PlayerSkin[playerid] = skinid;

    new
        string[71]
    ;

    if(save) {
        static const query[] = "\
            UPDATE \
                player_stats \
            SET \
                skin = %d \
            WHERE \
                u_id = %d \
        ";

        mysql_format(MySQL_GetHandle(), string, sizeof string, 
            query,
            skinid,
            Player_GetAccountID(playerid)
        );
        mysql_tquery(MySQL_GetHandle(), string);
    }
}

stock Player_GetSkin(playerid) {
	return PlayerSkin[playerid];
}