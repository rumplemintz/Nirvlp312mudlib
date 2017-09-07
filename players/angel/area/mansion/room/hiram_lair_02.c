/*                                                                    *
 *    File:         /players/angel/area/mansion/room/hiram_lair_02.c  *
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

int hit;

reset(arg)
{
  ::reset(arg);
  if(!present("new sign"))
     move_object(clone_object("/players/angel/area/mansion/obj/sign_03"), this_object());
  if(arg) return;
  set_light(0);
  short_desc = HIC+""+NORM;
  long_desc =
" This is a dark cavern. It appears to be very deep. It is bricked\n\
like an old large water well. A faint light can be seen to the east.\n\
There are some old wood stairs that spiral around the cavern and a\n\
platform controlled by a rope around a swivel bolted into a wood\n\
rafter high above. It appears the platform is stable enough to\n\
travel up and down the cavern.\n";

items =
  ({
    "brick",
    "They are large red brick that appear to be well aged",
    "bricks",
    "The bricks are well aged and one might be abled to bash them in",
    "leavers",
    "They are switches connected to the pulley",
    "light",
    "Some bricks are crumbling apart allowing light to come through",
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
    add_action("jump");         add_verb ("jump");
    add_action("search_room");  add_verb ("search");
    add_action("pull");         add_verb ("pull");
    add_action("release");      add_verb ("release");
    add_action("walk");         add_verb ("bash");
}

jump(str) {
	say(capitalize(this_player()->query_name())+
    " jumps over the wood rail.\n");
    this_player()->move_player(
    " jumps over the wood rail futher into the cavern#/players/angel/area/mansion/room/hiram_lair_03");
    say(capitalize(this_player()->query_name())+" arrives.\n");
    return 1;
}

DoDamage(object who) {
 if(hurt) { hurt = !hurt; return 1; }
  tell_object(who, HIR+"You feel the scaffolding slip downward!"+NORM);

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
    ste = 4;
    if (this_player()->query_attrib("ste") >= 19) ste = 3;
    if (random(ste) == 0) {
      write("You find the strength and pull the platform up.\n");
      call_other(this_player(),"move_player","in#players/angel/area/mansion/room/passageway_01");
}
else {
    write("You fall over and hit a wood poll. Ouch!\n");
    this_player()->hit_player(7 + random(9));
}
return 1;
}

release() {
    int ste;
    ste = 4;
    if (this_player()->query_attrib("ste") >= 19) ste = 3;
    if (random(ste) == 0) {
      write("You find the strength to release the platform down.\n");
      call_other(this_player(),"move_player","in#players/angel/area/mansion/room/hiram_lair_03");
}
else {
    write("You fall over and hit a wood poll. Ouch!\n");
    this_player()->hit_player(7 + random(9));
}
return 1;
}

walk(str) {
	say(capitalize(this_player()->query_name())+
    "bashes in the brick wall and steps through the hole.\n");
    this_player()->move_player(
    "bashes in the brick wall and steps through the hole.#/players/angel/area/mansion/room/hiram_lair_01");
    say(capitalize(this_player()->query_name())+" arrives.\n");
    return 1;
}

realm() {return "NT";}