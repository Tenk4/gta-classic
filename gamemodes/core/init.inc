#include <a_mysql>
#include <YSI_Coding\y_hooks>

#define		MYSQL_HOST 			"127.0.0.1"
#define		MYSQL_USER 			"root"
#define		MYSQL_PASSWORD 		"11211121"
#define		MYSQL_DATABASE 		"classic"

static 
    MySQL: MySQL_ConHandle;

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
	switch(errorid) {
		case 1136: printf("[MySQL] Error 1136 | Column count does not match value count => \"%s\"", query);
		case 1054: printf("[MySQL] Error 1054 | Invalid field name => \"%s\"", query);
		case 1065: printf("[MySQL] Error 1065 | Query was empty (variable's size too small?) => \"%s\" from \"%s\"", query, callback);
		case 1058: printf("[MySQL] Error 1058 | Column count doesn't match value count => \"%s\" from \"%s\"", query, callback);
		case 1203: printf("[MySQL] Error 1203 | User already has more than 'max_user_connections' active connections => \"%s\" from \"%s\"", query, callback);
		case 1045: printf("[MySQL] Error 1045 | Access denied");
		case ER_SYNTAX_ERROR: printf("[MySQL] Syntax Error => \"%s\"",query);

		default : printf("[MySQL] Error %d | Callback: %s | \"%s\"", errorid, callback, query);
	}
	return 1;
}

hook OnGameModeInit()
{
	new MySQLOpt: option_id = mysql_init_options();

	mysql_set_option(option_id, AUTO_RECONNECT, true);

	MySQL_ConHandle = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, option_id); 
	if (MySQL_ConHandle == MYSQL_INVALID_HANDLE || mysql_errno(MySQL_ConHandle) != 0)
	{
		print("[MySQL] Connection failed. Server is shutting down.");
		SendRconCommand("exit");
		return 1;
	}

	print("[MySQL] Connection is successful.");

    mysql_set_charset("tis620");
	return 1;
}

hook OnGameModeExit()
{
	mysql_close(MySQL_ConHandle);
	return 1;
}

stock MySQL:MySQL_GetHandle() {
    return MySQL_ConHandle;
}