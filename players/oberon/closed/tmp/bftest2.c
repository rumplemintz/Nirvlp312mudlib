inherit "/players/forbin/closed/bfeq.c";
#include "/players/jaraxle/define.h"

reset(arg){
	if(arg) return;
	::reset();
	set_name("cloak");
	set_alias("cloak");
	set_short(""+NORM+""+RED+"Blood"+NORM+" stained cloak");
	set_long("   Cloak forged from some unknown material. There are"+RED+" blood\n"+
		""+NORM+"stains covering these Cloak. Although dirty, they seem to be\n"+
		"in amazing condition\n");

	set_ac(20);
	set_type("cloak");
	set_weight(1);
	set_value(0);
	/* first # is which stat, second number is increase in that stat.
	0 = agility
	1 = might
	2 = accuracy
	3 = vigor
	4 = wisdom
	5 = faith
	*/
	set_bf_guild_bonus(0, 100);
	set_bf_guild_bonus(1, 100);
	set_bf_guild_bonus(2, 100);
	set_bf_guild_bonus(3, 100);
	set_bf_guild_bonus(4, 100);
	set_bf_guild_bonus(5, 100);
}
