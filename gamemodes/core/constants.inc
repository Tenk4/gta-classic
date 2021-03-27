#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS             100

#define SERVER_NAME             "GTA Classic"
#define SERVER_VERSION          "0.01"

#define MAX_BAN_REASON          32
#define BCRYPT_COST             12

#define SQL_DATETIME_FORMAT     "%%d/%%m/%%Y (%%T)"
#define SQL_DATE_FORMAT         "%d %M %Y"

#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))