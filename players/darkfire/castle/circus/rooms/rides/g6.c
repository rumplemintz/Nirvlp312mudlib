#pragma strict_types

#include "/players/darkfire/castle/circus/circus.h"
#include "_area.h"

/* Inherit the area's base room. */
inherit "/players/darkfire/castle/circus/rooms/rides/_base.c";

void
reset(int arg) {
	::reset();

	if(arg) return;

	set_col(6);
	set_row(5);

	set_short(CAROUSEL_NAME);
	
	set_long(get_carousel_description());

	add_exits("n,e,w");
}

void
init() {
	::init();
}