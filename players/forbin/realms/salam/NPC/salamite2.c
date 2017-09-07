/*
 *  Created:      Forbin@Nirvana
 *  Copyright:    Copyright (c) 2004 Forbin
 *                  All Rights Reserved.
 *  Realm:        Caves of the Salamite
 *  Function:     NPC
 *  Create Date:  2004.06.05
 *  Last Edit:    2004.06.10 -Forbin
 *  Notable Changes:            
 */ 

#include "/players/forbin/realms/salam/salamdefine.h"
#include "/players/forbin/logging.h"
#pragma combine_strings
inherit "/players/vertebraker/closed/std/monster.c";

reset(arg)  {
  ::reset(arg);
  if(arg) return;
  set_name("Salamite Warrior");
  set_alt_name("salamite warrior");
  set_alias("warrior");
  set_race("salamite");
  set_gender("male");
  set_short("A "+HIR+"Sala"+NORM+RED+"mite"+NORM+" Warrior");
  set_long(
    "  Ruddy red and covered with bright red scales, this creature \n"+
    "looks like a salamander, yet stands on its back two feet - while\n"+ 
    "balancing with a long tail.  Reaching six feet tall, its body is\n"+
    "smeared with a black substance that seems to have hardened into a\n"+
    "natural armor.  It looks ready to fight.\n");
  set_level(19);
  set_hp(500);
  set_al(-500);
  set_wc(30);
  set_ac(17);
  set_dead_ob(this_object());
  set_chat_chance(5);
    load_chat("The Salamite tenses up...ready to fight...\n");
    load_chat("The Salamite hisses at you...\n");
  set_a_chat_chance(20);
    load_a_chat("The Salamite tosses you to the ground...\n");
    load_a_chat("With lightning reflexes, the Salamite punches you in the face....\n");
    load_a_chat("The Salamite swings hard...barely missing you...\n");  
  set_chance(15);
  set_spell_dam(30);
  set_spell_mess1(
    "\nThe Salamite "+HIR+"xXx "+HIW+"SMACKS "+HIR+"xXx"+NORM+" its opponent with its tail...\n");
  set_spell_mess2(
    "\nThe Salamite "+HIR+"xXx "+HIW+"SMACKS "+HIR+"xXx"+NORM+" you with its tail!\n");
}

init(){
  ::init();
}

/* 
 *  ***********************************************************************
 *  Function:    heal_self
 *  Description: no heal_self damage allowed
 *  Arguments:   none
 *  ***********************************************************************
 */

heal_self(int i) {
  if(i < 0){
    tell_room(environment(), "The salamite hisses loudly, shrugging off your attack!\n");
    return 1;
  }
  ::heal_self(i);
  return 1;
}

monster_died() {
  object treasure;
#ifdef KILLLOG
  mon_log(KILLLOG);
#endif
tell_room(environment(this_object()),
    "\n\nWith the killing blow, a chunk of scales is knocked from the Salamite.\n\n");
  treasure = clone_object(OBJ+"salamite_scales.c");
  move_object(treasure,environment(this_object()));
    return 1;
}
