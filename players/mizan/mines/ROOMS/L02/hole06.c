inherit "/room/room.c";
#include "/obj/ansi.h"

void reset(int arg) 
{
   if(arg) return;
   set_light(1);
   
   short_desc = HIY + "[2]" + NORM + " Weasel Den Six - The Hidden Place";
   long_desc =
   "    Up to your ankles in warm, fermenting weasel poop, you realize that\n" +
   "  you're in what was once a rabbit burrow, stolen by the weasels long ago.\n"+
   "  It doesn't appear to go very far, as the way down has been plugged in\n"+
   "  with stacks of garbage, fecal matter, and dried chicken bones.\n" +
   "  You also realize that this must be the hidden weasel den that there\n"+
   "  was so much chatter about. Good for you! You've found it.\n";
   
  items = ({

    "floor",
    "The floor is absolutely filled with weasel poop. At least it's not moving.",

  });
  
  dest_dir = 
  ({
  });

  set_no_clean(1);
}

