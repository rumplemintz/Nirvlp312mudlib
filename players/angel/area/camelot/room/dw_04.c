/*                                                                    *
 *    File:             /players/angel/area/lowthar/room/dw_01.c      *
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
  short_desc = HIY+"DOURWOOD"+NORM;
  long_desc =
"    "+HIY+"~ DOURWOOD TRAIL ~"+NORM+"\n\
"+HIC+"\n\
                              /\\ \n\
                             /  \\ \n\
                         ^  _|..|_  ^ \n\
                       _|I|  |T.|  |.|_ \n\
                      \\II||--| |--||  / \n\
                       -\\-|-------|-/- "+NORM+"\n\
"+BROWN+"   The forest path begins to open and over the tips of the giant\n\
ancient trees towering high in the sky, the top of Camelot Castle can be seen.\n\
Despite this serene scene, you can't shake the feeling of evil that has over\n\
taken the once prestigious castle."+NORM+"\n";

  items =
  ({
  });

  dest_dir =
  ({
	"/players/angel/area/camelot/room/dw_03",         "southwest",
	"/players/angel/area/camelot/room/cam_castle",    "east",
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
   }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }