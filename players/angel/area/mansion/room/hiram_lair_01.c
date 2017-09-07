/*                                                                    *
 *    File:         /players/angel/area/mansion/room/hiram_lair_01.c  *
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
  if( !present("hiram", this_object()) )
    move_object(clone_object("/players/angel/area/mansion/npc/hiram.c"), this_object());
  if(arg) return;
  set_light(0);
  short_desc = HIC+"Hiram Abif's Lair"+NORM;
  long_desc =
" This is the Lair of Master Mason Hiram Abif. Your disoriented eyes\n\
adjust to the darkness and hear a faint dripping sound that seems to\n\
echo away for miles. You think your feet will suction to the wet mud\n\
on the ground. It is warm in the cave, yet a cold shiver runs up and\n\
down your spine. You can hear squeaks, but echo makes it nearly\n\
impossible to be able to tell where they are coming from.\n";

items =
  ({
   "cave",
   "A large open area with mud on the ground",
   "ground",
   "It's wet and filled with mud",  
   "mud",
   "It's thick and sticky",
   });
  dest_dir =
  ({
  "/players/angel/area/mansion/room/hiram_lair_02",   "out",
  });
}

init() {
  ::init();
    add_action("stop","out",1);
    add_action("disallow","quit");
}

  stop() {
    if(present("Hiram Abif Reborn", environment(this_player())))
      {write("Hiram slams you to the floor as you try to escape.\n");
      say(this_player()->query_name()+" is slammed to the floor as they try to escape.\n");
        return 1;
}}

  disallow() {
    if(present("Hiram Abif Reborn", environment(this_player())))
      if(this_player()->query_ghost() == 1) { return 0; }
      else{
      write("You can't quit from here.\n");
        return 1; }
}

realm(){ return "NT"; }