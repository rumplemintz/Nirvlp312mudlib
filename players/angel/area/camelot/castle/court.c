/*                                                                    *
 *    File:             /players/angel/area/camelot/castle/court.c    *
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
  "You are in the central court of Lord Hatfield's Castle. This court\n"+
    "is huge. The wide floor of the court is an expanse of quality old\n"+
    "world stone. The bright sunlight shimmers against limestone walls.\n"+
    "The court stretches in all directions. To the east, you see what\n"+
    "appears to be a large guarded armory. To the north is the main\n"+
    "entrance of the castle, to the west appears to be the stables and\n"+
    "to the south leads to the drawbridge.\n");
"    "+HIY+"~ ~"+NORM+"\n\
"+BROWN+"  \n\
\n\
\n\
."+NORM+"\n";

  items =
  ({
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
  });

  dest_dir =
  ({
	"/players/angel/area/camelot/",      "north",
	"/players/angel/area/camelot/",      "east",
	"/players/angel/area/camelot/",    "west",
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
   }

exit(){    if(this_player()) this_player()->clear_fight_area();     }














add_item( ({ "court", "central court"}),
    "This is a large open circular space with a water fountain in the center.\n"+
    "The floors are made of old world stone and the walls are limestone.");
  add_item( ({ "castle"}),
    "It appears to be at least four stories high, all made of limestone.\n");
  add_item( ({ "stone"}),
    "It is sculpted light grey cultured old world stone.\n");
  add_item( ({ "floor"}),
    "It is made of old world stone.\n");
  add_item( ({ "limestone"}),
    "Large rough white boulders.\n");
  add_item( ({"boulders", "boulder"}),
    "A large piece of stone.\n");
  add_item( ({ "walls", "wall"}),
    "The walls are made of limestone.\n");
  add_item( ({ "armory"}),
    "You cannot see in it.\n");
  add_item( ({ "entrance"}),
    "The castle entrance has large wooden double doors with\n"+
    "a cross of the Knight Templar's in the center.\n");
  add_item( ({ "door", "doors"}),
    "Large wooden double doors with a cross of the Knight Templar's in\n"+
    "the center. No knobs or handles are present to open the massive\n"+
    "doors from the outside.\n");
  add_item( ({ "cross"}),
    "A red painted cross with the Seal of the Knights Templar in the center.\n"+
    "The seal has an image of two knights on a single horse.\n");
  add_item( ({ "stables", "stable"}),
    "The door to the stables is closed, but you can see\n"+
    "a couple horses through the window in the door.\n");
  add_item( ({ "window"}),
    "There appears to be a small hole cut out at the top of the door.\n");
  add_item( ({ "drawbridge", "bridge"}),
    "It is made of large wooden planks.\n");
  add_item( ({"plank", "planks"}),
    "Large long pieces of wood.\n");
  add_item( ({"wood"}),
    "A large cut plank from a tree.\n");
  add_item( ({ "knight", "knights"}),
    "A mounted combatant.\n");
  add_item( ({ "seal"}),
    "An image of two knights on a single horse.\n"+
    "It is a symbol used as a means of authentication.\n");
  add_item( ({ "horse", "horses"}),
    "A large hoofed mammal.\n");
  add_item( ({ "sunlight"}),
    "The total spectrum of the electromagnetic radiation given off by the sun.\n");
  add_thing( ({"water fountain", "fountain"}), "A Large Water Fountain",
    "A stately and charming water fountain made of limestone with\n"+
    "intricate details all around the circular base.");
  add_exit(PATH+ "bridge", "south");
  add_exit(PATH+ "armory", "east");
}

void init()
{
  ::init();
  add_action("stop","east");
  add_action("drink","drink");
  add_action("search_me","search");
}

int stop()
{
  if(present("elguard", ETP))
  {
    write("The guard knocks you down and says: You cannot enter Lord Hatfield's armory!\n");
    say(NAME+" is knocked down to the stone floor.\n");
    return 1;
  }
}

int drink(string str)
{
  if(!str)
  {
    write("What would you like to drink?\n");
    return 1;
  }
  if(str == "water" || str == "from fountain")
  {
    write("You take a large gulp of water from the water fountain!\n"); 
    return 1;
  }
}

int search_me(string str)   /*search function players can search any item,*/
{
  if(!str)
  {
    notify_fail("What are you trying to search?\n");
    return 0;
  }
    write("You furiously search the "+str+" but find nothing.\n");
    return 1;
}