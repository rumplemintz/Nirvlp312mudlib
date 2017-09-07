inherit "obj/monster";
#include "/players/persephone/rooms.h"
object cyril;
reset(arg) {
  ::reset(arg);
    if(arg) return;
      cyril = clone_object("players/persephone/obj/bill");
      move_object(cyril,TOB);
      set_name("swashbuckler");
      set_alias("pirate");
      set_short("Swashbuckler");
      set_long("A swift and dashing young Swashbuckler\n"+
               "by the swagger in his step you think he\n" +
               "he thinks he runs the town\n\n");
      set_level (18);
      set_wc (28);
      set_ac (16);
      set_hp(475);
      set_al(0);
      set_aggressive(0);
      set_gender ("male");
}


init(){
  ::init();
    add_action("gerble","up");
    add_action("gerble","u");
    add_action("gerble","south");
    add_action("gerble","s");
    add_action("gerble","east");
    add_action("gerble","e");
    add_action("gerble","north");
    add_action("gerble","n");
}
gerble(){
  write("The Swashbuckler asks where you think you are going\n");
  say("The Swashbuckler blocks " + CAPTPLNM + "'s way\n");
return 1;
}