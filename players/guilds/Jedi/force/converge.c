#include "../defs.h"

inherit CMDBASE;

reset(arg) {
  if(arg) 
    return;
  name = "Converge";
  description = "Converge the force and your body together in order\n\
                to forge your body into a weapon. Converge requires\n\
                the use of both hands.";
  skill_type = TELE;
  skill_level = CONVERGE_SKILL;
  sp_cost = CONVERGE_COST;
  rank_level = 10;
  atk_flag = 0;
  
}

status main( string str, object jedi, object gob ) {

  if( gob->query_converge() ) {
    write("You break the convergence of force.\n");
    gob->set_converge( 0 );
    jedi->RemoveWeapon( gob );
    return 1;
  }

  if( jedi->query_weapon() ) {
    write("Convergence requires the use of both hands.\n");
    return 1;
  }

  if( !force_spell( str, jedi, gob ) )
    return 1;

  gob->set_converge( 1 );
  jedi->RegisterWeapon( gob );
  write("You close your eyes and converge the force into your body.\n");
  say( jedi->query_name() + " closes "+jedi->query_possessive() +" eyes for a moment.\n" );
  return 1;
}
