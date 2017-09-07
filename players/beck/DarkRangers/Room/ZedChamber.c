inherit "room/room";
/*
#include "/players/beck/Rangers/RangerDefs.h"
#include "/players/beck/Rangers/Room/Regenerate.h"
*/
reset(arg) {
   if (arg) return;
   short_desc=("Lord Zed's Throne Room");
/*
Align = "Dark Ranger";
*/
   long_desc=
   "This is Lord Zed's Throne Room.\n"+
   "This room would be very dark except that it has a huge\n"+
   "window on one side of it.\n"+
   "Through this window you can get a good look of the entire Earth.\n"+
   "A large throne is in the center of the room and is where\n"+
   "Lord Zed spends most of his day.\n"+
   "There are several control panels on one side of the room.\n"+
   "Glancing around you notice one button that looks to be important.\n"+
   "Upon closer inspection you notice it is on the transporter control panel.\n"+
   "",
   set_light(1);
   items=
   ({
         "button","push it to exit the command center",
         "panel","this panel seems to run the transporter.  Look at the button",
    });
   dest_dir=
   ({
    });
if(!present("window", this_object())){
move_object("/players/beck/DarkRangers/ViewingWindow.c", this_object());}
   if(!present("zed", this_object())){
      move_object("/players/beck/monster/zed.c", this_object());}
}
short(){
return "Lord Zed's Throne Room";
}
init() {
   ::init();
   add_action("push","push");
/*
add_action("ATarget","regen");
add_action("RTarget","regen_stop");
*/
}
push(arg){
   if(!arg){write("Push what?\n"); return 1;}
   if(arg !="button"){write("You need to push the button.\n"); return 1;}
call_other(this_player(),"move_player","teleport#/players/beck/room/venus_cave1.c");
return 1;
}
/*
heart_beat(){
Regenerate();
}
*/