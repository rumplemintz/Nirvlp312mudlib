inherit "room/room";
#include "definitions.h"

reset(arg) {
        if(!arg) {
        set_light(0);
        short_desc=("South Hall");
        long_desc=
"     The main hall extends throughout the entire cavern.  It\n"+
"is not lit, yet the floor is well trampled on. . . signs of\n"+
"inhabitance.  Moisture slickens the walls, and a thin layer of mud\n"+
"covers the floor.  The cavern here is dark and cold.  It is almost\n"+
"completely silent.\n";

   dest_dir=({
        DAAICHIKIZAROOM+"/hall11.c","north"  ,
        DAAICHIKIZAROOM+"/hall13.c","southwest"  ,
        DAAICHIKIZAROOM+"/dairoom1.c","west"  ,
        DAAICHIKIZAROOM+"/dairoom2.c","northeast"  ,
            });

   items=({
        "mud","     The mud is cold and soft to the touch",
        "floor","     The floor is made of stone, but covered with mud",
        "moisture","     The walls are damp with mineral rich water",
        "cavern","     The cavern is almost straight east-west",
   });
   }   }