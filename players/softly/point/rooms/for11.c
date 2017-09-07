#include "/players/softly/closed/define.h"
#include "/players/softly/closed/ansi.h"
inherit "/players/vertebraker/closed/std/room";

  reset(arg) {
  if(!present("bird")) 
  move_object(clone_object("players/softly/point/mobs/bird"),this_object());
  if(arg) return;

set_light(1);

short_desc = "Grassy Beach";
long_desc ="  Sand interspersed with sea grass flows between\n"+
           "the westward forest and the vast sea to the east.\n"+
           "The mist is very warm and dense.  A few remnants\n"+
           "of stubby trees dots the sand.  Far to the north\n"+
           "the top of a lighthouse can be seen.\n";

items = ({
  "sand", "The grey brown earth gives way to pale grey sand,\n"+
          "which stretches to the water's edge",
  "sea","The blue-green sea stretches as far as the eye can see",
  "mist","The air is white with mist, which hangs heavily over\n"+
         "the sand and the surface of the sea,  It is warm and\n"+
         "dense, surrounding everything like a cloak",
  "trees","Remnants of trees, bare from years of being pounded\n"+
          "by wind and water, dot the sand",
  "grass","Sharp blades of bright green sea grasses sparsely\n"+
          "populate the beach",
  "lighthouse","Through the mist the top of a tall red and white\n"+
               "striped lighthouse can be seen",
  "forest","The forest has many pine and oak trees.  It seems\n"+
           "very old",
  });

dest_dir = ({
  "/players/softly/point/rooms/for10.c","west",
  "/players/softly/point/rooms/for16.c","northeast",
  "/players/softly/point/rooms/for12.c","southwest",
  });
}



