inherit "room/room";
int i;
reset(arg) {
        if(!present("troglodyte")) {
        for(i=0;i<4;i++) {
        move_object(clone_object("players/dersharp/monsters/trog"), this_object());
        }
   }
        if(!arg) {
                set_light(1);
        short_desc ="A musty room";
        long_desc ="The evil permeates the air as you look in this room\n"+
                   "Creatures of the Shadow Master rise up to destroy you!\n";
        dest_dir = ({

                "players/dersharp/pillars/room16.c", "north",
                "players/dersharp/pillars/room24.c", "south",
                });

        }
}