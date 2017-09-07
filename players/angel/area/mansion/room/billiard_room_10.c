/*                                                                            *
 *      File:             /players/angel/area/mansion/billiard_room_10.c      *
 *      Function:         Room                                                *
 *      Author(s):        Angel@Nirvana                                       *
 *      Copyright:        Copyright (c) 2017 Angel                            *
 *                                All Rights Reserved.                        *
 *      Source:           02/17/17                                            *
 *      Notes:            Passageway to the cavern for Quest                  *
 *                                                                            *
 *                                                                            *
 *      Change History:                                                       *
 */

#include <ansi.h>

inherit "room/room";

int saber;

int enter;

reset(arg)
{
  ::reset(arg);
  if( !present("ashley", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/ashley.c"), this_object());
  if( !present("beatty", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/beatty.c"), this_object());
  if( !present("hiatt", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/hiatt.c"), this_object());
  if( !present("mcclurd", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/mcclurd.c"), this_object());
  if( !present("meyers", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/meyers.c"), this_object());
  if( !present("morgan", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/morgan.c"), this_object());
  if( !present("mccoy", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/mccoy.c"), this_object());
  if(arg) return;
  set_light(1);
  short_desc = "Billiard room";
  long_desc =
"    The billiard room or rather the pool hall has looked exactly\n\
the same for a century. Cinder-block walls painted black on three\n\
sides of the room. Shelves are filled with trophies and plaques all\n\
over the walls. The red felt pool tables are at the center of the\n\
room. Poker tables are scattered around the fringe. Low track\n\
lighting is curving across the ceiling with a congested smell of\n\
cigar smoke clogging the air.\n";

  items =
  ({
  "ceiling",
  "It has many lights hanging all around",
  "cinder-block",
  "Large bricks",
  "lighting",
  "Soft light hanging on bars",
  "plaques",
  "Various reward plaques",
  "shelves",
  "There are many trophies and Masonic memorabilia\n\
filling the shelves. There appears to be an\n\
'empty shelf' out of 'place'",
  "shelf",
  "Looks like a display item was moved from the shelf",
  "poker tables",
  "They are round soft fabric tables setup to play poker",
  "tables",
  "There are many rectangular soft fabric tables setup to play pool",
  "trophies",
  "A large variety of awards from Mayor Ray's life starting as a young man",
  "walls",
  "Three walls are made of large bricks while one side is wood paneling",

});
  dest_dir =
  ({
    "/players/angel/area/mansion/room/boiler_room_10",   "boiler",
  });
}

init(){ 
  ::init();
    add_action("open","open");
    add_action("place","place");
    add_action("place","hang");
    add_action("enter","enter");
    this_player()->set_fight_area();
      }

open(str) {
  if(!str) { write("Open what?\n"); return 1;}
  if(str=="door") {
    write("There aren't any additional visible doorways.\n");
    return 1;
  }
  write("Open what?\n");
  return 1;
}

place(str) {
  if(!str) {write("Place what?\n");return 1;}
  if(str!="saber on shelf") { write("Place what?\n"); return 1; }
  if(present("saber",this_player())) {
    destruct(present("saber",this_player()));
    write("You place the saber with its scabbard on the shelf.\n");
    saber=1;
    call_out("enter_passage",1);
    return 1;
}}

enter_passage() {
	if(saber) {
	 tell_room(this_object(),
"A large section of the wood paneling wall slides open into a passageway.\n"
    );
  }
}

enter(str) {
    if(saber) {
      this_player()->move_player("enter#"+"/players/angel/area/mansion/room/passageway_01");
      tell_room(this_object(),
"The wood paneling closes the passageway beind you.\n"
);
      return 1;
  }
}

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }