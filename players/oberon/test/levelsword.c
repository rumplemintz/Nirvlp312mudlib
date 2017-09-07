#include <ansi.h>
#include "/sys/lib.h"
inherit "obj/weapon";

int wepexp, weplvl;
int PSE, PEE; /* player start exp, player end exp */

reset(arg) {
	::reset(arg);
	if(arg) return;
	set_id("level_sword");
	set_name("Leveling Sword");
	set_alias("sword");
	set_short("A Leveling Sword");
	set_long("A sword that levels the more you kill.\n");
	set_class(1);
	set_weight(1);
	set_value(0);
	set_save_flag(0);
	set_hit_func(this_object());
	
	wepexp = 0;
	weplvl = 1;
}

weapon_hit(attacker) {
	int dmg;
	
	if(!PSE || PSE==0) PSE = this_player()->query_exp();
	
	write("Level: "+this_object()->query_weplvl()+", Exp: "+this_object()->query_wepexp()+", PSE: "+PSE+"\n");
	dmg = random(500); /* High dmg to test */
	wepexp += dmg;
	do_level();
	
	return dmg;
}

query_wepexp() { return wepexp; }
query_weplvl() { return weplvl; }

do_level() {
	if((weplvl==1 && wepexp>=1014)
		|| (weplvl==2 && wepexp>=1771)
		|| (weplvl==3 && wepexp>=2332)
		|| (weplvl==4 && wepexp>=5885)
		|| (weplvl==5 && wepexp>=12812)
		|| (weplvl==6 && wepexp>=26662)
		|| (weplvl==7 && wepexp>=39993)
		|| (weplvl==8 && wepexp>=59995)
		|| (weplvl==9 && wepexp>=90000)
		|| (weplvl==10 && wepexp>=134998)
		|| (weplvl==11 && wepexp>=195591)
		|| (weplvl==12 && wepexp>=295592)
		|| (weplvl==13 && wepexp>=492294)
		|| (weplvl==14 && wepexp>=620026)
		|| (weplvl==15 && wepexp>=820028)
		|| (weplvl==16 && wepexp>=1040028)
		|| (weplvl==17 && wepexp>=1367106)
		|| (weplvl==18 && wepexp>=2000000)
		|| (weplvl==19 && wepexp>=2500000)
		|| (weplvl==20 && wepexp>=2700000)
		|| (weplvl==21 && wepexp>=2900000)
		|| (weplvl==22 && wepexp>=3300000)
		|| (weplvl==23 && wepexp>=3600000)
		|| (weplvl==24 && wepexp>=3900000)
	) {
		write(HIR+"Your sword shakes and glows!\n"+NORM);
		weplvl += 1;
		set_class(weplvl);
	}
}

add_exp(amt) {
	write("EXP: "+amt+"\n");
	
}

/*
catch_tell(string str) {
	int expgain;
	if(sscanf(str, "Experience Gain: %i\n", expgain) == 2) {
		write(HIC+"Your sword pulses. ["+expgain+"]\n");
	}
}
*/

