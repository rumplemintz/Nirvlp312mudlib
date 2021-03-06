inherit "/players/pavlik/guild/mages/inherit/dragon.c";
inherit "/players/pavlik/guild/mages/objects/dragon_spells";
#include "/players/pavlik/guild/mages/defs.h"

#define PET capitalize(name)

reset(arg){
  ::reset(arg);
  if(arg) return;
  set_name("dragon");
  set_short("Dragon");
  set_race("dragon");
  set_ep(0);
  set_alias("pet");
  set_can_kill(1);
  set_ac(0);
  set_wc(10);
  set_hp(50);
  set_level(1);
  set_dead_ob(this_object());
  set_owner(0);
  set_follow(1);
  set_max_sp(50);
  set_sp(50);
  set_dragon_short("the");
  set_dragon_long(0);
  set_dragon_level(0);
  set_dragon_attack(1);
  set_dragon_defense(1);
  set_dragon_stamina(1);
  set_dragon_magic(1);
  set_casting(0);
  set_assist(1);
  if(query_mhp()/10 > 15) set_wimpy(query_mhp()/10);
  else set_wimpy(15);
  enable_commands();
  set_message_hit(({
	HIC+"OBLITERATED"+NORM, " with a Savage tail-'n-teeth "+HIR+"frenzy"+NORM,
	HIC+"Smashed"+NORM, " into the ground with a Deadly "+HIC+"*"+NORM+"StomP"+HIC+"*"+NORM,
	HIC+"Lashed"+NORM, " with his "+HIK+"SpIkeD TaiL"+NORM,
	HIR+"clawed"+NORM, ", drawing "+RED+"blood"+NORM,
	HIR+"chomped"+NORM, ", feeding",
	CYN+"swung"+NORM+" his mighty "+HIK+"TaiL"+NORM+" at", "",
	CYN+"snapped"+NORM+" at", ", exhaling tenuous puffs of smoke",
  }));
  set_heart_beat(1);
}


id(str) {
  string o;
  return str == lower_case(name) || str == name2 || str == "dragon" ||
  str == "pet" || str == "mage_pet";
}


init()
{
  ::init();
  if( !owner && tp->query_real_name() == query_owner_name() )
    set_owner( tp );
  if(owner && tp == owner)
  {
	add_action("dragon_commands", lower_case(name));
	add_action("dragon_commands", "dragon");
  }
}


heart_beat()
{
  object obj;

  ::heart_beat();

  if(!owner)
  {
#if 0
	if(environment())
		tell_room(environment(),  PET+" leaps"+NORM+" into the sky and "+HIBLK+"disappears."+NORM+"\n");
        destruct( this_object() );
#else
	if(environment()) {
	  tell_room(environment(),  PET+" leaps"+NORM+" into the sky and "+HIBLK+"disappears."+NORM+"\n");
          move_object( this_object(), ROOM_DIR+"dragon_room" );
	  tell_room(environment(),  PET+" enters the room and falls into a deep "+CYN+"slumber."+NORM+"\n");
        }
        set_heart_beat(0);
#endif
	return 1;
  }
  else {
    obj = present("mageobj", owner);
    if( obj )
      obj->set_dragon_hps( query_hp() );
  }

  if(follow)
	pet_follow();

  add_spell_point(1 + random(3));
  if(query_attack() && query_hp() <= wimpy)
	dragon_flee();

#define drag this_object()
 
  if(query_attack() && !random(4))
  {
    int choice, spl;
    
    choice = 1 + random(drag->query_dragon_level());
    spl = 1 + random(2);
 
    if(choice >= 13){
      if(spl == 1) lightning_bolt(drag);
      else if(spl == 2) heal_spell(drag);
      else if(spl == 3) lightning_bolt(drag);
    } 
    else if(choice >= 9){
      if(spl == 1 || spl == 3) heal_spell(drag);
      else acid_arrow(drag);
    }
    else if(choice >= 5){
      if(spl == 1) breath_fire(drag);
      else if(spl == 2) breath_acid(drag);
      else if(spl == 3) breath_ice(drag);
    }
    else
      dragon_klaw(drag);
  }
  if(assist && !query_attack() && owner->query_attack() && environment() == environment(owner) )
  {
	tell_room(environment(),
	  HIC+PET+NORM+" looses an "+HIM+"ear-splitting "+HIY+"R~O~A~R"+NORM+" and jumps into the fray!\n"+NORM);
	set_can_kill(1);
	owner->query_attack()->set_can_kill(1);
	attack_object(owner->query_attack());
  }

}

