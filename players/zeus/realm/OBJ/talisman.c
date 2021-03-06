/* 
//  -Forbin 2005.03.07
//  Made the amulet storable.  It's very difficult to get and should be
//  storable.  Shouldn't be a problem when it comes to the quest, as I
//  have stored the variables that the quest checks in it and solving 
//  the quest destroys the amulet, so no worries about people killing
//  for it, then another person solving the quest for pts.  Added code
//  so the enchantment eventually wears off.  Added a long() function 
//  so that players would know when the enchantment is active.
*/

inherit "obj/armor";
#include "/players/zeus/closed/all.h"
int go;
int count; /*  [addition] -Forbin 2005.03.07 enchantment eventually wears off  */     
string gz,goo,gt; /*  [addition] -Forbin 2005.03.04  changed string go to
                  //  goo to avoid conflicts with int go when saving  */
reset(arg){
   if(arg) return;  /* [addition] -Forbin 2005.03.09 was resetting variables and such */
   ::reset();   

  go = 0; 
  set_name("talisman");
  set_short(BOLD+BLK+"An ancient talisman"+NORM);
  set_type("amulet");
  set_ac(1);
  set_weight(1);
  set_value(2000);
}

/* [addition] -Forbin 2005.03.04  added ::id(str) below  */
id(str){ return (::id(str) || str == "talisman" || str == "zeus_quest_talisman"); }

grr(){
  int x;
  for(x = 0; x < 3; x ++)
  {
    if(present("zeus_talisman_piece", environment()))
    {
      if(!gz)
        gz = present("zeus_talisman_piece", environment())->query_creator();
      else if(!go)
        goo = present("zeus_talisman_piece", environment())->query_creator();
      else if(!gt)
        gt = present("zeus_talisman_piece", environment())->query_creator();
      present("zeus_talisman_piece", environment())->fk();
    }
  }
}

/* [addition] -Forbin 2005.03.04  */
long() {
  if(go) 
    long_desc = 
      "This is an ancient talisman.  There are some strange carvings in its\n"+
      "surface which make no sense to you.  As you hold it in your hands,\n"+
      "you can feel a very strong magical force within it.  It glows\n"+
      "faintly with a slight "+RED+"red aura"+NORM+".\n";
  else
    long_desc =
      "This is an ancient talisman.  There are some strange carvings in its\n"+
      "surface which make no sense to you.  As you hold it in your hands,\n"+
      "you can feel a very strong magical force within it.\n";
  ::long();
}
/*  [end addition] -Forbin 2005.03.04  */

void init(){ ::init(); if(environment()) grr(); }

/*  [removed] -Forbin 2005.03.05
query_save_flag(){  return 1; }
*/
set_go(x){ go = x; }
query_go(){ return go; }

/*  [additon] -Forbin 2005.03.05  */
set_gz(arg) { gz = arg;}
set_goo(arg) { goo = arg;}
set_gt(arg) { gt = arg;}
/*  [end addition] -Forbin 2005.03.04  */

query_gz(){ return gz; }
query_goo(){ return goo; }
query_gt(){ return gt; }

do_special(owner) {
  object x;
  if(!owner || !owner->query_attack()) return 1;
  if(!owner->is_player()) return 1;
  if(!go) return 0;
  if(!random(4))
  {
    x = present("circle_object", owner);
    if(x)
    {
      x->add_endurance(1);
    }
  }
  if(owner->query_attrib("ste") > random(60)){
    owner->add_spell_point(3);
    if(!random(4))
    {
      tell_object(owner, 
        "Your talisman glows as it replenishes your power.\n");
    }
  }
/* [addition] -Forbin 2005.03.07  enchantment eventually wears off  */  
  if(count > 50000+random(15000)) {
    tell_object(owner,
      "The "+RED+"red aura "+NORM+"surrounding the talisman fades.\n");
    go = 0;
    count = 0;
    return 0;
  }
  count ++;
  if(!random(5)) return 2; /*  [addition] -Forbin 2005.03.07 bonus ac */
/*  [end addition] -Forbin 2005.03.07  */  
  return 1; 
}

/*  [addition] -Forbin 2005.03.04 to support saving.  */
string locker_arg() { 
  return ""+gz+"&PkP&"+goo+"&PkP&"+gt+"&PkP&"+go+"&PkP&"+count+""; 
}

void locker_init(string arg) { 
  string t1, t2, t3; 
  int t4, t5;
  sscanf(arg, "%s&PkP&%s&PkP&%s&PkP&%d&PkP&%d", t1, t2, t3, t4, t5);
  gz = t1; goo = t2; gt = t3; go = t4; count = t5;
}

status restore_thing(string arg) { 
  restore_object(arg); 
  return 1; 
}

status save_thing(string arg) { 
  save_object(arg); 
  return 1; 
}

status generic_object() { 
  return 1; 
}
/*  [end addition] -Forbin 2005.03.04  */
