
#include "std.h"

reset(arg) {
   if(!arg) 
     set_light(1);
   extra_reset();
}

object tree;

extra_reset() {
   if(!present("tree")) {
     tree = clone_object("players/molasar/MISC/elftree");
     move_object(tree, this_object());
   }
}

short() { return "A large clearing in the forest"; }

long() {
   write("You have entered a large clearing in the forest.  This area seems\n");
   write("to be tended on a regular basis by the lack of stray foilage.\n");
   write("A large tree sits on top of a small knoll.\n");
   write("   There are two obvious exits:  south and west\n");
}

init() {
   add_action("south","south");
   add_action("west","west");
}

south() {
   this_player()->move_player("south#players/molasar/FOREST/forest17");
   return 1;
}

west() {
   this_player()->move_player("west#players/molasar/FOREST/forest13");
   return 1;
}

