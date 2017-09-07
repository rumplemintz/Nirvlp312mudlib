/*                                                                    *
 *    File:             /players/angel/area/camelot/castle/armory.c   *
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
"[30;1mThis room is dimly lit from a set of flickering torches. Between\n"+
    "the torches, shields adorn the walls, all polished to a bright\n"+
    "gleam from what sunlight gets through a tiny window in the east\n"+
    "wall. A suit of armor stands attentively on a pedestal in the\n"+
    "corner of the room. There is a plaque on the front of the pedestal.\n"+
    "In the center of the room there are many wooden crates that are\n"+
    "well secured.[2;37;0m\n");
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

add_item( ({"torches", "torch"}),
    "Made of ringed steel and wooden stakes, it\n"+
    "seems to be able to burn quite awhile!");
  add_item( ({"shields", "shield"}),
    "They are all made of steel with a painted gold colored cross in\n"+
    "the center. The shields seem to be well attached to the wall.");
  add_item( ({"walls", "wall"}),
    "A simple wall made of limestone.\n");
  add_item( ({"limestone"}),
    "Large rough white boulders.\n");
  add_item( ({"boulders", "boulder"}),
    "A large piece of stone.\n");
  add_item( ({"shadow", "shadows"}),
    "They are too dark, you might try to 'search' in them.\n");
  add_item( ({"sunlight"}),
    "The total spectrum of the electromagnetic radiation given off by the sun.\n");
  add_item( ({"window"}),
    "It looks like a couple bricks were left out of the wall.\n");
  add_item( ({"armor"}),
    "A full plated suit of armor. It is authentic armor worn by Sir Galahad.\n");
  add_item( ({"pedestal"}),
    "A large stone pedestal that stands about waist height.\n"+
    "The suit of armor is attached.\n");
  add_item( ({"crates", "crate"}),
    "Large wooden boxes that appear to be closed tight.\n");
  add_item( ({ "plaque"}),
    "You should try to read it.\n");
  add_item( ({ "box", "boxes"}),
    "Simple square wood objects.\n");
  add_item( ({"plank", "planks"}),
    "Large long pieces of wood.\n");
  add_item( ({"wood"}),
    "A large cut plank from a tree.\n");
  add_thing( (({"knights pedestal", "pedestal", "suit"})), "[30;1mA Suit on a Pedestal[2;37;0m",
    "A full plated suit of armor. It is authentic armor worn by Sir Galahad.\n"+
    "This medieval armor is highly prized for incredible detailing and\n"+
    "superior style! The steel armor was formed by hand hammering on\n"+
    "wooden stumps and then hand worked on the steel anvil. The pieces\n"+
    "were then joined together with hand placed rivets and straps that\n"+
    "allow the position of the arms and legs to move.\n");
  add_read( ({ "plaque", "a plaque"}), "Authentic armor worn by Sir Galahad.\n"+
    "A Knight of the Round Table.");
  add_exit(PATH+ "court", "west");
}

void init()
{
  ::init();
  add_action("search","search");
}

status search(string str)
{
  object shield;
  if(present("knight"))
  {
    write("You can't search anything while the Dark Knight stands before you!\n");
    return 1;
  }
  if(!str)
  {
    write("Search what?\n");
    return 1;
  }
  if(str=="shadows" && is_here)
  {
    write("You search in the shadows and find an old shield.\n");
    shield=CO(PATH+ "oshield");
    MO(shield,TP);
    is_here=0;
    return 1;
  }
  write("You find nothing.\n");
  return 1;
}