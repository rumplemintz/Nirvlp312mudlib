/*                                                                    *
 *    File:             /players/angel/area/lowthar/room/cam_05.c     *
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
"    "+HIY+"~ Cottage ~"+NORM+"\n\
"+BROWN+"   This is the inside of the blacksmith's old cottage. The boards are\n\
barely stuck together in this one room home. Looking around the wood\n\
floor, iron wood stove, a couple of lumpy straw beds, wood shutters\n\
that act as windows, and a old wood talbe with three chairs can be\n\
seen."+NORM+"\n";
  items =
  ({
	"cottage",
	"",
	"boards",
	"",
	"room",
	"",
	"home",
	"",
	"wood",
	"",
	"floor",
	"",
	"stove",
	"",
	"beds",
	"",
	"shutters",
	"",
	"windows",
	"",
	"table",
	"",
	"chairs",
	"",
  });

  dest_dir =
  ({
    "/players/angel/area/camelot/room/cam_02",  "south",
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
   }

exit(){    if(this_player()) this_player()->clear_fight_area();     }