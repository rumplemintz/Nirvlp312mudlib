/*                                                                            *
 *      File:             /players/angel/area/mansion/drive.c                 *
 *      Function:                                                             *
 *      Author(s):        Angel@Nirvana                                       *
 *      Copyright:        Copyright (c) 2017 Angel                            *
 *                                All Rights Reserved.                        *
 *      Source:           02/17/17                                            *
 *      Notes:            Entrance to Mansion                                 *
 *                                                                            *
 *                                                                            *
 *      Change History:                                                       *
 */

#include <ansi.h>

inherit "room/room";

int C;

reset(arg)
{
  ::reset(arg);
  if( !present("gardener", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/gardener.c"), this_object());
  if(arg) return;
  set_light(1);
  short_desc = "Drive Way";
  long_desc =
"  This circle driveway curves through the well manicured south\n\
lawn. As you look up at the mansion you notice it's massive size.\n\
Looking at the gigantic wood doors you feel overwhelmed with its\n\
majestic aura.\n";

  items =
  ({
  "doors",
  "They seem strong and secure with unlimited flexibility",
  "drive",
  "A concrete road",
  "driveway",
  "A concrete road",
  "lawn",
  "It's a well manicured luscious green grass",
  "mansion",
  "A three story brick home",
  });
  dest_dir =
  ({
    "/players/angel/area/mansion/room/entrance_10",           "enter",
    "/players/angel/area/mansion/room/mansion_01",            "curb",
  });
}

init(){
  ::init();

    this_player()->set_fight_area();
    add_action("search", "search");
}

    search(str) {
if(!str) { write("Try searching the ground.\n"); return 1; }
if(str == "ground" && C == 1) {
  write("You search the ground and find a trowl that seems out of place.\n");
  move_object(clone_object("players/angel/area/mansion/obj/trowl.c"),this_player());
  C = 0;
  return 1; }
else {
  write("You search furiously and find nothing.\n");
  return 1; }
}

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }