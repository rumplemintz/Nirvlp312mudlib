 
inherit"/room/room";
reset(arg) {
if(!arg) {
 
 
set_light(1);
short_desc = "A HOT desert";
long_desc = "You are scorched by the hot sun.  You are getting thirsty.  You\n"+
            "start to wonder if this was a good idea.  Are you lost?  Will You\n"+
            "ever get out?  To the east is a mountain range.  Off to the north\n"+
            "you can see an animal of some kind.\n";
 
dest_dir = ({
             "/players/mouzar/castle/high/des12", "south",
             "/players/mouzar/castle/high/des13", "north",
             "/players/mouzar/castle/high/des22", "west",
             "/players/mouzar/castle/high/des2", "east",
         });
             
       }
     
         }