inherit "room/room";
reset(arg) {
        if(!arg) {
                set_light(1);
        short_desc = "The wilderness of Kor";
        long_desc = "     You have wandered into the land of Kor, the Orc Lord.\n"+
                "Orcs of Kor are not aggressive, and are not very strong.  They are\n"+
                "however, very ugly!  Good luck on your journey through the lands.\n";
        dest_dir = ({

                "players/rumplemintz/room/kor/room7", "north",
                "players/rumplemintz/room/kor/room5", "southwest",
                });

        }
}