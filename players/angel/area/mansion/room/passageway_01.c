/*                                                                            *
 *      File:             /players/angel/area/mansion/room/passageway_01.c    *
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

inherit "room/room.c";

status hurt;
toggle_hurt() { hurt = !hurt; }

int hit;

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(0);
  short_desc = HIC+""+NORM;
  long_desc =
"This passageway opens into a large dark cavern. Looking around\n\
there is an old wood system with pulley's and levers setup to\n\
move up and down the cavern. There is a faint sound of moving\n\
water below.\n";

items =
  ({
    "bricks",
    "They are large red brick that appear to be well aged",
    "levers",
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
    add_action("jump");         add_verb ("jump");
    add_action("search_room");  add_verb ("search");
    add_action("release");      add_verb ("release");

}

jump(str) {
	say(capitalize(this_player()->query_name())+
    " jumps over the wood rail.\n");
    this_player()->move_player(
    " jumps over the wood rail futher into the cavern#/players/angel/area/mansion/room/hiram_lair_02");
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
      "You could attempt to pull and release the platform with the ropes\n"+
      "or jump down though that might be dangerous!\n");
      say (this_player()->query_name() +" searches the room.\n");
      return 1;
}
release() {
    int ste;
    ste = 4;
    if (this_player()->query_attrib("ste") >= 19) ste = 3;
    if (random(ste) == 0) {
      write("You find the strength to release the platform down.\n");
      call_other(this_player(),"move_player","in#players/angel/area/mansion/room/hiram_lair_02");
}
else {
    write("You fall over and hit a wood poll. Ouch!\n");
    this_player()->hit_player(7 + random(9));
}

return 1;
}

realm() {return "NT";}