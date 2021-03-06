
#include "std.h"

object xynobyte, dagger, tooth;
   
#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset()
{
int i;
i = 0;
if (!xynobyte || !living(xynobyte)) {
  while (i < 5)  {
    i += 1;
    xynobyte = clone_object("obj/monster");
    call_other(xynobyte, "set_name", "xynobyte");
    call_other(xynobyte, "set_level", 8);
    call_other(xynobyte, "set_al", -200);
    call_other(xynobyte, "set_short", "A Xynobyte");
    call_other(xynobyte, "set_long", "Evolved during the ice age, this\n"
              +"little creature is extremely vicious.  It lives off the \n"
              +"blood of animals.  Sometimes the xynobyte will attack\n"
              +"if provoked.  During the Medeval period, these hapless\n"
          +"creatures were blamed for stealing babies...\n");
    call_other(xynobyte, "set_ac", 5);
    call_other(xynobyte, "set_wc", 9);
    dagger = clone_object("obj/weapon");
    call_other(dagger, "set_name", "dagger");
    call_other(dagger, "set_short", "A dagger");
    call_other(dagger, "set_long", "A very sharp dagger used by the \n"
              +"Xynobytes to extract the teeth from babies.\n"
              +"They later use the teeth in a hunting ritual for\n"
              +"good luck...\n");
    call_other(dagger, "set_class", 8);
    call_other(dagger, "set_weight", 1);
    call_other(dagger, "set_value", 200);
    move_object(dagger, xynobyte);
    tooth = clone_object("obj/treasure");
    call_other(tooth, "set_name", "tooth");
    call_other(tooth, "set_alias", "tooth");
    call_other(tooth, "set_value", 50);
    call_other(tooth, "set_weight", 1);
    call_other(tooth, "set_short", "A babies tooth");
    call_other(tooth, "set_long", "A babies tooth carried by\n"
              +"a Xynobyte for good luck during the hunt.\n");
    move_object(tooth, xynobyte);
    move_object(xynobyte, this_object());
   }
  }
 }

THREE_EXIT("players/morgoth/CASTLE/field10", "north",
    "players/morgoth/CASTLE/field12", "south",
    "players/morgoth/CASTLE/field15", "west",
    "A small clearing",
    "You have entered a small clearing in which\n"
   +"a group of Xynobytes are practicing a pre-\n"
   +"hunting ritual...  They are dancing around\n"
   +"a circle of miniature skulls.  After carefull\n"
   +"consideration you realize the skulls were once\n"
   +"babies heads...  It is then when you notice the\n"
   +"the small objects each Xynobyte holds...\n", 1)

