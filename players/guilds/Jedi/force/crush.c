#include "../defs.h"

inherit CMDBASE;

#define COST 100

reset(arg) {
  if(arg) 
    return;
    
  skill_type = KIN;
  skill_level = 7;
  rank_level = 10;
  atk_flag = 1;
  
}

status main( string str, object jedi, object gob ) {
  object spell;

  if( !force_spell( str, jedi, gob ) )
    return 1;

  this_player()->spell_object(target, "crush", random(18), 0, "");
  write("You tighten the living force that surrounds "+target->query_name()+"'s throat.\n");
  say(jedi->query_name()+" points toward "+target->query_name()+".\n");
  spell = clone_object( "/players/dragnar/Jedi/obj/crush" );
  move_object(spell, this_player());
  spell->set_enemy( target );
  this_player()->add_spell_point( -COST );
  PO->set_force_delay(10);
  return 1;
}
