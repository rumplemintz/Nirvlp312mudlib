/*                                                                            *
 *      File:             /players/angel/area/mansion/room/office_10.c        *
 *      Function:         Room                                                *
 *      Author(s):        Angel@Nirvana                                       *
 *      Copyright:        Copyright (c) 2017 Angel                            *
 *                                All Rights Reserved.                        *
 *      Source:           02/17/17                                            *
 *      Notes:            Here is where the Masonic Quest starts              *
 *                                                                            *
 *                                                                            *
 *      Change History:                                                       *
 */

#include <ansi.h>

inherit "room/room";

int is_here;

reset(arg)
{
  ::reset(arg);
  if( !present("mayor", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/mayor_ray.c"), this_object());
  is_here=1;
  if(arg) return;
  set_light(1);
  short_desc = "Office";
  long_desc =
"   This is Mayor Bob Ray's office. The cities business along with\n\
Mayor's personal company's business occurs here on a daily basis.\n\
The room has 15 feet high ceilings with elegant tapestry around the\n\
room. The room has thick wood trim that add to the elegance of the\n\
room. There is a brick fireplace on the south side of the room. The\n\
area is filled with dark oak furniture and a beautiful mahogany desk.\n\
Stairs leading up can be seen.\n";

  items =
  ({
	"apron",
	"A white leather apron with the marking, Knight Commander",
	"ceilings",
	"It has a white textured surface",
	"chair",
	"A dark leather chair with an apron draped over it",
	"desk",
    "it is made of decorative mahogany with a beautiful leather chair",
    "fireplace",
    "A brick fireplace with a ornate wood mantle",
    "furniture",
    "It all appears to have been hand made by a craftsman",
    "stairs",
    "Large wood stairs that lead to another floor",
    "tapestry",
    "Heavy maroon curtains",
    "trim",
    "12 inch high baseboard with a routed edge",
  });
  dest_dir =
  ({
    "/players/angel/area/mansion/room/foyer",            "foyer",
    "/players/angel/area/mansion/room/living_room_10",   "living",
  });
}

init(){
  ::init();
    add_action("up","up");
    add_action("stairs","stairs");
    add_action("search","search");
    this_player()->set_fight_area();
      }
      
exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }

  up(str){
  write("The stairs are blocked.\n");
  return 1;
  }

  stairs(str){
  write("The stairs are blocked.\n");
  return 1;
  }

search(str) {
  object key;
  if(present("mayor")) {
    write("Get out of my desk before I have you arrested!\n");
    return 1;
  }

  if(!str) {
    write("Search what?\n");
    return 1;
  }
  if(str=="desk" && is_here) {
    write("You find a old skelton key.\n");
    key=clone_object("/players/angel/area/mansion/obj/hirams_key");
    move_object(key,this_player());
    is_here=0;
    return 1;
  }
  write("You find nothing.\n");
  return 1;
  }