/*                                                                            *
 *      File:             /players/angel/area/mansion/room/cavern_basin_02.c  *
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

#include <ansi.h>

inherit "room/room.c";

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(0);
  short_desc = HIC+"Cavern Basin River"+NORM;
  long_desc =
"  You have run the boat ashore next to a large corn field in the\n\
country. Off to the right it appears to be an old distressed white\n\
farm house. It appears to be three stories tall with closed black\n\
shutters. When looking around the house you get an eerie feeling.\n\
All around the house there are large corn stalks. As the wind flows\n\
briskly across your face, the corn stalks appear to be bending.\n\
Between the corn there is an open pathway that may lead to town.\n";

items =
  ({
	"boat",
	"An old wood boat with ores",
	"field",
    "A large open area where corn plants are growing",
    "house",
    "It is large with white distressed paint",
    "path",
    "Looks like many people have walked down this dirt path",
    "pathway",
    "Looks like many people have walked down this dirt path",
	"rapids",
	"Fast moving water",
	"shutters",
    "They are made of wood and painted black",
    "stalks",
    "The main stem of a herbaceous corn plant",
	"stream",
	"Long and fast moving water",
  });
  dest_dir =
  ({
  });
}

init() {
  ::init();
  add_action("walk", "walk");
}

status walk(string arg) {
  if (!arg) {
    notify_fail("Walk where?\n");
    return 0;
  }

  if (arg == "opening") {
    notify_fail("walk where?\n");
    return 0;
  }

  if (arg == "path" || arg == "pathway") {
    this_player()->move_player("walk through an open path past the corn stalks#/players/angel/area/mansion/room/clearing.c");
    return 1;
  }

  notify_fail("walk where?\n");
  return 0;
}