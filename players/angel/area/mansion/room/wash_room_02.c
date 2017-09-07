/*                                                                            *
 *      File:             /players/angel/area/mansion/room/wash_room_02.c     *
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

inherit "room/room";

reset(arg)
{
  ::reset(arg);
  if( !present("maid", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/maid.c"), this_object());
  if(arg) return;
  set_light(1);
  short_desc = "Wash room";
  long_desc =
"This room is ideal for washing laundry. There are laundry hampers\n\
adjacent to the washer and dryer area for family members to toss\n\
soiled clothes in throughout the week. An area for hanging clothes\n\
and a countertop with a work surface that is adjacent to the dryer for\n\
efficiency. You can see the ironing board with plenty of countertop\n\
work space. The storage cabinets are on the opposite side of the room.\n";

  items =
  ({
  "cabinets",
  "Made of solid wood filled with household objects for laundry",
  "clothes",
  "Many large piles",
  "countertop",
  "Made of black diamond marble",
  "dryer",
  "Whirlpool 7.4 cu ft Stackable Gas Dryer with a Steam Cycle",
  "hampers",
  "Large baskets with a lid used for laundry",
  "washer",
  "A Whirlpool Load and Go Front-Load Washer Steam Cycle in Chrome",
  "iron",
  "looks like it is a Professional 1715W Iron by Rowenta",
  "ironing board",
  "A fold down board with a padded cover",

  });
  set_call_out( "washer_effect", 5, 20 );
  dest_dir =
  ({
    "/players/angel/area/mansion/room/boiler_room_10",  "boiler",
  });
}

washer_effect() {
  switch( random(5) ) {
    case 0:
      tell_room(this_object(), "From the corner of your eye you see the shadows of men passing by.\n");
      break;
    case 1:
      tell_room(this_object(), "You hear clothes softly tumbling over and over.\n");
      break;
    case 2:
      tell_room(this_object(), "You hear what sounds like moving water.\n");
      break;
    case 3:
      tell_room(this_object(), "You hear a creak in the ceiling as if someone is walking above you.\n");
      break;
    default:
      tell_room(this_object(), "You hear many deep voices in the direction of the billiard room.\n");
      break;
  }

  call_out(call_out_func, call_out_int + random( call_out_int_rand ) );
}

init(){ 
  ::init();
    this_player()->set_fight_area();
      }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }