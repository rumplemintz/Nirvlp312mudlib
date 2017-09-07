/*                                                                    *
 *    File:         /players/angel/area/mansion/room/hiram_lair_03.c  *
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

status hurt;
toggle_hurt() { hurt = !hurt; }

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(0);
  short_desc = HIC+"Cavern"+NORM;
  long_desc =
" This is a dark cavern. It appears to be very deep. It is bricked\n\
like an old large water well. There are some old wood stairs that\n\
spiral around the cavern and a platform controlled by a rope around\n\
a swivel bolted into a wood rafter high above. It appears the plat\n\
form is stable enough to travel up and down the cavern.\n";

items =
  ({
    "bricks",
    "They are large red brick that appear to be well aged",
    "leavers",
    "They are switches connected to the pulley",
    "platform",
    "This is a small platform that uses a rope to lower and raise it in the well",
    "pulley",
    "It appears to be connected with rope that can be 'released' and 'pull'ed.",
    "rope",
    "It appears the rope can be 'released' and 'pull'ed.",
    "stairs",
    "They are maid of wood bolted to the circular well. The wood is rotten!",
    "swivel",
    "A stainless steal roller to help move the platform along",
    "well",
    "A large water well made over 100 years ago",
   });

}

init() {
  ::init();
    add_action("release");        add_verb ("release");
    add_action("search_room");    add_verb ("search");
    add_action("pull");           add_verb ("pull");

      if(this_player())
    DoDamage(this_player());
}

release(str) {
	say(capitalize(this_player()->query_name())+
    "releases the rope and the scafold drops down 50 yards.\n");
    this_player()->move_player(
    "releases the rope and drops futher into the cavern#/players/angel/area/mansion/room/hiram_lair_04");
    say(capitalize(this_player()->query_name())+" arrives.\n");
    return 1;
}

DoDamage(object who) {
 if(hurt) { hurt = !hurt; return 1; }
  tell_object(who, HIR+"\t\n\n\n\nYou feel the scaffolding slip downward!\n\n\n\n"+NORM);

  if(who->is_player()) {
  who->hit_player(40);

  }
  return 1;
}

  search_room() {
    write("You search and find a better way to control the rope.\n"+
      "You could attempt to pull the platform up again.\n");
      say (this_player()->query_name() +" searches the room.\n");
      return 1;
}
pull() {
    int ste;
    ste = 6;
    if (this_player()->query_attrib("ste") >= 19) ste = 3;
    if (random(ste) == 0) {
      write("You find the strength and pull up the platform up.\n");
      call_other(this_player(),"move_player","in#players/angel/area/mansion/room/hiram_lair_02");
}
else {
    write("You fall over and hit a wood poll. Ouch!\n");
    this_player()->hit_player(7 + random(9));
}

return 1;
}

realm() {return "NT";}