/*                                                                            *
 *      File:             /players/angel/area/mansion/room/cavern_basin_01.c  *
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

#include "/sys/lib.h"

#include <ansi.h>

inherit "room/room.c";

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(0);
  short_desc = HIC+"Cavern Basin"+NORM;
  long_desc =
" It appears you are amidst a boat. Looking out of the boat it\n\
appears this area is at the end of a low river stream. The stream\n\
appears to flow down hill fast with a couple of heavy rapid's.\n";

items =
  ({
	"boat",
	"An old wood boat with ores, one might want to row the boat",
	"rapids",
	"Fast moving water",
	"stream",
	"Long and fast moving water",
	
   });
  dest_dir =
  ({
  });
}

init() {
  ::init();
  add_action("dial", "row");
}

dial(str) {
	"/players/angel/closed/displays.c"->display_file("/players/angel/area/mansion/obj/river");
    this_player()->move_player(
    " down the stream#/players/angel/area/mansion/room/cavern_basin_02.c");
    say(capitalize(this_player()->query_name())+" arrives.\n");
    return 1;
}