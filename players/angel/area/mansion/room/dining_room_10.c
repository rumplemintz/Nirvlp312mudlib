/*                                                                            *
 *      File:             /players/angel/area/mansion/room/dining_room_10.c   *
 *      Function:                                                             *
 *      Author(s):        Angel@Nirvana                                       *
 *      Copyright:        Copyright (c) 2017 Angel                            *
 *                                All Rights Reserved.                        *
 *      Source:           02/17/17                                            *
 *      Notes:                                                                *
 *                                                                            *
 *                                                                            *
 *      Change History:                                                       *
 */

#include <ansi.h>

inherit "room/room";

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(1);
  short_desc = "Dining room";
  long_desc =
"The dining room is exquisite. The walls are covered with a\n\
shimmering gold paper and in the middle of the ceiling above the\n\
carved oak table is a candelabra. Down the center of the table is\n\
a runner with a Celtic design woven in gold and green into the fabric\n\
itself. At the end of the table are floor to ceiling French doors,\n\
left slightly ajar to let in the scented summer air. The polished\n\
silver cutlery is heavy to the hand and shone brightly in the early\n\
evening light. At each place stands a tall empty wine glass and\n\
beautifully folded napkins to match the runner. All that is missing\n\
is the food and the guests.\n";
  items =
  ({
  "candelabra",
  "Eloquent candle holder in the shape of flowers",
  "cutlery",
  "Long sharp blades, narrow point, excellent for rough chopping",
  "doors",
  "Tall french door with single pane glass",
  "glass",
  "Tall with a broad bowl, and is designed for full bodied red wines",
  "napkins",
  "Embellished wildflower design",
  "paper",
  "Gold wall paper with delicate flowers",
  "rails",
  "Twisted in a perfect spiral, like a child's slinky toy",
  "runner",
  "Embellished Wildflower design",
  "table",
  "Solid wood with carvings around the edges",
  });
  dest_dir =
  ({
    "/players/angel/area/mansion/room/living_room_10",  "living",
    "/players/angel/area/mansion/room/kitchen_10",      "kitchen",
  });
}

init(){ 
  ::init();
    this_player()->set_fight_area();
      }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }