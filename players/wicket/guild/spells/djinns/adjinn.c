#include "/players/wicket/guild/defs.h"
#include <ansi.h>
inherit "/obj/monster";

object owner, target;

int monitor, stay;

reset(arg)
{
	::reset(arg);
	if(arg) return;
	set_name("djinn");
	set_alt_name("air");
	set_race("djinn");
	set_alias("air djinn");
	set_short("An "+HIW+"Ancient"+HIY+" Air Djinn"+NORM+" ("+YEL+"shrouded in winds"+NORM+")" );
	set_level(0);
	set_hp(0);
	set_ac(0);
	set_wc(0);
	set_al(0);
	set_heal(5, 5);
	set_no_exp_value(1);
	set_dead_ob(this_object());
	monitor = 1;
}

long(){
  write("An ancient air djinn that burns with a deep power from the element of fire.\n");
  write("It it made of nothing but complete air and just glows with immense power.\n");
  write("It appears to pay attention to only its master for which it was summoned.\n");
  if(TP == owner){
    write("Use 'ecmds' for more details.\n"); }
    if(hit_point < (max_hp/10)) {
      write("The Djinn is in very bad shape.\n"); return; }
    if(hit_point < (max_hp/5)) {
      write("The Djinn is in bad shape.\n"); return; }
    if(hit_point < (max_hp/2)) {
      write("The Djinn is somewhat hurt.\n"); return; }
    if(hit_point < (max_hp - 20)){
      write("The Djinn is slightly hurt.\n"); return;}
      write("The Djinn is in good shape.\n");
 }
 
 monster_died()
 {
	 object orb;
	 
	 orb = present("wicket_element_orb", owner);
	 
	 orb->set_has_djinn(0);
	 AIRDAEMON->add_people(owner);
	 return 1;
 }

init(){
	::init();
    	
	if(TP && TP == owner && !TP->query_ghost()) {
	    add_action("fight","attack");
	    add_action("dismiss", "dismiss");
	    add_action("feed","feed");
	    add_action("beckon","beckon");
	    add_action("dmon","dmon");
	    add_action("ecmds","ecmds");
  	}
}

ecmds(){
	tell_object(owner, "\n(~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~)\n");
	tell_object(owner, "				Djinn Commands\n");
	tell_object(owner, "attack		Makes your Djinn attack a mob.\n");
	tell_object(owner, "dismiss		Dismiss your Djinn.\n");
	tell_object(owner, "feed		Offer a corpse to your Djinn.\n");
	tell_object(owner, "beckon		Command your pet to stay/follow.\n");
	tell_object(owner, "dmon		Can be used to turn 'on' and 'off' or to check its health.\n");
	tell_object(owner, "(~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~)\n");
	return 1;
}

fight(str){
	if(!str && !owner->query_attack()){
		write("The Air Djinn blinks at you.\n");
		return 1;
	}
	
	if(!str && TO->query_attack()){ 
		write("The Air Djinn tells you: I'm already attacking "+TO->query_attack()->query_name()+".\n");
		return 1;
	}
	
	if(!str && owner->query_attack() && !attacker_ob && !owner->query_attack()->is_player()){
		say("The Air Djinn spins around violent and attacks "+owner->query_attack()->query_name()+".\n");
		attacker_ob = owner->query_attack();
		return 1;
	}
	
	target = present(str, environment(TO));
	
	if(!target){
		write("The Air Djinn tells you: I don't see any "+str+" here\n");
		return 1;
	}
	
	if(target->query_npc() == 0) {
		write("The Air Djinn tells you: Kill the player on your own!\n");
		return 1;
	}
	say("The Air Djinn spins around violent and attacks "+target->query_name()+".\n");
	this_object()->attack_object(target);
	return 1;
}

dismiss(){
	object ob;
	
	ob = present("wicket_element_orb", TP);
	say("The Air Djinn bows to its audience and flies into the sky.\n");
	ob->set_has_djinn(0);
	ob->gsave();
	destruct(TO);
	return 1;
}

feed(){
	object ob;
	ob = present("corpse", ENV(TO));
	if(!ob){
		tell_object(owner, "The Djinn fails to find a corpse and "+HIR+"GASHES"+NORM+" your arm out of anger!\n");
		owner->hit_player(30 + random(10), "other|wind");
		return 1;
	}
	say("The ancient winds whip around the djinn closing up their wounds slowly as the corpse is absorbed.\n");
	hit_point += ob->heal_value();
	if(hit_point > max_hp) hit_point = max_hp;
	destruct(ob);
	return 1;
}


beckon(){
	if(this_object()->query_attack()){
		write("The Djinn glares at you while continuing its attack.\n");
		return 1; 
	}
	
	if(stay != 1)
	{
		say("The Djinn bows to "+owner->query_name()+" and begins to relax.\n");
		stay = 1;
		return 1;
	}
	
	if(stay == 1)
	{
		say("The Djinn nods to "+owner->query_name()+" and begins to follow.\n");
		stay = 0;
		return 1;
	}
	return 1;
}

dmon(str){

	if(!str){
		tell_object(owner, BOLD+YEL+"Air Djinn: "+HIW+((hit_point * 10)/max_hp)+" / 10"+NORM+"\n");
		return 1;
	}
	
	if(str == "on" && monitor == 1){
		write("Your pet monitor is already on.\n");
		return 1;
	}
	
	if(str == "on" && monitor != 1){
		write("You turn on your pet monitor.\n");
		monitor = 1;
		return 1;
	}
	
	if(str == "off" && monitor != 1)
	{
		write("Your pet monitor is already off.\n");
		return 1;
	}
	
	if(str == "off" && monitor == 1)
	{
		write("You turn off your pet monitor.\n");
		monitor = 0;
		return 1;
	}
}


heart_beat(){
 
	if(root()) return;
	if(!owner) return;
	::heart_beat();
	
	if(owner && stay != 1 && !owner->query_ghost()){
		if(ENV(TO) != ENV(owner)){
			say("The Air Djinn follows after its owner, "+capitalize(owner->query_name())+".\n");
			move_object(this_object(), environment(owner));
			say("The Air Djinn flows in behind "+capitalize(owner->query_name())+".\n");
			set_heart_beat(1);
		}
		if(TO->query_attack() && monitor == 1){
			tell_object(owner, 
 			BOLD+HIY+"Air Djinn: "+HIW+((hit_point * 10)/max_hp)+" / 10"+NORM+"\n");
		} 
		if(!TO->query_attack() && owner->query_attack() && !owner->query_attack()->is_player()){
 			say("The Air Djinn spins wildly and attacks "+owner->query_attack()->query_name()+".\n");
			this_object()->attack_object(owner->query_attack());
		}
	}
	
	if(query_hp() < query_mhp()) heal_self(5);
}

is_pet(){ return 1; }
is_djinn() { return 1; }

patch_owner(o) { owner = o; }
