#include "ansi.h"
inherit "/obj/armor.c";

object wepp, atk;
int hypermode, times;

id(str) { return str == "ring" || str == "ros"; }
short() { return "Ring of Speed"; }
long() { write("A Ring of Speed.\n"); }

reset(arg) {
	if(arg) return;
	::reset(arg);
	hypermode = 0;
	set_type("ring");
	set_weight(1);
	set_value(0);
}

init() {
	::init();
	add_action("go_hyper", "hypermode");
	add_action("hypercheck", "hypercheck");
}

do_special(owner) {
	if(!owner || !owner->query_attack()) return 1;
	if(!owner->is_player()) return 1;
		
	atk = owner->query_attack();
	times = hypermode;

	while(atk && times--) {
		tell_object(owner, HIR+"You vibrate violently!\n"+NORM);
		/*
		owner->add_spell_point(-20);
		owner->add_hit_point(-20);
		*/
		owner->toggle_already_fight(1);
	  if(wepp = owner->query_weapon())
			wepp->hit(owner->query_attack());
		owner->attack();
	}

	return 1;
}

go_hyper(arg) {
	if(!arg) return 0;
	write("You start to vibrate at level "+arg);
	set_hyper(arg);
	return 1;
}
hypercheck() {
	write("Hypermode: "+query_hyper()+".\n");
	return 1;
}

set_hyper(amt) { hypermode = amt; }
query_hyper() { return hypermode; }
