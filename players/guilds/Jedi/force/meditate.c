#include "../defs.h"

inherit CMDBASE;

reset(arg) {
  if(arg) 
    return;
  name = "Meditate";
  description = "Concentrate on the force that surrounds your body in\n\
                order to deepen your connection with it. This will\n\
                enhance many of your non-combat jedi skills.";    
  skill_type = TELE;
  skill_level = MEDITATE_SKILL;
  sp_cost = MEDITATE_COST;
  atk_flag = 0;
  
}

status main( string str, object jedi, object gob ) {

  if( gob->query_meditate() ) {
    write("Your focus returns to the here and now and breaks your force meditation.\n");
    gob->set_meditate( 0 );
    return 1;
  }

  if( gob->query_rage() ) {
    write("Your hate and rage give you intense focus and make it impossible to meditate.\n");
    return 1;
  }

  if( !force_spell( str, jedi, gob ) )
    return 1;

  gob->set_meditate( 1 );
  write("You kneel down on one knee, close your eyes and feel the force around you.\n");
  say( jedi->query_name() + " kneels down on one knee and closes "+jedi->query_possessive() +" eyes.\n" );
  return 1;
}
