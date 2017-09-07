/************************************************************************
*  The Power Ranger Guild Weapon                                        *
*  Created by Beck/Russ Warren for Nirvana                              * 
*  Updated by vital/keith for the Rangers                               *
*  Last changed 2005.10.13                                              *
*************************************************************************/
#pragma strict_types

#include "../RangerDefs.h"
#include <ansi.h>

static status wielded;
static object wielded_by;
static int broke;
static int eff_wc;
static int misses,hits;
static int save_flag, class_of_weapon;
static object hit_func;
static string type;
static string *message_hit;
static object PrevWeapon;
static int damagetmp;

int
weapon_class() { return class_of_weapon; }

mixed
hit(object attacker)
{
  if(hit_func)
    return call_other(hit_func,"weapon_hit",attacker);
  return 0;
}

void
set_class(int c) { class_of_weapon = c; }

void
un_wield() { call_out("re_wield",2); }

void
re_wield()
{ 
  PrevWeapon = 0;
  environment(this_object())->wield(this_object(),1);
}

status
weapon_breaks()
{
  if(broke) return 1;
  return 1;
}

status
count_misses()
{
  misses += 1;
  return 1;
}

status
count_hit_made(int w)
{
  hits += 1;
  eff_wc=((hits-1)*eff_wc + w)/hits;
  return 1;
}

status
query_wear() { return 0; }

void
add_wear(int arg)
{
  misses = 0;
  hits = 0;
}

status
fix_weapon()
{
  if(!broke) return 0;
  broke = 0;
  return 1;
}

status
re_break()
{
  broke = 1;
  return 1;
}

status
query_broke() { return broke; }

object
SPrevWeapon(object ob) { PrevWeapon = ob; }

object
PrevWeapon() { return PrevWeapon; }

status
query_pro_weapon(){ return 1;}

int
proficiency_hit(object ob)
{
  int enemyhp, enemymhp, enemyper;
  int damage;
  int damage2;
  int temp;
  int i;
  int result;
  string name, attacker;
  string skill; string msg;
  mixed *skills;
  string *offskills;
  if(!environment(this_object()) || /* checks by verte 6.6.01 */
    !environment(this_object())->query_attack()) return 0;
  hits = 0;misses = 0;
  damage = (1);
  damage2 = 0;
  name = (string) environment(this_object())->query_name();
  attacker =
    (string) (environment(this_object())->query_attack())->query_name();
  if(this_object()->QMorphed())
  {
    temp = (int) this_object()->QuerySkillLevel("morph");
    for(i=1; i < temp; i++)
    {
      damage += 2;
      result += 1;
      temp -= i;
    }
  }
  if(this_object()->QNinja())
  {
    temp = (int) this_object()->QuerySkillLevel("morph");
    for(i=1; i < temp; i++)
    {
      damage += 2;
      result += 1;
      temp -= i;
    }
  }
  offskills = (array) this_object()->QOffSkills();
  for(i=0; i < sizeof(offskills); i++)
  {
    damage += (int) ("/players/guilds/Rangers/Commands/" + capitalize(offskills[i]) +
      ".c")->OffSkill(1); /* OffSkill passed 1, as value is discarded */
  }
  if(damage < 0) damage = 0;
  if(damage > 100) damage = 90;
  damage2 = damage / 3;
  damage -= damage2;
  damagetmp = damage2;
  environment(this_object())->set_spell_dam(damage2); 
  if(damage+damage2 > 100) damage = 100-damage2;
  return damage;
}

string *
query_message_hit(int tmp)
{
  string *mess;
  tmp += damagetmp;
  mess = ({" into ashes", BLINK+BOLD+RED+"<<< E V I S C E R A T E D >>>"+OFF });
  if (tmp < 37) { mess = ({" into ashes", BLINK+BOLD+RED+"<<< E V I S C E R A T E D >>>"+OFF }); }
  if (tmp < 35) { mess = ({" with hurricane force",BLINK+RED+"DISEMBOWELED"+OFF}); }
  if (tmp < 32) { mess = ({" with deadly precision",BOLD+RED+"GORED"+OFF}); }
  if (tmp < 29) { mess = ({" to small fragments","massacre"}); }
  if (tmp < 25) { mess = ({" with a bone crushing sound","smashed"}); }
  if (tmp < 22) { mess = ({"","laid the "+GREEN+"Smack"+OFF+" down on"}); }
  if (tmp < 19) { mess = ({" very hard","hit"}); }
  if (tmp < 16) { mess = ({" with reckless abandon","went off on"}); }
  if (tmp < 13) { 
     mess = ({" with a brilliant display of martial arts","stunned"}); }
  if (tmp < 10) { mess = ({"","hit"}); }
  if (tmp < 5) { mess = ({"","beat up"});}
  if (tmp < 3) { mess = ({" with a weak attack","grazed"}); }
  if (tmp == 1) { mess = ({" in the stomach","tickled"});}
  return mess;
}


status
check_ranger_kill(string str)
{
  object ob;
  if(!str) return 0;
  if(!this_player()) return 0;
  if(!environment(this_player())) return 0;
  ob = present(str, environment(this_player()));
  if(!ob){ return 0; }
  if( (string) this_object()->QRangerAlign() == "Power Ranger")
  {
    if(this_object()->QMorphed() || this_object()->QNinja())
    {
      if(!ob->is_player() && ob->query_alignment() > 10)
      {
        write("You can not bring yourself to attack that riteous being.\n");
        return 1;
      }
    }
    if(ob->RangerNPC())
    {
      write("Zordon tells you: You better not kill fellow Power Rangers!!!\n");
      return 1;
    }
  }
  return 0;
}
