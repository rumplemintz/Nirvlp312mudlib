#include "../defs.h"
#include <ansi.h>
/******************************************************************************
 * Program: jhelp.c - Jedi guild
 * Path: /players/guilds/Jedi/bin
 * Type: Command Daemon for jhelp
 * Created: Mar 3rd, 2017 by Dragnar
 * Description: Jedi help system
 * History:
 *          03/03/2017 - Gnar - Created
 ******************************************************************************/
void
write_header( string color ) {
  write(color+"["+pad("",70,'~')+"]"+NORM+"\n");
}

main(string str, object caster, object gob) {
  int i, cnt;
  mapping cmds;
  mapping force;
  string file, color;
  string *f;

  color = gob->query_saber_color();
  write( "\n" );
  write_header( color );

  /** Default help doc **/
  if( !str || str == "jedi" ) {
    cat( DOCDIR + "jedi" );
    write_header( color );
    i = sizeof(f = get_dir( DOCDIR ) ); 
    cnt = 1;
    while( i-- ) {
      if( cnt == 1 )
        write("\t");

      write( pad(f[i],15) );
      if( cnt % 4 == 0 ) {
        write( "\n" );
        cnt = 0;
      }
      cnt++;
    }
    if( (cnt - 1) % 4 ) {
      write( "\n" );
    }
    write_header( color );
    return 1;
  }

  cmds = ACTIONS->query_cmds();
  force = ACTIONS->query_spells();

  /** jedi commands **/
  if( member( cmds, str ) ) {
    file = cmds[ str];
  }
  
  /** jedi force spells **/
  if( member( force, str ) ) {
    file = force[ str ];
  }

  /** doc help **/
  if( !file ) {

    file = DOCDIR + str;
    if( file_size(file) > 0 ) {
      cat(file);
      write_header( color );
      return 1;
    } 
    else
      file = 0;
  }


  if( !file ) {
    write("No jedi help found for : "+str+"\n");
    return 1;
  }

  write(color+"  Spell       : " +NORM+file->query_name()+ "\n");
  write(color+"  Skill Type  : " +NORM+capitalize(file->query_skill_type()) +"\n");
  write(color+"  Skill Level : " +NORM+file->query_skill_level() +"\n" );
  write(color+"  Force Cost  : " +NORM+file->query_cost()+"\n");
  write_header( color );
  write(color+"  Description : " +NORM+file->query_description()+ "\n" );
  write_header( color );

  return 1;
}
