#include "/sys/ansi.h"
#include "/sys/lib.h"
inherit "/room/room";

reset(arg) {
	::reset(arg);
	if(arg) return;
	set_light(1);
	short_desc = "Amber Adventure Shop";
	long_desc =
		"There is a strange man here, who barely seems to notice you. All\n"+
		"around are various trinkets and gadgets, all in various stages of\n"+
		"completion. It's hard to believe he has anything finished to sell\n"+
		"within this huge mess!\n";
	items = ({
		"shop","The shop surrounds you, and protects you from the horrors of life",
		"plants","Various food based plants",
	});
	dest_dir = ({
		"/players/oberon/amber/city/rooms/amberstreet1","south",
	});
	move_object(clone_object("/players/oberon/amber/city/mob/shopkeeper_misc.c"), this_object());
}
