#include "roomgod.c"
inherit "room/room";

string zone;
string zone() { return zone; }
init() { add_action("goplace", "hangar"); ::init(); }

reset(arg) {
   if(!arg) {
   set_light(1);
   short_desc=("Red Zone");
   zone = "Red Zone";
   long_desc=
"     A large X-shaped battlefield stretches out before you.\n"+
"Tall metal and rock walls form the borders of the field.\n"+
"Situated upon these walls stand several red flags.\n";

   dest_dir=({
   "/players/dune/closed/pavilion/rooms/field/red2.c",   "e",
   "/players/dune/closed/pavilion/rooms/field/red3.c",   "s",
   "/players/dune/closed/pavilion/rooms/field/red4.c",   "se",
   "/players/dune/closed/pavilion/rooms/field/white4.c", "w",
   "/players/dune/closed/pavilion/rooms/field/white2.c", "nw",
   "/players/dune/closed/pavilion/rooms/roboshop.c", "hangar",
        });

   items=({
   "flags","These flags signify the color of zone your are in",
   "walls","The walls are very sturdy",
   "battlefield","The battlefield is X-shaped.\n"+
                 "You are in only one of the five zones",
        });
   }   }
