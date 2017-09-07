/*                                                                    *
 *    File:             /players/angel/area/lowthar/room/cam_04.c     *
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
"    "+HIY+"~ Blacksmith's yard ~"+NORM+"\n\
"+BROWN+"    This yard was once full of all the blacksmith's supplies he needed\n\
to create armors and swords for the kingdom. It appears it recently\n\
has been emptied.  Now every once in awhile you may see a young boy\n\
scouring the area for left over metal to sell."+NORM+"\n";

  items =
  ({
  });

  dest_dir =
  ({
	"/players/angel/area/camelot/room/cam_01",   "south",
	"/players/angel/area/camelot/room/cam_07",   "west",
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
   }

exit(){    if(this_player()) this_player()->clear_fight_area();     }