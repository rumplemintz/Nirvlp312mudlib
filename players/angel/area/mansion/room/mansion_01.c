/*                                                                            *
 *      File:             /players/angel/area/mansion/mansion_01.c            *
 *      Function:         Heal shop / Quest                                   *
 *      Author(s):        Angel@Nirvana                                       *
 *      Copyright:        Copyright (c) 2007 Angel                            *
 *                                All Rights Reserved.                        *
 *      Source:           06/20/07                                            *
 *      Notes:            Entrance to Mansion                                 *
 *                        Expanded 02/01/17                                   *
 *                                                                            *
 *      Change History:                                                       *
 */

#include <ansi.h>

inherit "room/room";

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(1);
  short_desc = "Bob Ray's Mansion";
  long_desc =
"    "+HIY+"Mansion"+NORM+"\n\
  According to the mailbox near the street, this is Mayor Bob Ray's\n\
mansion.  It is a three-story brick home.  It appears to have\n\
brilliant workmanship. Some of the windows in the second floor are\n\
made of colored glass. The yard is well manicured. The house is a\n\
marvelous sight.\n";

  items =
  ({
  "glass",
  "The glass has many different colors",
  "home",
  "A three-story brick home",
  "mailbox",
  "A Decorative Whitehall Estate Mailbox",
  "window",
  "The window's look like something that you might find in Tiffany's",
  "yard",
  "It is well manicured. You see a paved circle drive to the north that leads to a side door",
});
  dest_dir =
  ({
  "/players/angel/area/town/room/emain_04", "road",
  });
}

init(){ 
  ::init();
    add_action("walk", "walk");
    this_player()->set_fight_area();
      }

exit(){    if(this_player()) this_player()->clear_fight_area();     }

realm(){ return "NT"; }

status walk(string arg) {
  if (!arg) {
    notify_fail("walk where?\n");
    return 0;
  }

  if (arg == "sidewalk") {
    notify_fail("walk where?\n");
    return 0;
  }

  if (arg == "drive" || arg == "driveway") {
    this_player()->move_player("you walk along the driveway to the house entrance#/players/angel/area/mansion/room/drive.c");
    return 1;
  }

  notify_fail("walk where?\n");
  return 0;
}

/*
init() {
  ::init();
  add_action("North", "north");
}

North() {
  if ( this_player()->query_level() < 30) {
    write("The mansion is currently under construction.\n");
    say(call_other(this_player(), "query_name", 0) +
      " is turned away at the door.\n");
    return 1;
  }
  write("You wriggle through the force field...\n");
  this_player()->move_player("you walk along the driveway to the house entrance#/players/angel/area/mansion/room/drive.c");
  return 1;
}*/