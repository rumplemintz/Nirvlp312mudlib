inherit "/players/vertebraker/closed/std/room.c";
#include <ansi.h>

reset(arg) {
   if(arg) return;
   set_light(1);
   set_short("Sea of Hirandea");
   set_long(
      ""+BOLD+"\n"+
      
      ""+NORM+""+BLU+" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
      ""+NORM+""+BLU+" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
      ""+NORM+""+BLU+" ~~~~~~~~~~~~~~~~~~~~~~~~"+NORM+""+GRN+"###"+NORM+""+BLU+"~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
      ""+NORM+""+BLU+" ~~~~~~~~~~~~~~~~~~~~~~"+NORM+""+GRN+"#######"+NORM+""+BLU+"~~~~~~~~~~~~~~~~~~~~~~~\n"+
      ""+NORM+""+BLU+" ~~~~~~~~~~~~~~~~~~"+NORM+""+GRN+"###################"+NORM+""+BLU+"~~~~~~~~~~~~~~~\n"+
      ""+NORM+""+BLU+" ~~~~~~~~~~~~~~~~~~~~"+NORM+""+GRN+"####################"+NORM+""+BLU+"~~~~~~~~~~~~\n"+
      ""+NORM+""+BLU+" ~~~~~~~~~~~~"+NORM+""+GRN+"################################"+NORM+""+BLU+"~~~~~~~~\n"+
      ""+NORM+""+BLU+" ~~~~~~~"+NORM+""+GRN+"#########################################"+NORM+""+BLU+"~~~~\n"+
      ""+NORM+""+BLU+" ~~~~~~~"+NORM+""+GRN+"#########################################"+NORM+""+BLU+"~~~~\n"+
      ""+NORM+""+BLU+" ~~~~~"+NORM+""+GRN+"##############################################"+NORM+""+BLU+"~"+NORM+"\n");
   add_exit("/players/mo/rig/ROOMS/sea/r1.c","south");
   add_exit("/players/mo/rig/ROOMS/sea/r3.c","north");
}