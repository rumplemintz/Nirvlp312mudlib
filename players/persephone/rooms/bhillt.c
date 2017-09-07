inherit "/players/persephone/closed/thingys.c";
#include "/players/persephone/rooms.h"
int t;
reset (arg){
 if(!present("ant")) {
  for(t=0;t<4;t++){
   move_object(clone_object("players/persephone/monster/ant"), TOB);
  }
 }
 if(!present("woodpecker")){
  move_object(clone_object("players/persephone/monster/bird"), TOB);
 }
 if(!arg){
  set_light(1);
  short_desc="Blueberry Hill";
  long_desc="You are on the top of Blueberry Hill and there appear to be many\n" +
            "blueberry bushes growing around you. Unfortunately you do not have\n" +
            "a very impressive view as there are trees growing all around the hill\n" +
            "A path leads North from here and to the East and the West you think\n" +
            "can see some dells\n";
  dest_dir=({"players/persephone/rooms/bhillm","north",
             "players/persephone/rooms/gnolla","west",
             "players/persephone/rooms/stream1","south",
             "players/persephone/rooms/gnollb","east",
  });
 }
}
realm(){ return "NT";}