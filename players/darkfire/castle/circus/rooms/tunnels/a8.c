#pragma strict_types

#include "/players/darkfire/castle/circus/circus.h"
#include "_area.h"

/* Inherit the area's base room. */
inherit "/players/darkfire/castle/circus/rooms/tunnels/_base.c";

void
reset(int arg) {
	::reset();

	if(arg) return;

	set_col(0);
	set_row(7);

	set_long_deadend();

	add_exits("s");
	add_exit(PATH_TENTS + "h5", "tents");
}

void
init() {
	::init();
}