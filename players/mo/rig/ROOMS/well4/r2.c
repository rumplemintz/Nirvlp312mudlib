inherit "/players/vertebraker/closed/std/room.c";
#include <ansi.h>
int random_index;
reset(arg) {
   if(arg) return;
   random_index=random(2);
   move_object(clone_object(({"/players/mo/rig/MON/roughneck.c","/players/mo/rig/MON/toolhand4.c"})[random_index]),
      this_object());
   move_object(clone_object(({"/players/mo/rig/MON/geologist.c","/players/mo/rig/MON/d.c"})[random_index]),
      this_object());
   set_light(1);
   set_short("Well #4 - Chinle Oil Platform");
   set_long(
      "     You are standing on a metal floor that circles around the well. You are\n"+
      "able to walk "+BOLD+"around"+NORM+" the well area, but the view does not change much.\n"+
      "The well extends at least a hundred or so feet in the air.  It is cased in\n"+
      "a gray sheet metal that shields workers from potential blow outs. The area\n"+
      "is surprising clean which indicates that there have not been any oil blowouts\n"+
      "recently. Tools used by the roughnecks, and toolhands are scattered on\n"+
      "the floor.\n");
   
   add_exit("/players/mo/rig/ROOMS/well4/r3.c","around");
   
   add_item("tools","Wrenches, screw drivers, and pliers strewn about.\n");
   add_item("floor","A metal floor that you can walk on.\n");
   
}
