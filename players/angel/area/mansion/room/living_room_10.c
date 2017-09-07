/*                                                                            *
 *      File:             /players/angel/area/mansion/room/living_room_10.c   *
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
  short_desc = "Living room";
  long_desc =
"  The room is like a perfect magazine cover. You're afraid to sit in\n\
case you wrinkle the fabric or stain it with something you don't even\n\
know is on your pants. The couch is cream, inlaid with fine green\n\
silk leaves embroidered so delicately that they might have landed\n\
there in spring and just sunk in. One might think they took hundreds\n\
of hours to sew. The white curtains are made of linen, white linen,\n\
the kind of white that is untouched by hands and devoid of dust. A\n\
cursory look to the right shows almost hidden cords used to open and\n\
close the curtains. The only other furniture are chairs arranged\n\
around the bespoke fireplace which leaps with a gas flame. The black\n\
and white photographs are casual family snaps arranged to look like\n\
it has been done by a professional. The floor is a high polished\n\
wood, dark and free of either dust or clutter.\n";

  items =
  ({
  "chairs",
  "High back wood chair with a cushion seat",
  "cords",
  "A lift cord allowing the blinds to be pulled up",
  "couch",
  "Cream with inlaid with fine green silk leaves",
  "curtains",
  "Made of white linen",
  "fireplace",
  "Wood mantle that is highly crafted",
  "flame",
  "The red and yellow visible gaseous part of the fire",
  "floor",
  "They are high polished wood",
  "linen",
  "A fabric that the curtains are made out of",
  "photos",
  "Black and white family photos",
  "photographs",
  "Large black and white photos in metal frames",
  "snaps",
  "Black and white family photos",
  "wood",
   "A dark color material covering the floor",
  });
  dest_dir =
  ({
    "/players/angel/area/mansion/room/foyer",            "foyer",
    "/players/angel/area/mansion/room/office_10",        "office",
    "/players/angel/area/mansion/room/dining_room_10",   "dining",
  });
}

init(){ 
  ::init();
    this_player()->set_fight_area();
      }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }