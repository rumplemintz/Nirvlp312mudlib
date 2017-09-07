#include "/sys/ansi.h"
#include "/sys/lib.h"
inherit "/room/room";

int i;

reset(arg) {
	::reset(arg);
	if(arg) return;
	set_light(1);
	short_desc = "Eastern Guard Shack";
	long_desc =
		"The guard house is made mostly of stone. The walls are a dull grey\n"+
		"stone, while the floor is a nice cobblestone. Various racks of armor\n"+
		"and weapons line the walls. There is a cot in the corner of the room,\n"+
		"and chairs for the guards to rest on. To the west leads back to\n"+
		"Castle Way.\n";
	items = ({
		"stone","The stones hold very little of interest",
		"stones","The stones hold very little of interest",
		"walls","There are walls. They are dull and grey",
		"floor","The cobblestone makes the floor only slightly more interesting than the walls",
		"cobblestone","The cobblestone makes the floor only slightly more interesting than the walls",
		"racks","The racks hold all the spare guard armor",
		"weapons","There are mostly short swords on the weapon racks",
		"armor","There are many spare shields stacked on the racks",
		"cot","In the corner of the room is a cot for guards to rest on",
		"chairs","Just normal chairs, waiting to be sat upon",
	});
	dest_dir = ({
		"/players/oberon/amber/city/rooms/castleway1","west",
	});

	for(i=random(2); i>=0; i--)
		move_object(clone_object("/players/oberon/amber/city/mob/gateguard.c"), this_object());
}
