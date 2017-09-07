#include "atlas.h"
inherit "/obj/treasure";



id(str) { return str=="atlas"; }
short() { return "Adventurer's Atlas"; }
long() { write("A book of maps. Use 'atlas_help' for commands.\n"); }



reset(arg) {
	::reset(arg);
	if(arg) return;
	set_name("atlas");
}

init() {
	::init();
	add_action("maplist","maplist");
	add_action("show_help","atlas_help");
	add_action("save_atlas","save_atlas");
}

get() { return 1; }
drop() { return 1; }
query_weight() { return 0; }
query_value() { return 0; }

show_help(topic) {
	/* Atlas Help */
	write("Atlas Help System.\n");
	return 1;
}

maplist(arg) {
	/* Query .o object for available maps, and make maps available from maps/ */
	write("There are currently no maps in your atlas!\n");
	return 1;
}


/*************************/
/* MAP CONTROL FUNCTIONS */
/*************************/
set_current(map) { /* Change currently selected map */ }
query_current(map) { /* Return currently selected map */ }

save_atlas() {
	string file;
	file = SAVE_DIR + environment()->query_real_name();
	if (!save_object(file)) {
		tell_object(this_user(), "Error in saving your Atlas!\n");
		return 0;
	} else return 1;
}


/***************************/
/* MAP RECORDING FUNCTIONS */
/***************************/
add_step(arg) { /* Manually add a direction/room. Used for abnormal exits */ }
record_steps(arg) { /* Proccess to create maps via path-walking */ }
set_areadirs(arg) { /* Set the directions to an area from Green */ }








