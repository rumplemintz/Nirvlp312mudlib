inherit "room/room";
reset(arg){
        if(!arg){
        set_light(1);
        short_desc="The Top";
        long_desc="  You have reached the top floor of Bane's castle.  There are many\n"+
                "things to learn if you want to reach Bane himself.  The task is not an\n"+
                "easy one, but you feel as though it can be accomplished.\n";
        dest_dir=({
		"players/rumplemintz/room/bane/castle/floor3/room25", "down",
		"players/rumplemintz/room/bane/castle/floor4/room2", "northeast",
        });
        }
}
