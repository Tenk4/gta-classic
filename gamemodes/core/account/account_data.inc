#include <YSI_Coding\y_hooks>

enum ACC_DATA {
    ID,
    Name[MAX_PLAYER_NAME],
    Password[129],
    DateReg[11],
    TimeReg[9],
    IP[16]
};
new accData[MAX_PLAYERS][ACC_DATA];

hook OnPlayerConnect(playerid) {
	static const empty_player[ACC_DATA];
	accData[playerid] = empty_player;
    return 1;
}