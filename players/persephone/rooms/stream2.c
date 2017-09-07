inherit "/players/persephone/closed/thingys.c";
#include "/players/persephone/rooms.h"
reset (arg){
 if(arg) return;
  set_light(1);
  short_desc="Raging Brook";
  long_desc="You are standing in the middle of a raging brook which appears to\n" +
            "disappear just to the south down a hole in the ground. On either side\n" +
            "you see very royal looking trees and some rushes on the West bank of\n" +
            "the brook. To the north the brook continues while to the south you\n" +
            "see a marsh\n" +
            "\n";
  dest_dir=({"players/persephone/rooms/stream1","north",
             "players/persephone/rooms/hall","south",
  });
}
realm() { return "NT"; }