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
"+BROWN+"  You are advancing along a narrow path that runs deep into the forest of\n\
Dourwood's. Giant, ancient trees tower over you to either side, and sweet\n\
songbirds sing in their lofty branches. However, despite this serene scene,\n\
you can't shake the feeling that you're being watched."+NORM+"\n";

  items =
  ({
  });

  dest_dir =
  ({
	"/players/angel/area/camelot/room/dw_02",    "southwest",
	"/players/angel/area/camelot/room/dw_04",    "northeast",
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
   }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }