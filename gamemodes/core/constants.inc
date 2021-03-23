#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS             100

#define SERVER_NAME             "GTA Classic"
#define SERVER_VERSION          "0.01"

#define MAX_BAN_REASON          32
#define BCRYPT_COST             12

#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))