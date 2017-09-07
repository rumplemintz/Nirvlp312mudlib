/*                                                                            *
 *      File:             /players/angel/area/mansion/room/storage_room_10.c  *
 *      Function:         Room                                                *
 *      Author(s):        Angel@Nirvana                                       *
 *      Copyright:        Copyright (c) 2017 Angel                            *
 *                                All Rights Reserved.                        *
 *      Source:           02/17/17                                            *
 *      Notes:            Hirams key unlocks the door to the next clue        *
 *                                                                            *
 *                                                                            *
 *      Change History:                                                       *
 */

#include <ansi.h>

inherit "room/room";

int unlocked;

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(1);
  short_desc = "Storage room";
  long_desc =
"  This is a general storage room. It appears that it is full of\n\
items that once were in the main house. There are momentos, family\n\
photographs, earthy furniture, equipment, shelves, walnut book\n\
shelves, glass fronted book shelves, leather bound books with many\n\
odds and ends. A rough assortment of furniture collected over time.\n\
Behind the stacked furniture it appears there might be another door.\n";

  items =
  ({
  "books",
  "They are old abd leather bound",
  "door",
  "A heavy wood door with a skelton lock",
  "equipment",
  "House hold cleaning equipment",
  "furniture",
  "Many old broken chairs",
  "photographs",
  "Large black and white photos in metal frames",
  "shelves",
  "Solid wood with marks where many books once were",
  });
  dest_dir =
  ({
    "/players/angel/area/mansion/room/boiler_room_10",   "boiler",
  });
}

init(){ 
  ::init();
    add_action("unlock","unlock");
    add_action("enter","enter");
    this_player()->set_fight_area();
}

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }

unlock(str)
{ object door;
  if(str!="door") { write("Open what?\n");
    return 1; }
    if(unlocked) { write("The door is already open!\n");
      return 1;}
      door=present("hiram's key",this_player());
      if(!door) { write("The door must have the correct key to be opened!!!\n");
        return 1; }
        unlocked=1;
        {write("As you unlock the door you hear a loud click.\n");
        items = ({ "door", "An unlocked door, maybe you could enter it"}); 
          return 1;}
}
enter(str)
{   if(str!="door") { write("Enter what?\n");
      return 1; }
      if(!unlocked) { write("The door must have the correct key to be opened!!!\n");
        return 1; }
        write("You enter the storage room and see what looks like a mason shrine.\n");
        this_player()->move_player("enter#"+"/players/angel/area/mansion/room/storage_room_11");
        return 1;
}