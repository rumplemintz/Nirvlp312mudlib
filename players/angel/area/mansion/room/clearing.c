/*                                                                            *
 *      File:             /players/angel/area/mansion/room/clearing.c         *
 *      Function:         Room                                                *
 *      Author(s):        Angel@Nirvana                                       *
 *      Copyright:        Copyright (c) 2017 Angel                            *
 *                                All Rights Reserved.                        *
 *      Source:           02/17/17                                            *
 *      Notes:            Connects the quest area back to the towm            *
 *                                                                            *
 *                                                                            *
 *      Change History:                                                       *
 */

#include <ansi.h>

inherit "room/room";

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(1);
  short_desc = "A Clearing";
  long_desc =
"  To the north you can see an old distressed white farm house with\n\
corn fields all around. To the south the dirt path is open going\n\
towards a small town.\n";

  items =
  ({
  "farm",
  "They appears to be growing corn",
  "field",
  "A large open area where corn plants are growing",
  "house",
  "It is old and worn",
  "path",
  "A dirt walkway",
  
  });
  dest_dir =
  ({
  "/players/angel/area/town/room/10th_country",  "south",
  });
}