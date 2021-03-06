#include "/sys/ansi.h"
#include "/sys/lib.h"
inherit "/room/room";

reset(arg) {
	::reset(arg);
	if(arg) return;
	set_light(1);
	short_desc = "Along the southern wall";
	long_desc =
		"Along the southern wall of Amber. The road is paved with colorful\n"+
		"cobblestone. To the south is an enormous wall that seems to wrap\n"+
		"around the whole city. Sounds of the citizens can be heard from the\n"+
		"streets and shops. To the west is the southern gate.\n";
	items = ({
		"cobblestone","Gorgeous stones carefully positioned on the ground.",
		"stones","The way the stones lay is truly a work of art.",
	});
	dest_dir = ({
		"/players/oberon/amber/city/rooms/southgate", "west",
		"/players/oberon/amber/city/rooms/southwall4", "east",
	});
	if(random(2)) move_object(clone_object("/players/oberon/amber/city/mob/adult.c"), this_object());
	if(random(2)) move_object(clone_object("/players/oberon/amber/city/mob/kid.c"), this_object());
}
