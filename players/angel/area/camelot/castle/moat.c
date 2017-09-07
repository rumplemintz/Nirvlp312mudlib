/*                                                                    *
 *    File:             /players/angel/area/camelot/castle/moat.c     *
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
  "    This moat is a deep, broad trench, shallowly filled with water.\n\
It surrounds the Camelot Castle in order to provide it with a\n\
preliminary line of defense. Looking around, part of the walls\n\
appear to be built with large stones.\n";

  items =
  ({
    "stones",
    "The stones do not appear to be level with the wall. It almost\n\
looks as if there was a stair system built into the wall.\n\
Someone might be able to climb them if they had good balance.",
    "castle",
    "Looking up, one can see a massive wall built of limestone.",
    "wall",
    "The walls are made of large limestone boulders.",
    "limestone",
    "Large rough white boulders.",
    "boulders",
    "A large piece of stone.",
    "water",
    "It is a bit murky.",
    "moat",
    "Looking around you see high walls and murky water.",
    "trench",
    "A deep hole.",
    "sunlight",
    "The total spectrum of the electromagnetic radiation given off by the Sun.",
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
    
    add_action("search", "search");
    add_action("climb",  "climb");
    add_action("stop",   "climb");
   }

exit() {    if(this_player()) this_player()->clear_fight_area();     }

stop() {
  if(present("white_gator", environment(this_player())))
   {write("The gator take a large bite into your leg and slams you into the water!\n");
    say(this_player()->query_name()+" is slammed down while trying to escape.\n");
    return 1;
}}

climb(str) {
    int wis;
    wis = 6; /* one out of 6 chance of getting out */
    if(str=="stones" && this_player()->query_attrib("wis") >= 15) wis = 3; /* better chance */
    if(random(wis) == 0) {
    write("You get a foothold and climb out of the moat.\n");
    this_player()->move_player("climb#players/angel/area/camelot/castle/bridge.c");
    return 1;
  }
  else
  {
    write("You fall on your butt, back into the water. Youch!\n"+ 
    "\n"+ 
    "You better watch those Hit Points, that fall really took a toll!\n");
    this_player()->hit_player(2 + random(4));
  }
return 1;
}
/*
search(str)
{
  object scroll;
  if(present("white_gator"))
  {
    write("The alligator is blocking your way!\n");
    return 1;
  }
  if(!str)
  {
    write("Try to search something else!\n");
    return 1;
  }
  if(str=="stones" && found_scroll)
  {
    write("You search the stones and find a pile of old worn scrolls.\n"+
    "You can reach down and pick one up. They must have fallen down long ago!\n");
    MO(PATH+ "scroll",ETP);
    found_scroll=0;
    return 1;
  }
  write("You find nothing.\n");
  return 1;
}*/