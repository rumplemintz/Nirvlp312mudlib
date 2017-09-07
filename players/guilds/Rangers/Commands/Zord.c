#pragma strict_types
#include <ansi.h>
#include "../RangerDefs.h"

string *Owners;

int reset_ownership(int OwnerNumber);
string query_zord_call(object owner);
string query_zord_msg(object owner);

status
RangerPower(string str, string type)
{
  string msg, shortmsg, rtype;
  object pet, prev_obj;

  prev_obj = previous_object();

  if(!prev_obj->QMorphed())
  {
    if(prev_obj->QNinja())
    {
      tell_object(this_player(),
        "Zordon tells you: \"You cannot use a Zord as a Ninja.\"\n");
      return 1;
    }
    tell_object(this_player(),
      "Zordon tells you: \"You must be morphed to summon your Battlezord.\"\n");
    return 1;
  }
  if(!Owners)  Owners = ({});
  if(member_array(this_player()->query_real_name() +
    prev_obj->QRandomNumber(), Owners) != -1)
  {
    tell_object(this_player(),
      "Zordon tells you: \"You already have summoned your Battlezord.\"\n");
    return 1;
  }
  if(!present("ViewingGlobe",environment(this_player())))
  {
    if(MASTER->QPowerPoints(type) <
      ( 200 + (60 * ((int)prev_obj->QuerySkillLevel("machine")) ) ) )
    {
      tell_object(this_player(),
        "Zordon tells you: \"There is not enough Power to use.\"\n");
      return 1;
    }
  }
  if(MASTER->QPowerPoints(type) <
    (100 + (30 * ((int)prev_obj->QuerySkillLevel("machine")) ) ) )
  {
    tell_object(this_player(),
      "Zordon tells you: \"There is not enough Power to use.\"\n");
    return 1;
  }
  rtype = (string) prev_obj->query_ranger_type();
  msg = query_zord_call(prev_obj);
  shortmsg = query_zord_msg(prev_obj);
  tell_room(environment(this_player()), this_player()->query_name() + 
    " yells: "+msg+"\n");
  pet = clone_object("/players/guilds/Rangers/RangerZord.c");
  pet->set_level(prev_obj->QuerySkillLevel("machine"));
  pet->set_hp(1 + (20 * ((int) prev_obj->QuerySkillLevel("machine"))));
  pet->set_short("A " + shortmsg);
  pet->set_Owner(this_player());
  pet->set_OwnerName(this_player()->query_real_name());
  pet->set_OwnerNumber(this_player()->query_real_name() +
    prev_obj->QRandomNumber());
  if(this_player()->RangerNPC())
  {
    pet->set_OwnerName(this_player()->query_name());
  }
  pet->set_wc(prev_obj->QuerySkillLevel("machine"));
  pet->set_ac(2 +
    (random((int)prev_obj->QuerySkillLevel("machine") / 2)));
  pet->set_alt_name(prev_obj->COLOR + "Zord");
  pet->set_message(shortmsg);
  move_object(pet, environment(this_player()));
  MASTER->APowerPoints( - (100 + 30 * 
    ((int)prev_obj->QuerySkillLevel("machine"))), type);
  if(!present("ViewingGlobe",environment(this_player())))
  {
    MASTER->APowerPoints( - (100 + 30 * 
      ((int)prev_obj->QuerySkillLevel("machine"))), type);
  }
  Owners += ({ this_player()->query_real_name() +
    prev_obj->QRandomNumber() });
  tell_room(environment(this_player()),"A " + shortmsg + " arrives.\n");
  return 1;
}

status
QRangerInfo() { return 1; }

status
RangerInfo(string str)
{
  write("\
  Your Zord is your most trusted companion.  The Zord assists you\n\
in combat automatically.  Statistics (Hp, Ac, Wc) and  cost of \n\
calling your Zord depend on your skill level in Machine.\n\n");
  return 1;
}


int
reset_ownership(int OwnerNumber)
{
  if(!Owners) return 0;
  if(member_array(OwnerNumber, Owners) != -1)
  {
    Owners -= ({ OwnerNumber });
    return 1;
  }
}

string
query_zord_call(object owner)
{
  string rtype, temp_msg, temp_dino, temp_animal;
  rtype = (string) owner->query_ranger_type();
  temp_dino = (string) owner->DINO;
  temp_animal = (string) owner->ANIMAL;
  switch(owner->QuerySkillLevel("morph"))
  {
    case 0..9:
      temp_msg = "Zord Power";
      break;
    case 10..19:
      temp_msg = temp_dino + " " + rtype + "zord Power";
      break;
    case 20..49:
      temp_msg = temp_animal + " " + rtype + "Thunderzord Power";
      break;
    case 50..149:
      temp_msg = temp_animal + " " + rtype + "-zord Power";
      break;
    case 150..169:
      temp_msg = temp_dino + " " + rtype + "-zord Power";
      break;
    case 170..200:
      temp_msg = temp_animal + " " + rtype + "-zord Power";
      break;
    default: temp_msg = "Zord Power";
  }
  return temp_msg;
}

string
query_zord_msg(object owner)
{
  string rtype, temp_msg, temp_dino, temp_animal;
  rtype = (string) owner->query_ranger_type();
  temp_dino = (string) owner->DINO;
  temp_animal = (string) owner->ANIMAL;
  switch(owner->QuerySkillLevel("morph"))
  {
    case 0..9:
      temp_msg = "Zord ";
      break;
    case 10..19:
      temp_msg = temp_dino + " " + rtype + "zord";
      break;
    case 20..49:
      temp_msg = temp_animal + " " + rtype + "Thunderzord";
      break;
    case 50..149:
      temp_msg = temp_animal + " " + rtype + "-zord";
      break;
    case 150..169:
      temp_msg = temp_dino + " " + rtype + "-zord";
      break;
    case 170..200:
      temp_msg = temp_animal + " " + rtype + "-zord";
      break;
    case 201..249:
      temp_msg = temp_animal + " " + rtype + "-zord";
      break;
    case 250..300:
      temp_msg = temp_dino + " " + rtype + "-zord";
      break;
    default: temp_msg = "Zord";
  }
  return temp_msg;
}