
#include "std.h"


reset(arg) {
    if(!arg)
   set_light(1);
   extra_reset();
}

object wraith, scroll;

extra_reset() {
   if(!present("wraith")) {
     wraith = clone_object("players/molasar/MONSTERS/wraith");
     transfer(wraith, this_object());
   }
}

init() {
   add_action("east","east");
   add_action("not","missile");
   add_action("not","mi");
   add_action("not","shock");
   add_action("not","sh");
   add_action("not","fireball");
   add_action("not","fi");
}

not() {
   write("Creatures of this plane are not affected by mortal spells.\n");
   return 1;
}

east() {
   this_player()->move_player("northeast#players/molasar/WORLD/room2");
   return 1;
}

short() { return "A hollow"; }

long() {
   write("A dark eerie hollow.  You can sense that something evil and\n");
   write("powerful makes its home here.\n");
   write("   There is one obvious exit:  east\n");
}

