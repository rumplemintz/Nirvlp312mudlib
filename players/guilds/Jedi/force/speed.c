#include "../defs.h"

inherit CMDBASE;

#define COST SPEED_COST

reset(arg) {
  if(arg) 
    return;
    
  skill_type = PHYS;
  skill_level = SPEED_SKILL;
  rank_level = 10;
  atk_flag = 0;
  
}

status main( string str, object jedi, object gob ) {

  if( gob->query_speed() ) {
    write("You release your control of the force and return to normal speed.\n");
    gob->set_speed( 0 );
    return 1;
  }

  if( !force_spell( str, jedi, gob ) )
    return 1;

  gob->set_speed( gob->query_skill( skill_type ) );
  write("You use the force to enhance your physical strength and reflexes.\n");
  return 1;
}
