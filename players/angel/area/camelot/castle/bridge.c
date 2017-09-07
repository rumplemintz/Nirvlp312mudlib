/*                                                                    *
 *    File:             /players/angel/area/camelot/castle/bridge.c   *
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
  "    Stepping onto the drawbridge, the magnificent castle court can be seen\n\
to the north. This bridge is made of large oak planks with one fixed\n\
side attached to the wall by large hinges. There are chains attached\n\
to a pulley system as if someone might want to pull the bridge up to\n\
prevent others from crossing the moat below.\n";
/*
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
  });*/
}

init(){
  ::init();
    this_player()->set_fight_area();
   }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

/*
 add_item( ({"drawbridge", "bridge"}),
    "It is made of large wooden planks.\n");
  add_item( ({"court", "central court"}),
    "It can't all be seen, but you can tell\n"+
    "there is a water fountain in the center.");
  add_item( ({"castle"}),
    "Looking up, one can see a massive wall built of limestone.\n");
  add_item( ({"plank", "planks"}),
    "Large long pieces of wood.\n");
  add_item( ({"wood"}),
    "A large cut plank from a tree.\n");
  add_item( ({"wall", "walls"}),
    "The walls are made of large limestone boulders.\n");
  add_item( ({"limestone"}),
    "Large rough white boulders.\n");
  add_item( ({"boulders", "boulder"}),
    "A large piece of stone.\n");
  add_item( ({"hinges", "hinge"}),
    "They look to be made out of steel.\n");
  add_item( ({"chains", "chain"}),
    "They are a heavy duty metal links.\n");
  add_item( ({"pulley"}),
    "A wheel and axle for the chains to move over.\n");
  add_item( ({"wheel", "axle"}),
    "The wheel and axle is a simple machine to lift items easier.\n");
  add_item( ({"machine"}),
    "It has a wheel and axle that chains move over.\n");
  add_item( ({"moat"}),
    "It is a deep, broad trench.\n"+
    "If you could jump down there, you could cool down quick!\n");
  add_item( ({"trench"}),
    "A deep hole.\n");
  add_item( ({"hole"}),
    "A large opening in the ground.\n");
  add_item( ({"opening"}),
    "A deep hole.\n");
  add_item( ({"ground"}),
    "There is a deep hole there.\n");
  add_exit(PATH+ "court", "north");
}

void init()
{
  ::init();
  add_action("north", "north");
  add_action("jump",  "jump");
}

north()
{
  if(!present("scroll_of_invite", TP))
  {
    tell_object(TP, "Guard shouts: You must have an invitation to pass!\n");
    return 1;
  }
  TP->MP("north#players/angel/area/camelot/court.c");
  return 1;
}

jump(str)
{
  if(!str)
  {
    write("Where would you like to jump?\n");
    return 1;
  }
  if(str == "into moat" || str == "moat")
  {
    write("You jump into the moat and find it quite invigorating!\n");
    TP->MP("north#players/angel/area/camelot/moat.c");
    return 1;
  }
}*/