/*                                                                            *
 *      File:             /players/angel/area/mansion/bed_room_10.c           *
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
  if( !present("fly", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/fly.c"), this_object());
  if( !present("maggie", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/maggie.c"), this_object());
  if(arg) return;
  set_light(1);
  short_desc = "Bed room";
  long_desc =
"  There is a large sleigh bed, neatly made, two straight-backed\n\
chairs, a washstand, a bureau--without any mirror--and a small table.\n\
There are heavy maroon draperies covering the dormer windows and\n\
pictures of the city all over the walls. Since there are no screens,\n\
the windows are not raised.\n";

  items =
  ({
  "bed",
  "A solid wood bed with a high curved headboard",
  "bureau",
  "A large piece of furniture that has multiple parallel\n\
horizontal drawers stacked one above another",
  "chairs",
  "Many straight backed chair with a cushion seat",
  "draperies",
  "Maroon curtains",
  "pictures",
  "Multiple pictures of the local city",
  "table",
  "A small wood table with one drawer",
  "walls",
  "They are covered with decorative wallpaper",
  "washstand",
  "A small rosewood cabinet supported on three legs.\n\
It is holding a wash basin and water pitcher.",
  "windows",
  "Drafty single pane windows",

  });
  dest_dir =
  ({
  "/players/angel/area/mansion/room/foyer",   "foyer",
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
      }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }