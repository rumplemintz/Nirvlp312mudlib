

inherit "room/room";

reset(arg) {
    if (arg) return;

    set_light(1);
    short_desc = "The Lair of the Blood Fisted Clan";
    no_castle_flag = 0;
    long_desc =
        "You are in the upper level of the cave. It is dark and dank\n"
        + "here. You here the sounds of water dripping and see that the\n"
        + "walls are damp. You hear a low rumbling noise running through\n"
        + "cave. Perhaps you should turn back before you run into any of\n"
        + "clansmen. An omnious fear presses down on you from all sides.\n"
	+ "To the east you see an open room, full of orcs and what appears\n"
	+ "to be a throne, perhaps you should check this out.\n";

items = ({
	"walls", "Damp cavern walls covered with calcium residue."+
                 " How cheery",
});
dest_dir = ({
	"/players/pain/NEW/lair7", "north",
	"/players/pain/NEW/lair9", "south",
});
if(!present("orc"))
{
move_object(clone_object("/players/pain/NEW/mon/orc_e"),this_object());
move_object(clone_object("/players/pain/NEW/mon/orc_e"),this_object());
move_object(clone_object("/players/pain/NEW/mon/orc_w"),this_object());
move_object(clone_object("/players/pain/NEW/mon/orc_w"),this_object());
}
}

init() {
	::init();
add_action("east", "east");
}

realm() { return "NT"; }

east() {
  if(!present("orc")) {
    this_player()->move_player("into the throne room#/players/pain/NEW/throne");
    return 1;
  }
  write("The orc maneuvers to block your path!\n");
  say("An orc maneuvers to block "+this_player()->query_name()+"'s path!\n");
  return 1;
}
query_light() {
    return 1;
}
query_room_maker() {
    return 101;
}

/*
    remove the comments around the "room is modified()" code
    below to prevent changes you have done to this room to
    to be lost by using the room maker
*/
/*
room_is_modified() {
    return 1;
}
*/

/*
 make your additions below this comment, do NOT remove this comment
--END-ROOM-MAKER-CODE--
*/
