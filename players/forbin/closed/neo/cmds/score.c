#include "../defs.h"

status main(string str, object gob, object player)
{
  int myweight, carry, i,f,s,t, nextexp, a; 
  string com, con, cre, aa;

  if((int)player->query_ghost()) return 0;
  
  a = (int)player->query_age();
  aa = "";
  if(a/43200) 
  {
    aa += (a/43200 +"d ");
    a = a - (a/43200)*43200;
  }
  if(a/1800) 
  {
    aa+= (a/1800 +"h ");
    a = a  - (a/1800)*1800;
  }
  if(a/30) 
  {
    aa += (a/30 +"m ");
    a = a - (a/30)*30;
  }
  aa += (a*2 +"s.");

  player->recalc_carry();  /* carry code by Snow  *thanx*  */
  carry = (int)player->query_level();
  carry += 6;
  carry += (int)player->query_attrib("str")/5;
  myweight = (int)this_object()->get_my_weight(player);

  nextexp = (int)"/bin/play/_xpnext.c"->query_next_xp("", player); 

  i = (((int)player->query_intoxination() * 100) / ((int)player->query_max_intox()));
  f = (((int)player->query_stuffed() * 100) / ((int)player->query_max_stuff()));
  s = (((int)player->query_soaked() * 100) / ((int)player->query_max_soak()));
  t = (((int)player->query_infuse() * 100) / ((int)player->query_max_infuse()));
  
  com = (string)gob->show_skill_prof("combat");
  con = (string)gob->show_skill_prof("control");
  cre = (string)gob->show_skill_prof("creation");
  
  tell_object(player,
    "\n"+SGC+"<<"+PGC+"==-==-==-==-==-=="+SGC+">> "+HIW+"Neo Symbiotes "+
    SGC+"<<"+PGC+"==-==-==-==-==-=="+SGC+">>"+NORM+"\n");
    
  tell_object(player,
    "   "+player->short()+"\n\n"+
    PGC+"  Level:  "+NORM+(int)player->query_level());
  if((int)player->query_extra_level() > 0)
    tell_object(player, colour_pad("+"+(int)player->query_extra_level(), 10));
  else
    tell_object(player, colour_pad("", 10));
  tell_object(player, 
    PGC+"Experience:  "+NORM+(int)player->query_exp());
  if(nextexp > 0)
    tell_object(player,
      SGC+" ["+NORM+nextexp+SGC+"]"+NORM+"\n");
  else
    tell_object(player, "\n");
  tell_object(player,
    PGC+"  Hp:     "+NORM+colour_pad((int)player->query_hp()+SGC+"/"+NORM+
      (int)player->query_mhp(), 20));   
  tell_object(player,
    PGC+"Gold:  "+NORM+YEL+(int)player->query_money()+NORM+"\n");
  tell_object(player,
    PGC+"  Sp:     "+NORM+colour_pad((int)player->query_sp()+SGC+"/"+NORM+
      (int)player->query_msp(), 12));   
  tell_object(player,
    PGC+"Quest Points:  "+NORM+(int)player->query_quest_point()+"\n");
  tell_object(player,
    PGC+"  Stuff:  "+NORM+colour_pad(f,-3)+SGC+"%          "+PGC+"Age: "+NORM+aa+"\n");
  tell_object(player,
    PGC+"  Soak:   "+NORM+colour_pad(s,-3)+SGC+"%\n");
  tell_object(player,
    PGC+"  Intox:  "+NORM+colour_pad(i,-3)+SGC+"%"+NORM+
    "         You are carrying "+myweight*100/carry+SGC+"%"+
    NORM+" of maximum.\n");
  tell_object(player,
    SGC+"<<"+PGC+"==-==-==--==-==-=="+SGC+">> "+HIW+"Guild Skills "+
    SGC+"<<"+PGC+"==-==-==--==-==-=="+SGC+">>"+NORM+"\n");
  tell_object(player,
    PGC+"                                   Tentacle Assignments\n"+NORM);
  tell_object(player,
    PGC+"   Guild Level: "+NORM+colour_pad(""+CAP((string)gob->print_glevel())+"",19));
  tell_object(player,
      SGC+colour_pad("1",-2)+PGC+" ["+NORM+
      colour_pad(colour_pad(""+CAP((string)gob->query_tents(0,1))+"", -((12+strlen((string)gob->query_tents(0,1))) / 2)), 12)+PGC+"]\n"+NORM); 
  tell_object(player,
    PGC+"   Guild Exp:   "+NORM+colour_pad(""+(int)gob->query_guildexp()+"",19));
  tell_object(player,
    SGC+colour_pad("2",-2)+PGC+" ["+NORM+
    colour_pad(colour_pad(""+CAP((string)gob->query_tents(1,2))+"", -((12+strlen((string)gob->query_tents(1,2))) / 2)), 12)+PGC+"]\n"+NORM); 
  tell_object(player,
    SGC+colour_pad("3",-37)+PGC+" ["+NORM+
    colour_pad(colour_pad(""+CAP((string)gob->query_tents(2,3))+"", -((12+strlen((string)gob->query_tents(2,3))) / 2)), 12)+PGC+"]\n"+NORM); 
  tell_object(player,
    PGC+"   Combat:    "+NORM+colour_pad(""+(int)gob->query_skill("combat")+"",1)+
    SGC+" ["+NORM+colour_pad(com,-3)+SGC+"]              ");  
  tell_object(player,
    SGC+colour_pad("4",-2)+PGC+" ["+NORM+
    colour_pad(colour_pad(""+CAP((string)gob->query_tents(3,4))+"", -((12+strlen((string)gob->query_tents(3,4))) / 2)), 12)+PGC+"]\n"+NORM); 
  tell_object(player,
    PGC+"   Control:   "+NORM+colour_pad(""+(int)gob->query_skill("control")+"",1)+
    SGC+" ["+NORM+colour_pad(con,-3)+SGC+"]              "); 
  tell_object(player,
    SGC+colour_pad("5",-2)+PGC+" ["+NORM+
    colour_pad(colour_pad(""+CAP((string)gob->query_tents(4,5))+"", -((12+strlen((string)gob->query_tents(4,5))) / 2)), 12)+PGC+"]\n"+NORM); 
  tell_object(player,
    PGC+"   Creation:  "+NORM+colour_pad(""+(int)gob->query_skill("creation")+"",1)+
    SGC+" ["+NORM+colour_pad(cre,-3)+SGC+"]              ");
  tell_object(player,
    SGC+colour_pad("6",-2)+PGC+" ["+NORM+
    colour_pad(colour_pad(""+CAP((string)gob->query_tents(5,6))+"", -((12+strlen((string)gob->query_tents(5,6))) / 2)), 12)+PGC+"]\n"+NORM); 
  tell_object(player,
    SGC+colour_pad("7",-37)+PGC+" ["+NORM+
    colour_pad(colour_pad(""+CAP((string)gob->query_tents(6,7))+"", -((12+strlen((string)gob->query_tents(6,7))) / 2)), 12)+PGC+"]\n"+NORM); 
  tell_object(player,
    "      "+PGC+"Dark Matter Pool"+NORM+"             ");
  tell_object(player,
    SGC+colour_pad("8",-2)+PGC+" ["+NORM+
    colour_pad(colour_pad(""+CAP((string)gob->query_tents(7,8))+"", -((12+strlen((string)gob->query_tents(7,8))) / 2)), 12)+PGC+"]\n"+NORM); 
  tell_object(player,
    SGC+"   ["+HIW+colour_pad((string)gob->show_mp()+"",20)+SGC+"]          ");
  tell_object(player,
    SGC+colour_pad("9",-2)+PGC+" ["+NORM+
    colour_pad(colour_pad(""+CAP((string)gob->query_tents(8,9))+"", -((12+strlen((string)gob->query_tents(8,9))) / 2)), 12)+PGC+"]\n"+NORM); 
  tell_object(player,
    SGC+colour_pad("10",-37)+PGC+" ["+NORM+
    colour_pad(colour_pad(""+CAP((string)gob->query_tents(9,10))+"", -((12+strlen((string)gob->query_tents(9,10))) / 2)), 12)+PGC+"]\n"+NORM); 
  tell_object(player,
    SGC+"<<"+PGC+"==-==-==-==-==-==-==-=="+SGC+">> "+HIW+"* "+
    SGC+"<<"+PGC+"==-==-==-==-==-==-==-=="+SGC+">>"+NORM+"\n");    
  return 1;
}

int get_my_weight(object ob) /* Code by Snow  *thanx*  */
{    
  int total;
  object one;
  if(!ob) return 1;
  one = first_inventory(ob);
  while(one)
  {
    total += (int)one->query_weight();
    one = next_inventory(one); 
  }
  return total;
}

