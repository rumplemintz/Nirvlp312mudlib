/*                                                                    *
 *    File:             /players/angel/area/camelot/room/cam_01.c     *
 *    Function:         room                                          *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           4/15/17                                       *
 *    Notes:                                                          *
 *                                                                    *
 *                                                                    *
 *    Change History:                                                 *
 */

#include "/sys/lib.h"
 
#include <ansi.h>

inherit "room/room";

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(1);
  short_desc = HIY+"Village of Camelot"+NORM;
  long_desc =
"    "+HIY+"~ Village road ~"+NORM+"\n\
"+BROWN+"    This is a small village composed of six or seven buildings\n\
and to the east of the village you see a small farm, however,\n\
it's the blacksmith shop to the north which attracts your\n\
attention."+NORM+"\n";

  items =
  ({
    "village",
    "",
    "buildings",
    "",
    "farm",
    "",
    "blacksmith",
    "",
    "shop",
    "",
  });

  dest_dir =
  ({
/*	"/players/angel/area/camelot/room/cam_04",      "north",
	"/players/angel/area/camelot/room/cam_02",      "east",*/
	"/players/angel/area/camelot/room/entrance",    "west",
  });
}

init(){
  ::init();
  add_action("north", "north");
  add_action("east",  "east");
    this_player()->set_fight_area();
   }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

north() {
  if ( this_player()->query_level() < 30) {
    write("The village has not yet been cleared.\n");
    say(call_other(this_player(), "query_name", 0) +
      " cannot pass the bolckade.\n");
    return 1;
  }
  write("You wiggle through the force field...\n");
  this_player()->move_player("you walk along the driveway to the house entrance#/players/angel/area/camelot/room/cam_04.c");
  return 1;
}

east() {
  if ( this_player()->query_level() < 30) {
    write("The village has not yet been cleared.\n");
    say(call_other(this_player(), "query_name", 0) +
      " cannot pass the bolckade.\n");
    return 1;
  }
  write("You wiggle through the force field...\n");
  this_player()->move_player("you walk along the driveway to the house entrance#/players/angel/area/camelot/room/cam_02.c");
  return 1;
}