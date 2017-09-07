#include <ansi.h>
#include "../defs.h"
/******************************************************************************
 * Program: quiescent.c
 * Path: /players/dragnar/SevenSpires/scrolls
 * Type: Object
 * Created: June 30th, 2015 by Dragnar
 *
 * Purpose: One of the scrolls in the Seven Spires area that give temporary
 *          powers to a player. This one allows a player to prevent a mob
 *          from running away, for a period of time. 1 use only.
 *
 * History:
 *          06/30/2015 - Dragnar
 *            Created
 *          02/22/2017 - Gnar - Updated to have multiple charges.
 ******************************************************************************/
int charges;

object shad;

id(string str) {
   return str == "scroll" || str == "quiescent" || str == "quiescence" || str == "scroll of quiescence";
}
short() {
	return "A Scroll of "+BLU+"Quiescence"+NORM;
}

long() {
write(YEL+
" ___________________________________\n\
/  _\\                               \\\n\
\\ (_/_______________________________/\n\
 \\                               \\\n\
  \\ "+BLU+"  _                           "+NORM+YEL+"\\\n\
   \\ "+BLU+"/ \\     o  _   _  _  _  ._ _|_"+NORM+YEL+"\\\n\
    \\"+BLU+"\\_X |_| | (/_ _> (_ (/_ | | |_"+NORM+YEL+" \\\n\
     \\  "+HIB+ pad(implode(explode(pad("",charges,'*'),""),"    "),25)+NORM+YEL+"    \\\n\
      \\                               \\\n\
       \\     "+NORM+"This scroll gives the "+YEL+"    \\\n\
      __\\      "+NORM+"bearer the power to "+YEL+"     \\\n\
     / )_\\      "+NORM+"quiescent any foe."+YEL+"       \\\n\
     \\___/_______________________________/\n"+NORM);
}

reset(arg){
  if(arg) return;
  charges = 5;
}

init() {
  add_action("do_quiescent","quiescent");
}

int do_quiescent(string str) {
  object ob, targ;
  string name;

  if( !str ) {
    if( !this_player() || !(targ = (object) this_player()->query_attack()) )
      return 0;
  }
  
  if( !targ && str )
    targ = present(str, environment( this_player() ) );

  if( !targ || !targ->is_npc() ) {
    write("The scroll fails to obey your command.\n");
    return 1;
  }

  name = (string) targ->query_name();

  if( targ->query_quiescent() ) {
    write("A scroll has already been used on "+name+".\n");
    return 1;
  }

  write("You read the ancient words on the scroll and "+name+" stops moving!\n");
  say(this_player()->query_name()+" says some ancient words and the scroll begins to glow.\n");
  shad = clone_object(OBJDIR+"/quiescence_shadow.c");
  shad->set_amount( (int) this_player()->query_attrib("int") * 20 );
  shad->do_shadow( targ );
  charges--;
  if( charges < 1 ) {
    write("The scroll, devoid of power, crumbles to ashes in your hands.\n");
    destruct( this_object() );
  }
  return 1;
}

time_out() {
  if(environment() && environment()->is_player() )
    tell_object( environment(), BLU+"The scroll melts away and evaporates into the air.\n"+NORM);
  if(shad)
    shad->stop_shad();
  destruct(this_object());
}

remove_object() {
  if(shad)
    shad->stop_shad();
  destruct(this_object());
  return 1;
}

locker_arg() {
  return ""+charges;
}

locker_init(str) {
  if(str)
    sscanf(str,"%d",charges);
}

get() { return 1; }
drop() { return 0; }
query_weight() { return 0; }
query_value() { return 0; }
