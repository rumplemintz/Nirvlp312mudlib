#include "/players/illarion/ansi.h"
#define GDIR "players/illarion/guild/"
#define GMON "/players/illarion/guild/mon/"
#define GROOM "/players/illarion/guild/room/"
#define POWER_DIR "/players/illarion/guild/power/"
#define SAVE_DIR "players/illarion/guild/member/"
#define DOC "/players/illarion/guild/doc/"
#define TP this_player()
#define QN(x) (string)x->query_name()
#define QRN(x) (string)x->query_real_name()
#define TPN this_player()->query_name()
#define TPRN this_player()->query_real_name()
#define OBJ(x) (string)x->query_objective()
#define PRO(x) (string)x->query_pronoun()
#define POS(x) (string)x->query_possessive()
#define GR query_guild_rank()
#define GX query_guild_exp()
#define GN query_guild_name()
#define FAIL(x) { notify_fail(x); return 0; }
#define OB_NAME "blademaster_guild_object"
#define WEP_NAME "blademaster_guild_weapon"
#define ENTO environment(this_object())
#define ENV(x) (object)environment(x)
#define TO this_object()
#define BLD(x) "\""+BOLD+x+NORM+"\""
#define SCALE "/players/illarion/guild/daemons/scale.c"
#define DAEM "/players/illarion/guild/daemons/daem.c"
#define IBUG(x) tell_object(find_player("illarion"),x);
#define SOULS_PER_MON_LEVEL 10
#define SOULS_PER_SKILL_LEVEL 100