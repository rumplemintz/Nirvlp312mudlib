#include "../defs.h"
/******************************************************************************
 * Program: command.c
 * Path: /players/dragnar/Jedi/lib
 * Type: Inherit
 * Created: May 20th, 1999 by Dragnar
 *
 * Purpose: Inherited object for all of the Jedi spells. Keeps track of
 *          required variables and does all the checks for doing an
 *          attack. Some ideas borrowed from Pavliks Mage guild.
 *          Jedi spells are in the /bin directory.
 * History:
 *          05/20/1999 - Dragnar
 *            Created
 *          02/22/2014 - Dragnar
 *            Updated to include more variables and made calls more flexible.
 ******************************************************************************/
#define DEBUG 1
#define PENALTY_DEBUG 0

int skill_level;      /* Skill level required */
int rank_level;       /* Jedi Rank required */
int atk_flag;         /* Does this spell start a fight? */
int delay_flag;       
int saber_flag;       /* Does this spell require a lightsaber? */
int sp_cost;          /* Spell cost */
int combo_bonus;
string name;
string skill_type;
string old_attack;
string *BonusAttacks;
string description;
object target;        /* Spell target */
object Saber;         /* our lightsaber object */

int force_spell( string who, object jedi, object gob );
int start_attack( string str, object jedi );
status sp_check( object jedi );
status rank_check( object jedi );
status skill_check( object gob );
status saber_check( object jedi, object gob );
delay_check();

query_name() { return name; }
query_skill_type() { return skill_type; }
query_skill_level() { return skill_level; }
query_description() { return description; }
query_cost() { return sp_cost; }

int calc_exp( object jedi, object gob ) {
  int gexp;
  int exp_worth, mod, lev;

  gexp = sp_cost;
  tell_object( jedi, "\t\texp Gain sp cost: "+gexp+"\n");

  if( atk_flag && target ) {
    /** Bonus for attacker level **/
    lev = (int) target->query_level();
    if( lev > 30 )
      lev = 30;
    gexp += lev / 2;
  tell_object( jedi, "\t\texp Gain lev: "+gexp+"\n");

    /** Bonus for attack exp value **/
    exp_worth = (int)target->calculate_worth();     
    switch( exp_worth ) {
      case 0..500:
        gexp = gexp * 105 / 100;
        break;
      case 501..800:
        gexp = gexp * 110 / 100;
        break;
      case 801..1500:
        gexp = gexp * 115 / 100;
        break;
      case 1501..2500:
        gexp = gexp * 120 / 100;
        break;
      case 2501..4000:
        gexp = gexp * 125 / 100;
        break;
      case 4001..5900:
        gexp = gexp * 130 / 100;
        break;
      case 5901..7500:
        gexp = gexp * 135 / 100;
        break;
      case 7501..9999:
        gexp = gexp * 140 / 100;
        break;
      case 10000..20000:
        gexp = gexp * 155 / 100;
        break;
      case 20001..35000:
        gexp = gexp * 160 / 100;
        break;
      case 35001..50000:
        gexp = gexp * 170 / 100;
        break;
      case 50001..100000:
        gexp = gexp * 180 / 100;
        break;
      case 100001..200000:
        gexp = gexp * 190 / 100;
        break;
      case 300001..500000:
        gexp = gexp * 190 / 100;
        break;
      case 500001..1000000:
        gexp *= 2;
        break;
      case 1000001..900000000:
        gexp = gexp * 225 / 100;
        break;
      default:
        break;
    }
  tell_object( jedi, "\t\texp Gain worth: "+gexp+"\n");
    
    /** Bonus for tanking **/
    if( (object) target->query_attack() == jedi ) {
     gexp = gexp * 15 / 10;
  tell_object( jedi, "\t\texp Gain tank: "+gexp+"\n");
     /** 20% Bonus for being only attacker **/
     if( !target->query_alt_attack() ) {
       gexp = gexp * 12 / 10;
  tell_object( jedi, "\t\texp Gain alt atk: "+gexp+"\n");
     }
    }
    
  }
  return gexp;
;
}

int force_spell( string who, object jedi, object gob ) {
  int gexp;

  if( jedi->query_ghost()) {
    notify_fail("You fail to reach the force.\n");
    return 0;
  }
  if( !sp_check( jedi ) ) {
    return 0;
  }
  
  if( rank_level && !rank_check( jedi ) ) {
     return 0;
  }

  if( saber_flag && !saber_check( jedi, gob ) )
    return 0;
   
  if( atk_flag && !start_attack( who, jedi ) )
    return 0;
    
  if( delay_flag && !delay_check( gob ) )
    return 0;
    
  /************************************************
    Need to add guild experience for the spell
    being used. Attack spells should consider:
      1. Level / exp worth of mob
      2. Is user tanking?
      3. Does mob have other attackers?
      4. Spell cost?
      5. Delay spells should get more exp
    Non attack spells: ???
   ************************************************/
  gexp = calc_exp( jedi, gob );
  tell_object( jedi, "EXP Gain: "+gexp+"\n");
  gob->add_skill_rank( query_verb(), "exp", gexp );
  return 1;
}

int start_attack( string str, object jedi ) {

  if(str) {
    target = present(str, environment( jedi ));
    if(!target) {
      write("You are unable to locate the force essence of "+capitalize(str)+".\n");
      target = 0;
      return 0;
    }
    if(!living(target)) {
      write("The lack of force essence in "+capitalize(str)+" indicates they are not a living being.\n");
      target = 0;
      return 0;
    }
    target->attacked_by( jedi );
  }
  else
    target = (object) jedi->query_attack();
  if(!target) {
    if( saber_flag ) {
      write("You must be attacking in order to use "+query_verb()+".\n");
        return 0;
    }        
      write("Who do you want to use "+query_verb()+" on?\n");
      return 0;
   }
   if( target == jedi ) {
      write("You can't attack yourself.\n");
      target = 0;
      return 0;
   }
   if( target->query_ghost() ) {
      write("The force has no impact on the dead.\n");
      target = 0;
      return 0;
   }
   if( target->is_player() && !present("jedi_object", target) ) {
      write("You can't use "+query_verb()+" on "+str+".\n");
      target = 0;
      return 0;
   }

   return 1;
}

status rank_check( object jedi ) {
   if( jedi->query_guild_rank() < rank_level ) {
      write("You have not mastered that ability.\n");
      return 0;
   }
   return 1;
}

status skill_check( object gob ) {

  if(!skill_type) skill_type = query_verb();
  if(gob->query_skill( skill_type ) < skill_level ) {
    write("You have not mastered that ability.\n");
    return 0;
  }
  return 1;
}

status saber_check( object jedi, object gob ) {
  
  Saber = present("jedi_saber", jedi );
  if(!Saber || !Saber->query_ignited()) {
    write("You try to "+query_verb()+" but fail.\n");
    return 0;
  }
    
  if( jedi->query_spell_dam()) {
    write("You are already doing an attack.\n");
    return 0;
  }

  old_attack = (string) gob->query_saber_attack();
  
  if(member_array( old_attack, BonusAttacks ) > -1) 
    combo_bonus = 1;

  jedi->set_spell_dam( gob->query_skill(SABER) );
  jedi->set_spell_dtype("other|force");
  return 1;
}

status cp_check(int needed, object gob ) {
   if(gob->query_cp() < needed || this_player()->query_ghost()) {
    write("Your concentration fails you.\n");
    return 0;
  }
  return 1;
}

status sp_check( object jedi ) {
  if( jedi->query_sp() < MIN_SP ) {
    write("You are too drained to call on the force.\n");
    return 0;
  }
  if( sp_cost > 0 )
    jedi->add_spell_point(-sp_cost);
  
  return 1;
}

delay_check( object gob ) {
  if(gob->query_force_delay()) {
    write("You are too weary to concentrate.\n");
    return 0;
  }
  return 1;
}

level_to_class(int x ) {
  switch( x ) {
  case 1..4:
    return "Apprentice";
    break;
  case 5..8:
    return "Jedi Knight";
    break;
  case 9..12:
    return "Jedi";
    break;
  case 13:
    return "Jedi Master";
    break;
  default:
    return "Error";
    break;
  }
}
