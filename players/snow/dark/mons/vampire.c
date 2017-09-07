/* A vampire for DarK ArenA */

inherit "/obj/monster.c";
#include "/players/snow/dark/defs.h"
#define RAN random
#include "/players/snow/closed/cyber/color.h"

string victim;
reset(arg) {
   ::reset(arg);
   if (!arg) {
 
    set_name("vampire");
    set_short(BOLD+"Vampire"+OFF);
    set_race("undead");
    set_alias("vamp");
    set_long(
"A beautiful, smooth, mahogany form whose only desire is\n\
 to see you dead.\n");
    set_level(21);
    set_hp(random(200)+450);
    set_ac(random(10)+10);
    set_wc(random(30)+25);
    set_al(-1000);
    set_dead_ob(this_object());
    set_aggressive(1);
    set_chat_chance(15);
    load_chat(
" The vampire moves toward you...\n");
    load_chat(
" The vampire glides smoothly in an entrancing circle...\n");
    call_out("monster_move", random(50) + 1);
  }
}
 
monster_died() {
  object party;
  MO(clone_object("/players/snow/dark/stuff/vheal.c"), TO);
  party = present("party object", attacker_ob);
  if(party) party->share_exp(5000);
  if(!party) attacker_ob->add_exp(5000);
  TR(ENV(), "The vampire explodes in a dusky shower of ash!\n");
  "/players/snow/dark/counter.c"->add_count(-1);
  return 0;
}
 
heart_beat() {
  object meat;
  ::heart_beat();
  if(!environment()) return 1;
  if(attacker_ob) {
    if(victim != attacker_ob->query_real_name()) {
      victim = attacker_ob->query_real_name(); }
    if(ENV(attacker_ob) && ENV(attacker_ob) != ENV(TO) &&
       ENV(attacker_ob)->query_darena() == "boo") MO(TO,ENV(attacker_ob));
    drain();
    RE;
  }
  if(!attacker_ob) {
    if(victim) {
      meat = PRE(victim,ENV(TO));
      if(meat) {
        TO->attack_object(meat);
        drain();
      RE;
      }
      meat = find_player(victim);
      if(meat) {
        if(ENV(meat)->query_darena() == "boo") {
          MO(TO,ENV(meat));
          TO->attack_object(meat);
          drain();
      RE;
        }
      }
    }
    findmeat();
    RE;
  }
  RE;
}
 
findmeat() {
  object ob;
  ob = first_inventory(ENV(TO));
  while(ob) {
    if(ob->is_player()) {
      if(random(10) < 4) {
        TO->attack_object(ob);
        drain();
        RE;
      }
    }
    ob = next_inventory(ob);
  }
  RE;
}

 
monster_move() {
  int ran;
  string dest;
  call_out("monster_move",random(50));
  ran = random(9);
  if(ran == 0) dest = C1;
  if(ran == 1) dest = C2;
  if(ran == 2) dest = C3;
  if(ran == 3) dest = C4;
  if(ran == 4) dest = C5;
  if(ran == 5) dest = C6;
  if(ran == 6) dest = C7;
  if(ran == 7) dest = C8;
  if(ran == 8) dest = C9;
  MO(TO,dest);
  RE;
}
 
drain() {
  if(!environment(this_object())) return;
  if(!environment(attacker_ob)) return; /* added by verte 3-11-01 */
  if(RAN(10) < 4 || ENV(TO) != ENV(attacker_ob) ) RE;
  TE(attacker_ob,"  The vampire drains your body of life!\n");
  attacker_ob->heal_self(-(RAN(10)+10));
  TO->heal_self(RAN(20));
  attacker_ob->add_exp(-100);
  RE;
}