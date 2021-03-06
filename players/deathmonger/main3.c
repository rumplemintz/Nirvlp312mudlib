

inherit "room/room";

reset(arg) {
    if (arg) return;

    set_light(0);
    short_desc = "Main road";
    no_castle_flag = 0;
    long_desc = 
        "Progress through the swamp is very slow.  Fortunately, you can see some light\n"
        + "to the north.\n";
    dest_dir = 
        ({
        "/players/deathmonger/main2", "south",
        "/players/deathmonger/main4", "north",
        "/players/deathmonger/CASTLE/deathlair", "west",
        });
}

query_light() {
    return 0;
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

