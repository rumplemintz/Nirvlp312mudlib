/*                                                                            *
 *      File:             /players/angel/area/mansion/room/boiler_room_10.c   *
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
  short_desc = "Boiler room";
  long_desc =
"This is the central boiler room. It operates in a closed-loop\n\
system, heating the whole mansion. This closed-loop system extracts\n\
heat from steam, the steam changes into water and goes back to the\n\
boiler through the pipes which are visibly sweating where boiling\n\
takes place once again.\n";

  items =
  ({
  "boiler",
  "A large metal box with pipes coming in and out everywhere",
  "pipes",
  "Made of old steel",
  });
  dest_dir =
  ({
    "/players/angel/area/mansion/room/entrance_10",        "up",
    "/players/angel/area/mansion/room/wash_room_02",       "wash",
    "/players/angel/area/mansion/room/billiard_room_10",   "billiard",
    "/players/angel/area/mansion/room/storage_room_10",    "storage",
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
      }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }