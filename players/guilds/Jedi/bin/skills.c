#include "../defs.h"
#include <ansi.h>
/******************************************************************************
 * Program: skills.c - Jedi guild
 * Path: /players/guilds/Jedi/bin
 * Type: Command Daemon for Skills
 * Created: Nov 12th, 2015 by Dragnar
 * Description: Shows the skill levels for the player.
 * History:
 *          11/22/2015 - Dragnar
 *          03/03/2017 - Gnar - Total overhaul to make it more flexible.
 ******************************************************************************/

string
get_skill_exp( object gob, string skill, int rank ) {
  int cols;
  string colors, ret;
  
  /** Get the % of progress to the next rank **/
  cols = ((int) gob->query_skill_rank( skill, "exp" ) * 100) / ( (int) LEV->QSkillLevel( rank ) );

  ret = " [";
  switch( cols ) {
    case 0..30:
      ret += HIR;
      break;
    case 31..70:
      ret += HIY;
      break;
    case 71..99:
      ret += HIB;
      break;
    default:
      ret += HIG;
      break;
  }

  /** Adjust to a lenth of 25 **/
  cols = cols * 25 / 100;

  if( cols == 0 )
    cols = 1;

  if( cols > 25 )
    cols = 25;

  ret += pad("", cols, '#') +NORM+ pad( "]", -(26 - cols));
  return ret;
}

main(string str, object caster, object gob) {
  int x, i, lev, rank;
  string type, header;
  mixed *skills;

  /*header = gob->query_wep_color_ansi() + implode(explode(pad("",40,'='),""),"-")+NORM+"\n"; */
  header = gob->query_wep_color_ansi() + pad("",70,'~')+NORM+"\n";
  write( header );
  /** Get the top level skills **/
  for( x=0; x < sizeof(SKILL_TYPES); x++ ) {
    type = SKILL_TYPES[x];
    lev = gob->query_skill( type );
    if( !str || str == type ) {
      write( HIW +pad(capitalize(type) + ": " + lev, -35 - strlen(type+": "+lev)/2) +NORM+"\n");
      write( header );
      skills = ACTIONS->query_skills( type ); 
      /** Get the sub skills **/
      for( i=0; i < sizeof(skills); i++ ) { 
        rank = gob->query_skill_rank( skills[i][0], "rank" );
        write( (skills[i][1] > lev  ? HIK : NORM) + pad(capitalize(skills[i][0]), 12) +": " +rank+NORM+" "+
          get_skill_exp( gob, skills[i][0], rank) + "\n");
      }
      write( header );
    }
  }

  return 1;
}
