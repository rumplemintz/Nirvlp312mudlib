#include <ansi.h>
inherit "/obj/monster";

int GENDER;

reset(arg) {
	::reset(arg);
	if(arg) return;
	GENDER = random(2);
	
	set_name(((GENDER)?"Male":"Female")+" Citizen");
	set_alias("citizen");
	set_race("human");
	set_short("A "+((GENDER)?"Male":"Female")+" Citizen");
	set_long("One of Amber's many citizens.\n");
	set_gender(((GENDER)?"Male":"Female"));
	set_level(16);
	set_aggressive(0);
	set_al(0);
	add_money(600+random(1000));

	wander = 1; /* whether we wander or not */
	wander_interval = 7; /* how often we move */
	wander_count = 10; /* count heartbeats until next wander */
	wander_realm = "/players/oberon/amber/city/rooms/"; /* base file path we are allowed to wander */
}

init() {
	::init();
}

heart_beat() {
	::heart_beat();
}
