#define GUILDNAME "Jedi"
/** Directories **/
#define CMDDIR "/players/guilds/Jedi/bin/"
#define DOCDIR "/players/guilds/Jedi/docs/"
#define SPELLDIR "/players/guilds/Jedi/force/"
#define DAEMONDIR "/players/guilds/Jedi/daemons"
#define CMDBASE "/players/guilds/Jedi/lib/command"
#define OBJDIR "/players/guilds/Jedi/obj"
#define LIB "/players/guilds/Jedi/lib/"
#define HALL "/players/guilds/Jedi/hall"
#define SAVE_PATH "players/guilds/Jedi/member/"

#define CHAN "/bin/channel_daemon"
#define GUILD_FILE "players/guilds/Jedi/gob"
#define ERROR "/players/guilds/Jedi/logs/ERROR"
#define LOG "/players/guilds/Jedi/logs/"

/** Daemons **/
#define ACTIONS "/players/guilds/Jedi/daemons/actions.c"
#define LEV     "/players/guilds/Jedi/daemons/JediLevels.c"
#define DEATH   "/players/guilds/Jedi/daemons/JediDeath.c"

/** Skills **/
#define SABER "saber"
#define PHYS  "physical"
#define TELE  "telepathy"
#define KIN   "telekinesis"
#define SKILL_TYPES ({ SABER, PHYS, TELE, KIN })

/** Skill Ranks **/
#define DEFAULT_SKILL_RANK ({ 1, 0 })
#define RANK_IDX 0
#define EXP_IDX 1
#define SKILL_RANK_ATTR ({ "rank", "exp" })

/** Skill costs **/
#define CONVERGE_SKILL 7
#define CONVERGE_COST 50
#define SPEED_SKILL 7
#define SPEED_COST 50
#define MEDITATE_SKILL 1
#define MEDITATE_COST 10

/** Need to get rid of these **/
#define USER environment(this_object())
#define HP USER->query_hp()
#if 0
#define attack USER->query_attack()
#endif
#define user USER
#define MSP user->query_msp()
#define wielded_saber present("lightsaber", environment(this_object()))->query_wielded()
#define Rank USER->query_guild_rank()
#define GXP USER->query_guild_exp()
#define PO previous_object()

/** Defines **/
#define RDIR (!random(2) ? "left" : "right")
#define MAXCOINS 40000
#define MIN_SP -30
#define CHAN_NAME "jedi"
#define MAX_SABERS 2
#define SABER1 0
#define SABER2 1
#define JEDI_CLAN "jedi"
#define SITH_CLAN "sith"
