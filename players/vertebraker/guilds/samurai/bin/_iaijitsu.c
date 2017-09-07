#include "../def.h"

cmd_iaijitsu(str)
{
  object atk;
  object wepp;
  object gob;
  
  gob = previous_object();
  if(TP->query_ghost()) return 0;
  if(TP->query_guild_rank() < 8)
  {
    write("You must master your current skills first.\n");
    return 1;
  }
  if(!str)
    atk = TP->query_attack();
  else
    atk = present(str, ENV(TP));
    
  if(!TP->query_weapon()) { 
    write("You are not wielding a weapon!\n");
     return 1; 
 }
  if(!atk)
  {
    write("You must select a target or be in combat.\n");
    return 1;
  }
  
  if(!TP->valid_attack(atk)) return 1;

  if(TP->query_sp() < 40)
  {
    write("You need more energy. [40]\n");
    return 1;
  }
  if(gob->query_beating() || TP->query_spell_dam()) {
    return 1;
  }
  gob->set_beating(1);
  
  TP->add_sp(-40);
  
/*
  if((int)TP->query_attrib("dex") < random(36)) {
     write("\tYou swing your "+TP->query_weapon()->query_name()+" and accidentally cut yourself!\n");
    say(TP->QN+" swings "+possessive(TP)+" "+TP->query_weapon()->query_name()+" and accidentally cuts "+objective(TP)+"self!\n");
    TP->hit_player(TP->query_wc(), "other|vertebraker");
    return 1;
   }
*/
  {
    int dam;
    string *msg;
    object *weps;
    mapping weaps;
    int    s;
    
   if(TP->query_weapon())
    weaps = this_player()->QueryWeapons();
    weps = keys( weaps );
      
    s = sizeof(weps);
    
    while(s--)
    {
      if(!atk || atk->query_ghost())
        continue;
        
      dam += weps[s]->hit(atk);

      if(!atk || atk->query_ghost())
        continue;

      dam += random(weps[s]->weapon_class());
      msg = weps[s]->query_message_hit(dam);
      write("You "+msg[1]+" "+atk->QN+msg[0]+".\n");
      say(TP->QN+" "+msg[1]+" "+atk->QN+msg[0]+".\n");

      if(dam > 40)
        dam = 40;

      /* 08/10/07 Earwax: defensive mode penalty */
      if (gob->query_kamae() == "gedan")
      {
        dam *= 2;
        dam /= 3;
      }
      if (gob->query_kamae() == "chudan")
      {
        dam = (dam * 4) / 5;
      }
      atk->hit_player(dam, "magical");
      
    }
  }
  
   return 1;
}