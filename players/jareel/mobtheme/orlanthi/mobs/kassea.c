inherit "/obj/monster";
#include "/players/jareel/define.h"
#define TO this_object()

int K;
int sword;
reset(arg) {
   ::reset(arg);

if (arg) return;
    set_alias("priestess");
    set_alt_name("rune priestess");
    set_name("kassea");
    set_race("human");
    set_al(0);
    set_level(23);
    set_aggressive(0);
    set_hp(800);
    add_money(5000+random(1900));

MOCO("/players/jareel/armor/orlanthi_wind_priestess_robes.c"),this_object());
init_command("wear armor");



  set_ac(21);
  set_wc_bonus(46);
  set_ac_bonus(20);
  set_wc(40);
  set_gender("female");
  set_dead_ob(this_object());

set_short(
     "Kassea - "+BOLD+BLU+"Rune Priestess"+NORM+" of Orlanth Thunderous. (neutral)");

set_long(
"Before you stands what appears to be a young woman, but appearances can\n"+
"be deceiving.  A powerful magical aura surrounds her diminutive stature.\n"+
"As you look at her the hair on your neck stands up with the electricity\n"+
"in the air.\n");

set_chance(40);
set_spell_mess1(
     "Kassea fires an energy bolt from her hand.\n");
set_spell_mess2(
     "Kassea fires an energy bolt from her hand\n");
 
set_spell_dam(50);
set_chat_chance(10);
load_chat("Kassea says: 'Who let you in here.'\n");
load_chat("Kassea says: 'Henrik, get your ass in here!'\n");
}

heart_beat(){
  ::heart_beat();
if(attacker_ob) {
    already_fight=0;
    attack();
K = random(5);
if(attacker_ob){
  if(K <= 1) K_thunderstrike();
  if(K == 2) K_heal();
  if(K == 3) K_heal2();
  else if(K >= 4) K_lightningstrike();
}
}
} 

K_thunderstrike()  {
tell_room(environment(TO),
  "Kassea waves her hand.\n"+
  "\n"+
  "        "+BLU+" B O O M ! ! !"+NORM+"\n"+
  "\n"+
  "You are thrown back by a sonic thunder blast.\n");
  call_other(attacker_ob,"hit_player",random(50)+5);
  return;
}

K_heal() {
tell_room(environment(TO),
  ""+BOLD+BLU+"Kassea channels energy from the robes"+NORM+".\n");
  heal_self(random(30));
return;
}

 
K_heal2()  {
tell_room(environment(TO),
  "Kassea intones a few words\n");
  heal_self(random(30));
return;
}
 
K_lightningstrike() {
tell_room(environment(TO),
  "Kassea unleashes lightning\n"+
  "\n"+
  ""+BLINK+BOLD+"   L I G H T N I N G "+NORM+" leaps from the blade.\n"+
  "\n"); 
  call_other(attacker_ob,"hit_player",random(60)+5);
return;
}
monster_died() {
}
