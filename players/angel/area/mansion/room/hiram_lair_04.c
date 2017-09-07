/*                                                                    *
 *    File:         /players/angel/area/mansion/room/hiram_lair_04.c  *
 *    Function:         room                                          *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           02/7/17                                       *
 *    Notes:                                                          *
 *                                                                    *
 *                                                                    *
 *    Change History:                                                 *
 */
#include <ansi.h>

inherit "room/room.c";

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(0);
  short_desc = HIC+"Cavern"+NORM;
  long_desc =
" This is a dark cavern. It appears to be very deep. It is bricked\n\
like an old large water well. There are some old wood stair that\n\
spiral around the cavern and a platform controlled by a rope around\n\
a swivel that is bolted into a wood rafter high above. It is\n\
impossible to go up from here!\n";

items =
  ({
    "bricks",
    "They are large red brick that appear to be well aged",
    "leavers",
    "They are switches connected to the pulley",
    "well",
    "A large water well made over 100 years ago",
    "stairs",
    "They are maid of wood bolted to the circular well.\n\
The wood is rotten!",
    "platform",
    "This is a small platform that uses a rope to lower and raise it in the well",
    "pulley",
    "It appears to be connected with rope that can be 'released' and 'pull'ed.",
    "rope",
    "It appears the rope can be 'released' and 'pull'ed.",    
    "swivel",
    "A stainless steal roller to help move the platform along",
   });

}

init() {
  ::init();
    add_action("release"); add_verb ("release");
}

release(str) {
	say(capitalize(this_player()->query_name())+
    " releases the rope and the scafold drops down 50 yards.\n");
    this_player()->move_player(
    " releases the rope and drops futher into the cavern#/players/angel/area/mansion/room/cavern_basin_01");
    say(capitalize(this_player()->query_name())+" arrives.\n");
    return 1;
}