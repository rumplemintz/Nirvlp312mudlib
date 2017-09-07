#include "../def.h"

cmd_fireblade(str)
{
  object obj, wep, offwep, gob;

  if(TP->query_ghost()) return 0;
  if(TP->query_guild_rank() < 9)
  {
    write("You must master your current skills first.\n");
    return 1;
  }
  if(!str)
  {
    /** Gnar - borrowed this from the code I added to DO for enshroud **/
    wep = this_player()->query_weapon();
    gob = previous_object();
    offwep = gob->query_offwep();
    if( wep && !wep->is_fireblade() ) {
      obj = wep;
    }
    else if( offwep && !offwep->is_fireblade() ) {
      obj = offwep;
    }
  }
  else {
  
    if(!(obj = present(str, TP)))
    {
      write("You don't have \""+str+"\".\n");
      return 1;
    }
    if(!obj->is_weapon())
    {
      write("That is not a weapon!\n");
      return 1;
    }
    if(obj->is_fireblade())
    {
      write("That's already blazing!\n");
      return 1;
    }

  }

  if( !obj )
    return 0;
    
  if(TP->query_sp() < 200)
  {
    write("You need more energy. [200]\n");
    return 1;
  }

  TP->add_sp(-200);
    
  write("You call forth a mighty "+HIY+"lightning bolt"+NORM+".\n");
  say(TP->QN+" calls forth a mighty "+HIY+"lightning bolt"+NORM+".\n");
    
  emit_channel("junk", "(junk) You see "+HIY+"lightning"+NORM+" strike in the distance.\n");
    
  write("You ignite "+obj->query_name()+".\n");
  say(TP->QN+" ignites "+obj->query_name()+".\n");
    
  tell_room(ENV(TP),
    capitalize(obj->query_name())+" explodes into "+HIR+"FLAMES"+NORM+"!\n");
    
  {
    object sh;
      
    sh = clone_object(OBJDIR+"fireblade");
    sh->load_it(obj);
  }
    return 1;
}
