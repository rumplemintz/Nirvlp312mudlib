/*                                                                    *
 *    File:             /players/angel/area/camelot/room/cam_02.c     *
 *    Function:         room                                          *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           4/15/16                                       *
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
"    "+HIY+"~ Market ~"+NORM+"\n\
"+BROWN+"    This is an open market that lines the street. Normaly you would \n\
be able to find every thing that you want to buy but, it is too early\n\
for any merchants to be open. "+NORM+"\n";

  items =
  ({
  });

  dest_dir =
  ({
	"/players/angel/area/camelot/room/cam_05",   "north",
	"/players/angel/area/camelot/room/cam_06",   "south",
	"/players/angel/area/camelot/room/cam_03",   "east",
	"/players/angel/area/camelot/room/cam_01",   "west",
    
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
   }

exit(){    if(this_player()) this_player()->clear_fight_area();     }