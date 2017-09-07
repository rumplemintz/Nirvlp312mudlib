/*                                                                    *
 *    File:             /players/angel/area/camelot/castle/dungeon.c  *
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
  short_desc = HIY+"Camelot Castle"+NORM;
  long_desc =
"    "+HIY+"~ ~"+NORM+"\n\
"+BROWN+"  \n\
\n\
\n\
."+NORM+"\n";

  items =
  ({
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
  });

  dest_dir =
  ({
	"/players/angel/area/camelot/",      "north",
	"/players/angel/area/camelot/",      "east",
	"/players/angel/area/camelot/",    "west",
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
   }

exit(){    if(this_player()) this_player()->clear_fight_area();     }