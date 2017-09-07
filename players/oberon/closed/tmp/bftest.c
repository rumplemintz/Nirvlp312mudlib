inherit "/players/forbin/closed/bfeq.c";
#include "/players/jaraxle/define.h"

reset(arg){
	if(arg) return;
	::reset();
	set_name("pants");
	set_alias("pants");
	set_short(""+NORM+""+RED+"Blood"+NORM+" stained pants");
	set_long("   Pants forged from some unknown material. There are"+RED+" blood\n"+
		""+NORM+"stains covering these pants. Although dirty, they seem to be\n"+
		"in amazing condition\n");

	set_ac(20);
	set_type("pants");
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
	set_bf_guild_bonus(0, 10);
	set_bf_guild_bonus(1, 20);
	set_bf_guild_bonus(2, 30);
	set_bf_guild_bonus(3, 40);
	set_bf_guild_bonus(4, 50);
	set_bf_guild_bonus(5, 60);
}
