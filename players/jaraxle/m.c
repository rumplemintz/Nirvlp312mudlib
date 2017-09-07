#include "/players/jaraxle/define.h"
inherit "obj/monster.c";

reset(arg)  {
   object gold;
   ::reset(arg);
   if(arg) return;
   
   set_name("Warrior Maiden");
   set_alias("maiden");
   set_alt_name("warrior");
   set_race("human");
   set_short("Warrior Maiden");
   set_long(
      "A beautiful looking human female with brownish tanned skin.\nShe is slightly thin, yet muscular.\n");
   set_level(15);
   set_hp(2000+random(1));
   set_al(-2000);
   set_ac(13);
   set_aggressive(1);
   init_command("wield bow");
   set_wc(20);
   set_dead_ob(this_object());
   set_chat_chance(3);
   load_chat("The Warrior Maiden tightens her quiver.\n");
   set_a_chat_chance(15);
   load_a_chat("The Warrior Maiden shoots an arrow into you!\n");
   gold = clone_object("obj/money");
   gold->set_money(0+random(0));
   move_object(gold,this_object());
}

monster_died() {
   tell_room(environment(this_object()),
      "The Warrior Maiden falls lifeless to the ground\n");
   return 0; }
