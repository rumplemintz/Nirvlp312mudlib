#include "/players/maledicta/ansi.h"
inherit "obj/monster.c";

object gold,helmet,armor,weapon,shield;
int guarding;

reset(arg)  {
  ::reset(arg);
  if(arg) return;

set_name("guard");
set_alt_name("high_guard");
set_alias("templar");
set_race("human");
set_short(HIB+"High Templar"+NORM);
set_long(
"  Before you stand the most powerful of the templar guard. He is\n"+
"dressed in full suits of plate armor, each tinted blue with a white\n"+
"cross displayed on the breastplate and knee guards. A large shield\n"+
"is held at the ready, and an oversized broadsword is left sheathed\n"+
"at the hip. He seems ready for any combat.\n");  
set_level(20);
set_hp(850);
set_al(1000);
weapon = clone_object("players/maledicta/templar/items/bsword");
move_object(weapon, this_object());
command("wield pike", this_object());
armor = clone_object("players/maledicta/templar/items/fullplate2");
move_object(armor, this_object());
command("wear fullplate", this_object());
helmet = clone_object("players/maledicta/templar/items/helmet");
move_object(helmet, this_object());
command("wear helmet", this_object());
shield = clone_object("players/maledicta/templar/items/shield");
move_object(shield, this_object());
command("wear shield", this_object());
set_wc(30);
set_ac(20);
set_aggressive(0);
set_heart_beat(1);
set_chance(20);
set_spell_dam(30);
set_spell_mess1(
  "The High Templar charges his foe!\n");
set_spell_mess2(
  "You feel a biting pain as the High Templars Sword slices into your flesh!\n");
gold = clone_object("obj/money");
gold->set_money(800);
move_object(gold,this_object());
}



heart_beat(){
int x;
object ob;
object ob2;
object att;
object next;

if(query_wc() < 30) set_wc(30);
if(query_ac() < 20) set_ac(20);
 
::heart_beat();

if(attacker_ob && !attacker_ob->query_ghost()){
  already_fight=0;
  attack();
  }

ob2 = first_inventory(environment(this_object()));
if(!query_attack()){
  while(ob2) {
      att = ob2->query_attack();
      next = next_inventory(ob2);
	  if(att && ob2->query_templar_guard()){
		  tell_room(environment(),
			  "The Templar Guard rushes to the attack!\n\n");
		  attack_object(att);
		       }
  ob2 = next;      
  }
 }
}	

