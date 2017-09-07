/*                                                                            *
 *      File:             /players/angel/area/mansion/room/foyer.c            *
 *      Function:         Room                                                *
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
  short_desc = "Foyer";
  long_desc =
"   From the foyer you can see into many different rooms. To the\n\
west is the bedroom, to the north is the living room and to the east\n\
is the office with more stairs going up. The walls are filled with\n\
black and white pictures. The large open room feels massive with a\n\
grand chandelier hanging down.\n";

  items =
  ({
  "chandelier",
  "Decorative hanging light with branches for several light bulbs",
  "pictures",
  "A photograph",
  "rails",
  "Twisted in a perfect spiral, like a child's slinky toy",
  "stairs",
  "Dark stained wood with fancy carvings",
  "walls",
  "Decadent flock wallpaper 15 feet high",
  });
  dest_dir =
  ({
    "/players/angel/area/mansion/room/entrance_10",      "down",
    "/players/angel/area/mansion/room/office_10",        "office",
    "/players/angel/area/mansion/room/living_room_10",   "living",
    "/players/angel/area/mansion/room/bed_room_10",      "bed",
  });
}

init(){ 
  ::init();
    this_player()->set_fight_area();
      }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }