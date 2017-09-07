inherit "/players/oberon/closed/hanzo/weapon2.c";

id(str) { return str == "hanzo" || str == "sword" || str == "test_sword"; }

/*
short() {
	if(wielded_by) {
		if(wielded_by == this_player())
			return "Your Hanzo Sword "+((two_handed_wield)?"(wielded in both hands)":"(wielded)");
		else
			return wielded_by->query_name()+"'s Hanzo sword "+((two_handed_wield)?"(wielded in both hands)":"(wielded)");
	}
	else return "A Hanzo Sword";
}
*/
long() { write("A very special Hanzo Sword.\n"); }

reset(arg) {
	::reset(arg);
	if (arg) return;

	set_short("A Hattori Hanzo Sword");
	set_type("sword");
	set_class(20);
	set_weight(1);
	set_two_handed_wep(1);
	set_no_break(1);
}
