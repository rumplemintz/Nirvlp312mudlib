#include "../defs.h"

static mapping  cmds, spells;
mixed *PHYS_SKILLS;
mixed *TELE_SKILLS;
mixed *KIN_SKILLS;
mixed *SABER_SKILLS;

int skill_sort( mixed *a, mixed *b ) {
  if( a[1] == b[1] )
    return a[0] > b[0];
  else
    return a[1] > b[1];
}

void
GetActions() {
    int i, skill_rank;
    string *f, cmd;
    string spellfile, skill_type;

    /*
     * Prepare the cmds mapping
     * The commands are bound to the .c files in CMDDIR
     */
    i = sizeof(f = get_dir(CMDDIR + "*.c"));
    if( i < 10 ) 
      write_file(ERROR, ctime(time())+" Sizeof CMDDIR files is: "+i+".\n");

    cmds = ([ ]);
    
    while (i--) {
	sscanf(f[i], "%s.c", cmd);
        cmds += ([ cmd : CMDDIR + cmd ]);
    }

    /*
     * Prepare the spells mapping
     * The spells are bound to the .c files in CMDDIR
     */
    i = sizeof(f = get_dir(SPELLDIR + "*.c"));
    if( i < 10 ) 
      write_file(ERROR, ctime(time())+" Sizeof SPELLDIR files is: "+i+".\n");

    spells = ([ ]);
    PHYS_SKILLS = ({ });
    TELE_SKILLS = ({ });
    KIN_SKILLS = ({ });
    SABER_SKILLS = ({ });
    
    while (i--) {
      sscanf(f[i], "%s.c", cmd);
      spells += ([ cmd : SPELLDIR + cmd ]);

      /** Get lists of the abilities for each skill type **/
      spellfile = SPELLDIR + cmd;
      skill_type = (string) spellfile->query_skill_type();
      skill_rank = (int) spellfile->query_skill_level();
      switch( skill_type ) {
        case PHYS:
          PHYS_SKILLS += ({ ({ cmd, skill_rank }) });
          break;
        case TELE:
          TELE_SKILLS += ({ ({ cmd, skill_rank }) });
          break;
        case KIN:
          KIN_SKILLS += ({ ({ cmd, skill_rank }) });
          break;
        case SABER:
          SABER_SKILLS += ({ ({ cmd, skill_rank }) });
          break;
        default:
          write_file( ERROR, ctime(time())+" invalid skill type found: "+skill_type+"\n");
      }
    }
    PHYS_SKILLS = sort_array( PHYS_SKILLS, "skill_sort", this_object() );
    TELE_SKILLS = sort_array( TELE_SKILLS, "skill_sort", this_object() );
    KIN_SKILLS = sort_array( KIN_SKILLS, "skill_sort", this_object() );
    SABER_SKILLS = sort_array( SABER_SKILLS, "skill_sort", this_object() );
}

mapping
query_cmds() {

  if(!cmds || sizeof(m_indices(cmds)) < 10) 
    GetActions();

  return cmds;
}


mapping
query_spells() {

  if(!spells || sizeof(m_indices(spells)) < 10) 
    GetActions();

  return spells;
}

void
rehash() {
  GetActions();
}

mixed *
query_skills( string skill_type ) {
  if( !PHYS_SKILLS  || sizeof(PHYS_SKILLS) < 1 ||
      !TELE_SKILLS  || sizeof(TELE_SKILLS) < 1 ||
      !KIN_SKILLS   || sizeof(KIN_SKILLS) < 1  ||
      !SABER_SKILLS || sizeof(SABER_SKILLS) < 1 )
    GetActions();

  switch( skill_type ) {
    case PHYS:
      return PHYS_SKILLS;
      break;
    case TELE:
      return TELE_SKILLS;
      break;
    case KIN:
      return KIN_SKILLS;
      break;
    case SABER:
      return SABER_SKILLS;
      break;
    default:
      return SABER_SKILLS;
  }
}

