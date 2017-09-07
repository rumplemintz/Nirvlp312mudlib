#include "/sys/ansi.h"
#include "/sys/lib.h"
inherit "/room/room";

reset(arg) {
	::reset(arg);
	if(arg) return;
	set_light(1);
	short_desc = "Along the northern wall";
	long_desc =
		"Along the northern wall of Amber. The road is paved with colorful\n"+
		"cobblestone. To the north is an enormous wall that seems to wrap\n"+
		"around the whole city. Sounds of the citizens can be heard from the\n"+
		"streets and shops. The street extends to the east and west.\n";
	items = ({
		"cobblestone","Gorgeous stones carefully positioned on the ground.",
		"stones","The way the stones lay is truly a work of art.",
	});
	dest_dir = ({
		"/players/oberon/amber/city/rooms/northwall4","east",
		"/players/oberon/amber/city/rooms/northgate","west",
	});
	if(random(2)) move_object(clone_object("/players/oberon/amber/city/mob/adult.c"), this_object());
	if(random(2)) move_object(clone_object("/players/oberon/amber/city/mob/kid.c"), this_object());
}