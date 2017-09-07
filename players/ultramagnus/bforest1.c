#include "std.h"
#undef EXTRA_INIT
#define EXTRA_INIT\
       add_action("up","climb");
#undef EXTRA_RESET
#define EXTRA_RESET\
extra_reset();
extra_reset()
{
       object tree;
if(!present("tree")){
       tree = clone_object("players/ultramagnus/btree.c");
       move_object(tree, this_object());
}
}
FOUR_EXIT("players/ultramagnus/forest3.c", "east",
        "players/ultramagnus/bforest2.c", "west",
       "players/ultramagnus/bforest5.c", "north",
       "players/ultramagnus/blueforest.c", "south",
        "Blue Forest",
        "You are in the Blue Forest. You see the main path to the east.\n" +
        "There are several trees with vibrant Blue leaves about.\n", 1)
up()
{
       call_other(this_player(), "move_player", "up#players/ultramagnus/bluetree.c");
       return 1;
}