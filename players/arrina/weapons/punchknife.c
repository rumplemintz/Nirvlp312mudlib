#include "/obj/ansi.h"

inherit "obj/weapon.c";

reset(arg)
{
  ::reset(arg);
  if (arg) return;
  set_name("punchknife");
  set_alias("knife");
  set_short(GRY+"Obsidian "+HIR+"Punchknife"+NORM);
  set_long("This is a knife you hold in your fist, with the blade\n\
extending through your fingers. It is well balanced and you \n\
feel it's power as you slide the blade between your fingers.\n");
  set_class(19);
  set_type("knife");
  set_weight(2);
  set_value(10000);
  set_hit_func(this_object());
}

weapon_hit(attacker)
{
  int W;
  W = random(100);
  if(W>70)
  {
    say(GRN+"The knife punches through its enemy!\n"+NORM);
    write(GRN+"The knife punches through its enemy!\n"+NORM);
    return 0;
  }
  if(W>50 && W <69)
  {
    say("As the punchknife strikes out within the fist of it's owner\n"+
    "and effortlessly enters the body of the foe....\n\t\t"+RED+
    "WARM BLOOD POURS...\n"+NORM+"over the hand of it's user.\n");
    write("As you punch out, the blade thrusts ahead of your fists\n"+
    "and effortlessly enters the body of your foe...\n"+
    "and you watch as\n\t\t"+RED+
    "WARM BLOOD POURS...\n"+NORM+
    "over your hand......\n");
    return 5;
  }
  if(W<11)
  {
    write("You feel the knife in your fist thirsting for blood!\n");
    return 7;
  }
  return;
}