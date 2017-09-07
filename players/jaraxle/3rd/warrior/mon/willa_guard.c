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
    "A stunningly beautiful looking human female with brownish tanned skin.\nShe is slightly thin, yet muscular.\nShe has tribal tattoos surrounding each of her arms.\n");

set_level(15);
set_hp(275);
set_al(0);
set_ac(15);
set_aggressive(0);
MOCO("/players/jaraxle/3rd/warrior/weaps/bow.c"),this_object());
MOCO("obj/soul"),this_object());
init_command("wield bow");
set_wc(20);
set_dead_ob(this_object());

set_chat_chance(3);
  load_chat("The Warrior Maiden tightens her quiver.\n");
set_a_chat_chance(15);
  load_a_chat("The Warrior Maiden shoots an arrow into you!\n");

gold = clone_object("obj/money");
gold->set_money(800+random(200));
move_object(gold,this_object());
}

monster_died() {
  tell_room(environment(this_object()),
        "The Warrior Maiden falls lifeless to the ground.\n");
return 0; }
init() { 
::init();
add_action("kill_me","kill");
}
kill_me(arg) {
if(arg == "willa"){
write("The Maiden crosses her bow your way!\n");
return 1; }
}
