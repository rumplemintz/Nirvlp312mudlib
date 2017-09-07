/*                                                                            *
 *      File:             /players/angel/area/mansion/room/storage_room_11.c  *
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

int is_here;

reset(arg)
{
  ::reset(arg);
  if( !present("mason", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/entered_apprentice_01.c"), this_object());
  is_here=1;
  if(arg) return;
  set_light(0);
  short_desc = "Masonic shrine";
  long_desc =
"This room appears to be a Masonic shrine filled with many mason\n\
artifacts. As you squint in the dim light you can see items on\n\
display. There are many different rings, aprons, pennants, hat\n\
pins, medallions, collar chains, swords, sabers and books sitting\n\
on the display cases among other items.\n";

  items =
  ({
  "aprons",
  "Masonic Blue Lodge Mason Aprons, made of white imitation leather.\n\
They have a royal blue plain ribbon border. Each has a different\n\
symbol based on rank",
  "artfacts",
  "Many object made by a human being",
  "books",
  "They are old and leather bound",  
  "chains",
  "Various gold, silver and plated chains",
  "cases",
  "Wood casses with glass shelves to disply items,\n\
there is a sign that reads 'Do Not Touch'",
  "medallions",
  "Various Gold Plated Masonic Brotherhood of Man, Square and Compass",
  "pennants",
  "Stainless steel with various mason inner designs",
  "pins",
  "Various Giant Square and Compass with G and all seeing eye",
  "rings",
  "Dozens antiqued enamel carved with Freemasonry Icon",
  "swords",
  "Many styles and designs mostly used for rituals",
  "sabers",
  "Many styles and designs mostly used for rituals",
  });
  dest_dir =
  ({
    "/players/angel/area/mansion/room/storage_room_10",   "storage",
  });
}

init(){
  ::init();
    add_action("search","search");
    this_player()->set_fight_area();
      }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }

search(str) {
  object saber;
  if(present("mason")) {
    write("You won't be going through that while I am here!\n");
    return 1;
  }

  if(!str) {
    write("Search what?\n");
    return 1;
  }
  if(str=="shelf" && is_here) {
    write("You find a masonic saber.\n");
    saber=clone_object("/players/angel/area/mansion/obj/masonic_saber_01");
    move_object(saber,this_player());
    is_here=0;
    return 1;
  }
  write("You find nothing.\n");
  return 1;
}