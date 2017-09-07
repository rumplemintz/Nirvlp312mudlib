#define NAME "Oberon"
#define DEST "room/mine/tunnel4"

/*
 * This is just the facade to a castle. If you want to enable the
 * "enter" command, move the player to a hall or something (which
 * you have to design yourself).
 * The predefined string DEST is where a player should come when he
 * leaves the castle.
 *
 * This file is loaded automatically from "init_file". We have to move
 * ourself to where we are supposed to be.
 */

id(str) { return str == "pattern"; }
short() { return "A large Pattern is etched into the ground"; }
long() {
	write("There is a strange pattern drawn on the ground here. It appears to\n");
	write("be a single, intertwined curve, laid out in a spiderweb-like shape.\n");
	write("There is small jewel in the center of the pattern.\n");
}

init() {
	add_action("enter", "enter");
	add_action("enter", "walk");
}

enter(str) {
	if(!id(str)) {
		write("You feel the urge to 'walk' the 'pattern'.\n");
		return 1;
	}
	write("As you start to walk the Pattern, you notice yourself somewhere new.\n");
	say(this_player()->query_name()+" starts to walk on the Pattern and disappears.\n");
	move_object(this_player(), "/players/oberon/amber/city/rooms/pattern1");
	command("look", this_player());
	return 1;
}

reset(arg) {
	if (arg) return;
	move_object(this_object(), DEST);

	/** Initialize Auto Load Objects **/
	destruct(clone_object("/players/oberon/guild/testautoload.c"));
}

is_castle(){return 1;}
