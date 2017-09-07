#include <ansi.h>
#include "/sys/lib.h"
inherit "obj/treasure";

int active;

reset(arg) {
	::reset(arg);
	if(arg) return;
	active=0;
	set_name("fountain");
	set_short("A fountain");
	set_long("There is a large fountain directly in the center of Amber\n"+
					"full of delicious looking water.\n");
	set_weight(9999);
}

init() {
	::init();
	add_action("cmd_drink", "drink");
}

cmd_drink(arg) {
	if(arg == "fountain") {
		if((this_player()->query_intoxination() > this_player()->query_max_intox()) ||
			(this_player()->query_soaked() > this_player()->query_max_soak())) {
			write("You don't require any more from the fountain.\n");
			return 1;
		}
		write_file("/players/oberon/closed/logs/FOUNTAIN", ctime()+" - Drank: "+this_player()->query_real_name()+".\n");
		write("You drink from the fountain.\n");
		say(this_player()->query_name()+" drinks from the fountain.\n");
		this_player()->add_intoxination(1);
		this_player()->add_soaked(300);

		if(random(20) == 1) {
			write_file("/players/oberon/closed/logs/FOUNTAIN", ctime()+" - Activate: "+this_player()->query_real_name()+".\n");
			/* For future use */
			/* write("As you drink, a very faint image appears at the bottom of the fountain.\n"); */
			/* add_item for 'image' */
			active=1;
		}
		return 1;
	}
	return 0;
}
