#include "/players/mythos/closed/guild/def.h"
#include "/obj/clean.c"

static status wielded;
static object wielded_by;
static string cap_name;
static int eff_wc, misses, hits, n, once;
static int orgatac, orgatwc;
static object orgatob;
string name_of_weapon, alt_name, alias_name, short_desc;
string long_desc, read_msg, info;
object hit_func, wield_func;
int save_flag, class_of_weapon, value, local_weight;
int storage;            /*amount of sp used to create this*/
string owner;           /*making weapon have owner- creator */
int slay, vampire, life, soul_steal, sharp, dancing, berserk;
int speed, wounding, spell, norm, ego, dance_count;
string type_s, path;
static object prev;

reset(arg) {
    if (arg)
     return;
     prev = 0;
    wielded = 0; value = 0; slay = 0; vampire = 0; life = 0; soul_steal = 0;
    sharp = 0; dancing = 0; berserk = 0; speed = 0; wounding = 0; spell = 0;
    norm = 0; once = 0; n = 0; ego = 0; dance_count = 0; long_desc = "";
    orgatwc = 0; orgatac = 0; orgatob = 0;
    call_out("wliving",100); 
}

id(str) {
  return str == name_of_weapon || str == alt_name || str == alias_name;}

short() {
   string tmp_short;
    if (call_other(this_player(), "query_level", 0) > 30) {
      tmp_short = short_desc + "  < wc " + class_of_weapon + 
      ","+eff_wc + " >";
      if (wielded)
         return tmp_short + " (wielded)";
      return tmp_short;}
    if (wielded)
        if(short_desc) 
          return short_desc + " (wielded)";
return short_desc;}

long() {
   int wear;
    write(call_other(clone_object("/"+path+".c"),"long",0));
    write(long_desc);
    write("It is like new.\n");
   if(this_player()->query_level() > 100) { write("Wear = Does not wear down.\n");
    write("Hits = "+hits+"    Misses = "+misses+"\n");
   }
}

init() {
 this_player()->zap_object(this_player());
  destruct(this_object());
return 1;
  if(living(ep) && epn != name_of_weapon &&
    epn != owner) { write("When you touch the weapon, the air seems to turn cold...\n");
                    write("You feel "+HIB+"COLD DEATH"+NORM+" pass by....\n");
                    tp->add_hit_point(-3);
                 say(capitalize(tpn)+" drops "+short_desc+"!\n");
                    write("You quickly drop the weapon!\n");
                    move_object(this_object(),environment(tp)); return 1;}
    add_action("wield"); add_verb("wield");
    add_action("stopwield"); add_verb("unwield");
    add_action("dgive","give");
    if (read_msg) { add_action("read","read");}
    if(dancing) { add_action("sword_dance","sword_dance"); }
}

dgive(str) {
string what, who;
  if(sscanf(str,"%s to %s",what,who) && (what == name_of_weapon ||
    what == alt_name ||  what == alias_name)) {
    write("You may not do that.\n"); return 1;}
}

wield(str) {
    if (!id(str))
        return 0;
    if (environment() != this_player()) {
        return 0;
    }
    if (wielded) {
        write("You already wield it!\n");
        return 1;
    }
    if(wield_func)
        if(!call_other(wield_func,"wield",this_object()))
            return 1;
    wielded_by = this_player();
    call_other(this_player(), "wield", this_object());
    wielded = 1;
return 1;}

un_wield() {
    if (wielded)
        wielded = 0;
wielded_by = 0;}

stopwield() {
   call_other(this_player(), "stop_wielding");
wielded = 0;
wielded_by = 0;
return 1;}

get() { return 1; }

drop(silently) {
    if (wielded) {
        call_other(wielded_by, "stop_wielding");
        wielded = 0;
        if (!silently)
            write("You drop your wielded weapon.\n");
    }
return 0;}

read(str) {
    if (!id(str))
        return 0;
    write(call_other(clone_object("/"+path+".c"),"read",alias_name));
    write(read_msg);
return 1;}

save_thing(str){
     save_object(str);
return 1;}
  
restore_thing(str){
      restore_object(str);
return 1;}
   
count_misses() {
   misses += 1;
return 1;}
 
count_hit_made(w) {
   hits += 1;
   eff_wc=((hits-1)*eff_wc + w)/hits;
return 1;}
   
set_id(n) {
    name_of_weapon = n;
    cap_name = capitalize(n);
    short_desc = cap_name;
long_desc = "You see nothing special.\n";}

set_name(n) {
    name_of_weapon = n;
    cap_name = capitalize(n);
    short_desc = cap_name;
long_desc = "You see nothing special.\n";}

set_class(c) { class_of_weapon = c; }

set_weight(w) { local_weight = w; }

set_value(v) { value = v; }

set_alt_name(n) { alt_name = n; }

set_hit_func(ob) { hit_func = ob; }

set_wield_func(ob) { wield_func = ob; }

set_alias(n) { alias_name = n; }

set_short(sh) { short_desc = sh; long_desc = short_desc + "\n";}

set_long(long) { long_desc = long; }

set_read(str) { read_msg = str; }

set_storage(s) {storage = s;}

set_info(i) { info = i;} 

set_owner(str) { owner=str;}

set_slaying(str) { slay = 1; type_s = str; norm = 1;
                long_desc = long_desc + HIR+"Slayer of "+capitalize(type_s)+NORM+"\n";}

set_vampire() { vampire = 1; norm = 1;
                long_desc = long_desc + BOLD+"Vampiric\n"+NORM;}

set_steal() { soul_steal = 1; norm = 1;
                long_desc = long_desc + HIR+"Soul Stealer\n"+NORM;}

set_life(li) { life = 1; norm = 1; ego = li;}

set_sharp() { sharp = 1; norm = 1;
                long_desc = long_desc + BOLD+"Sharpness\n"+NORM;}

set_berserk() { berserk = 1; norm = 1;
                long_desc = long_desc + BOLD+"Berserker\n"+NORM;}

set_dance() { dancing = 1; norm = 1; dance_count = 0;
                long_desc = long_desc + HIB+"Dancing\n"+NORM;}

set_speed() { speed = 1; norm = 1;
                long_desc = long_desc + BOLD+"Speed\n"+NORM;}

set_wound() { wounding = 1; norm = 1;
                long_desc = long_desc + BOLD+"Paralyzing\n"+NORM;}

set_spell() { spell = 1; norm = 1;
                long_desc = long_desc + BOLD+"Spell Cleaver\n"+NORM;}

set_count(dc) { dance_count = dc; }

set_path(str) { path = str; }

query_info() { return info; }

query_path() { return path; }

query_wear() { return 1;}

query_name() { return name_of_weapon; } 

query_weight() { return local_weight; } 

query_save_flag() { return 1; }

query_gsave() { return 1;}

query_value() { return value;}

namer() { return "cold";}

weapon_class() { return class_of_weapon;} 

hit(attacker) {
if(!orgatob) {
  orgatob = attacker;
  orgatwc = 0;
  orgatac = 0;
}
if(orgatob != attacker) {
   if(orgatwc) orgatob->set_wc(orgatwc);
   if(orgatac) orgatob->set_ac(orgatac);
   orgatob = attacker;
   orgatwc = 0;
   orgatac = 0;
}
if(prev != attacker && !(attacker->query_soul()) && !present("adds",attacker)) {
  object harmer;
  harmer = clone_object("/players/mythos/closed/guild/spells/prev.c");
  harmer->start_heal_shadow(attacker);
}
  if(!norm && random(3)==0) { 
  tell_object(attacker,CYN+"        *****   COLD FIRE   *****\n"+NORM);
  write("Your weapon flares!\n");
  tell_room(environment(this_player()),"Cold Fire engulfs the ENEMY!\n");
  return (qtf/3);}   
  if(soul_steal && attacker) { 
                    if(attacker->query_hp() < qtf+1) {     /* if soul_steal is set */
                    int la, much;                          /* so is life... check wliving */
                    string las, lass;
                    la = random(10);
                    much = attacker->query_level();
                    tell_room(environment(tp),capitalize(tpn)+" summons "+
                    HIC+"lightning"+NORM+" from the sky!\n");
                    if(random(5) == 0) {
                    /*
                    if (la == 8 || la == 9) {
                    if((present(fear,tp)->query_fae()) < 20) { 
                      present(fear,tp)->raise_fae(1);}
                    }
                    if (la == 7) { las = "strength"; lass = "str"; }
                    if (la == 6) { las = "will_power"; lass = "wil"; }
                    if (la == 5) { las = "magic_aptitude"; lass = "mag"; }
                    if (la == 4) { las = "piety"; lass = "pie"; }
                    if (la == 3) { las = "stamina"; lass = "sta"; }
                    if (la == 2) { las = "stealth"; lass = "ste"; }
                    if (la == 1) { las = "luck"; lass = "luc"; }
                    if (la == 0) { las = "intelligence"; lass = "int"; }
                    if (call_other(tp, "query_attrib", lass) < 20) {
                    call_other(tp, "raise_" + las, 1); }
                    else { tp->heal_self(much * 10); }
                    */
                    tp->heal_self(much * 3);
                    if(!orgatac) orgatac = attacker->query_ac();
                    if(orgatac/2 < attacker->query_ac())
                    attacker->set_ac(attacker->query_ac()*3/4);
                    write(BOLD+"You feed upon the soul of your enemy!\n"+NORM); }
                    return 30;} 
                  }
                  
  if(slay && attacker && random(3)==0) { if(attacker->id(type_s)) {
    write("The weapon quivers as you hit its foe!\n");
    tell_room(environment(this_player()),BLU+
    "\n            F  L  A  R  E\n\n"+NORM);
      if(attacker->query_hp() > qtf/2) attacker->heal_self(-qtf/2); }
            }
  if(vampire && attacker && random(3)==0) { 
    if(attacker->query_hp() > qtf/4) {
    if(!(attacker->query_soul()))
       attacker->heal_self(-qtf/4);
    }
                tp->heal_self(qtf/4);
       tell_room(environment(this_player()),
       "There is a sudden wrenching in the space of reality!\n");
       write("You feel invigorated!\n");}
  if(berserk && attacker && random(3)==0) { 
             if(tp->query_hp() < (tp->query_mhp())/3 && tp->query_wc() < 22) {
                tp->set_wc(tp->query_wc() + 1); 
                write("You feel stronger as "+HIR+"RAGE"+NORM+" fills you!\n");
                tell_room(environment(tp),capitalize(tpn)+
                " goes berserk!  Motions are ablur!\n"); } 
                if(tp->query_hp() > (tp->query_mhp())*5/12 && 
                   tp->query_wc() > class_of_weapon) {
                   write(BLU+"Your berserk rage cools...\n"+NORM);
                tp->set_wc(class_of_weapon);} }
  if(dancing && attacker && random(3)==0) { 
  tell_object(attacker,CYN+"        *****   COLD FIRE   *****\n"+NORM);
  write("Your weapon flares!\n");
  tell_room(environment(this_player()),"Cold Fire engulfs the ENEMY!\n"); 
  if(attacker->query_hp() > 7) {
  if(!(attacker->query_soul()))
       attacker->heal_self(-random(7));
    }}
  if(wounding && attacker && random(3)==0) { attacker->set_heal(0,10000);}
  if(spell && attacker && random(3)==0) { 
  write("The enemy's magic is diminished!\n");
  say(BOLD+"\nDARKNESS floods the room!\n\n"+NORM);
  if(attacker->query_hp() > qtf) {
   if(!(attacker->query_soul()))
     attacker->heal_self(-random(qtf/2));} }
  if(speed && attacker && random(3)==0 && n == 0) { 
  if( attacker->query_hp() > 20) {
  switch(random(3)) {
  case 0:  n = 1;
           tell_room(environment(tp),"The "+short()+" flares!\nThe motions of "+
            capitalize(tpn)+" are ablur!\n");
            if(!attacker || attacker->query_hp() < 20) { n = 0; return 0; break; }
             hit(attacker); 
             if(!attacker || attacker->query_hp() < 20) { n = 0; return 0; break; }
             tp->attack(); 
             if(!attacker || attacker->query_hp() < 20) { n = 0; return 0; break; }
  case 1: n = 1; 
           tell_room(environment(tp),"The "+short()+" flares!\nThe motions of "+
            capitalize(tpn)+" are ablur!\n");
            if(!attacker || attacker->query_hp() < 20) { n = 0; return 0; break; }
            hit(attacker); 
            if(!attacker || attacker->query_hp() < 20) { n = 0; return 0; break; }
            tp->attack();
            if(!attacker || attacker->query_hp() < 20) { n = 0; return 0; break; }
  case 2: n = 1; 
            tell_room(environment(tp),"The "+short()+" flares!\nThe motions of "+
             capitalize(tpn)+" are ablur!\n");
             if(!attacker || attacker->query_hp() < 20) { n = 0; return 0; break; }
             hit(attacker); 
             if(!attacker || attacker->query_hp() < 20) { n = 0; return 0; break; }
             tp->attack();
           n = 0; break;
  } }
            }
  if(sharp && attacker && random(10)==0) { 
              if(attacker->query_wc() > 13 && !(attacker->query_soul())) { 
              if(!orgatwc) orgatwc = attacker->query_wc();
              attacker->set_wc(attacker->query_wc()*2/3);
              write("You slice through the enemy's weapons!\n");} 
            }
return 0;}

weapon_breaks(){
object ob, cm;
int burst;
burst=storage/50;
if(random(3) > 0) { tell_object(ep,"The "+short_desc+" almost breaks!\n"); return 1;}
if(living(ep)) { cm = environment(ep); 
                 tell_object(ep,"Your WEAPON SHATTERS!!!!!\n");
                 ep->heal_self(-burst);}
else { cm = environment(this_object()); }
    tell_room(cm,BOLD+"\nSUDDENLY,\n\n"+NORM+HIC+
              "\tThere is a brilliant flash!\n\n\t\tCOLD FIRE is everywhere!\n\n"+NORM);
     ob=first_inventory(cm);
  while(ob) {
    if(living(ob) && (0==random(2))) {
      ob->heal_self(-random(burst));
      }
      ob = next_inventory(ob);}
      destruct(this_object());
return 1;} 

wliving() {
if(life && ep) {
  if(living(ep) && ep->query_real_name() == owner && 
     ego > ep->query_attrib("wil")) { weapon_breaks(); return 1;}
   if(living(ep)) {
   tell_object(ep,"Deep in your soul you feel a sudden chill....\n");
   ep->add_spell_point(-3-random(10));
   }
  if(dance_count > 0) { dance_count = dance_count - 1;} }
  call_out("wliving",500+random(1000));
return 1;}

sword_dance() { 
object dance_wep, con;
if(wielded) { write("You must unwield first!\n"); return 1;}
if(dance_count > 0) { write("You must let the weapon rest!\n"); return 1;}
  dance_wep = clone_object("/players/mythos/closed/guild/spells/dancer.c");
  dance_wep->set_name(name_of_weapon);
  dance_wep->set_level(tl);
  dance_wep->set_short(short_desc);
  dance_wep->set_long(long_desc);
  dance_wep->set_wc(class_of_weapon);
  dance_wep->set_owner(owner);
  dance_wep->set_ac(class_of_weapon/2);
  dance_wep->set_hp(tp->query_mhp());
  move_object(dance_wep,environment(tp));
  move_object(this_object(),dance_wep);
  con = clone_object("/players/mythos/closed/guild/spells/wepcon.c");
  con->set_con(dance_wep);
  move_object(con,tp);
  command("look at control",tp);
return 1; }

cleanup() { fix_weapon(); misses = 0; hits = 0; }

fix_weapon() { return 1;}
