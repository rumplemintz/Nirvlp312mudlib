inherit "room/room";
#include <ansi.h>

reset(arg){
  if(arg) return;

  short_desc = "Mob Battle Arena";
  long_desc = "You are in the arena'.\n";
  items=({
	});
  set_light(1);
  dest_dir=({
	});
#if 0
  enable_commands();
#endif
}

init() {
  ::init();
  if(find_call_out("display_health") == -1)
    call_out("display_health", 1);
}

#if 0
catch_tell(str)
{
  tell_room("/players/mosobp/workroom",
    HIY+"~~~"+HIW+"]  "+NORM+str);
}
#endif

display_health()
{
  object play, mmob;
  object *inv;
  int php, mmhp;
  int nlength;
  int s, t;
  inv = all_inventory(this_object());
  s = sizeof(inv);
  for (t = 0; t < s; t++)
  {
        if(inv[t]->is_npc())
        {
          mmob = inv[t];
          break;
        }
  }
  inv -= ({ mmob });
  s = sizeof(inv);
  for (t = 0; t < s; t++)
  {
        if(inv[t]->is_npc())
        {
          play = inv[t];
          break;
        }
  }
  if(!mmob && !play)
  {
    remove_call_out("display_health");
    return;
  }
  if(play)
    php = (play->query_hp() * 100) / play->query_mhp();
  if(mmob)
    mmhp = (mmob->query_hp() * 100) / mmob->query_mhp();
  if(play && mmob)
  {
        nlength = strlen((string)play->query_real_name()) + 2;
        tell_room("/players/mosobp/workroom",
      HIY+"~~"+HIW+"]  "+NORM+
      pad(capitalize((string)play->query_real_name()),nlength)+
      pad(php+"%",4)+HIW+"   ["+HIY+"VS"+HIW+"]   "+NORM);
        nlength = strlen((string)mmob->query_name()) + 2;
    tell_room("/players/mosobp/workroom",
      pad(mmob->query_name(),nlength)+
      pad(mmhp+"%",4)+"\n"+NORM);
  }
  else if(play)
  {
        nlength = strlen((string)play->query_real_name()) + 2;
        tell_room("/players/mosobp/workroom",
      HIY+"~~"+HIW+"]  "+NORM+
      pad(capitalize((string)play->query_real_name()),nlength)+
      pad(php+"%",4)+"\n"+NORM);
  }
  else if(mmob)
  {
        nlength = strlen((string)mmob->query_name()) + 2;
        tell_room("/players/mosobp/workroom",
      HIY+"~~"+HIW+"]  "+NORM+
      pad(capitalize((string)mmob->query_name()),nlength)+
      pad(mmhp+"%",4)+"\n"+NORM);
  }
  call_out("display_health", 2);
  return;
}
