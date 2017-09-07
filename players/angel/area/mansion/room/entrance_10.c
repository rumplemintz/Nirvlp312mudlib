/*                                                                            *
 *      File:             /players/angel/area/mansion/room/entrance_10.c      *
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
  short_desc = "Entrance";
  long_desc =
"  This is the main entrance. There are decorative wood stairs that\n\
lead down to the basement and up to the first floor. Metal spiral\n\
hand rails are attached with ordinate brackets to the walls.\n";

  items =
  ({
  "basement",
  "The floor of the building entirely below ground level",
  "brackets",
  "They are made of cast iron painted gold",
  "rails",
  "Twisted in a perfect spiral, like a child's slinky toy",
  "stairs",
  "Dark stained wood with fancy carvings",
  "walls",
  "Decadent flock wallpaper 15 feet high",
  });
  dest_dir =
  ({
    "/players/angel/area/mansion/room/foyer",            "up",
    "/players/angel/area/mansion/room/boiler_room_10",   "down",
    "/players/angel/area/mansion/room/drive",            "out",
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
      }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }