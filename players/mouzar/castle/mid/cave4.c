 
inherit"/room/room";
reset(arg) {
if(!arg) {
 
           set_light(1);
short_desc = "A dark cave";
long_desc = "This cave leads deeper in to the mountain.  It is hard to see\n" +
           "where you are going cause the only light source is from the\n" +
           "glowing fungus on the walls.\n";
dest_dir = ({
             "/players/mouzar/castle/mid/cave3","south",
             "/players/mouzar/castle/mid/cave5","north",
	     "/players/mouzar/castle/under/under1","down"
                      });
           }
       }
 
