/*                                                                            *
 *      File:             /players/angel/area/mansion/kitchen_10.c            *
 *      Function:                                                             *
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
int x;

reset(arg)
{
  ::reset(arg);
  if( !present("chef", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/chef.c"), this_object());
  if( !present("prep cook", this_object()) )
  {
    for(x=0; x<2; x++)
    {
    move_object(clone_object("/players/angel/area/mansion/npc/prep_cook"), this_object());
    }
  }
  if(arg) return;
  set_light(1);
  short_desc = "Kitchen";
  long_desc =
"This is a sleek, professionally designed bespoke kitchen. It has\n\
white quartz counters with stainless steel appliances that are\n\
spotless. The room appears as if it was recently scrubbed down.\n\
It is well equipped as you see utensils on hooks, matching cups,\n\
clean folded tea towels, professional knife block and dried flowers\n\
hang from beams, nothing superfluous here. It seems a bit\n\
minimalistic as you can hear the efficient hum of a refrigerator.\n";
    
  items =
  ({
  "appliances",
  "Stainless steel in appearance",
  "beams",
  "Large structural support that is made from wood",
  "block",
  "A wood butcher block",
  "counters",
  "Made of white quartz",
  "cups",
  "Several white coffee cups that have the square and compass with letter G inlaid",
  "flowers",
  "A regal bouquet dried out",
  "hooks",
  "Filled with utensils",
  "kitchen",
  "Where you cook your food",
  "refrigerator",
  "Stainless steel in appearance",
  "towels",
  "Folded tea towels that have the square and compass with letter G inlaid",
  "utensils",
  "Cooking tools",
 
  
  });
  dest_dir =
  ({
  "/players/angel/area/mansion/room/dining_room_10",   "dining",
  });
}

init(){ 
  ::init();
    this_player()->set_fight_area();
      }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }