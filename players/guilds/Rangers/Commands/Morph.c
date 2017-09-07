#pragma strict_types
#include <ansi.h>
#include "../RangerDefs.h"

void
RangerInit()
{
  object prev_obj;

  prev_obj = previous_object(); 

  if (prev_obj->QuerySkillLevel("morph") > 0)
  {
    prev_obj->AHiddenSkill("unmorph","vital");
  }
  if (prev_obj->QuerySkillLevel("morph") > 30)
  {
    prev_obj->AHiddenSkill("ninja","vital",8);
  }
}

int
QMax() { return 300; }

status
QRangerInfo() { return 1; }

status
RangerInfo()
{
  write("\
---------------   Morph   ---------------\n\
 Power Cost: 10 per skill level \n\n\
 Allows a Ranger to morph and thus use\n\
 additional abilities.\n\
 This skill has a maximum of "+QMax()+"\n\n\
     Initiate:                 0-9\n\
     Dino:                   10-19\n\
     Thunder:                20-29\n\
     " + BOLD + RED + "Ninja" + OFF + ":                  30-39\n\
     Zeo:                    40-49\n\
     Turbo:                  50-59\n\
     Space:                  60-69\n\
     Galaxy:                 70-79\n\
     Rescue:                 80-89\n\
     Lightspeed:             90-99\n\
     Time Force:           100-109\n\
     Wild Force:           110-129\n\
     Ninja Storm:          130-149\n\
     Dino Thunder:         150-169\n\
     S.P.D.:               170-189\n\
     Mystic Force:         190-209\n\
     Operation Overdrive:  210-219\n\
     Jungle Fury:          220-229\n\
     RPM:                  230-239\n\
     Samurai:              240-259\n\
     Megaforce:            260-269\n\
     Super Megaforce:      270-289\n\
     Dino Charge:          290-300\n\n\
Morphing directly affects your combat abilities. Adding points will\n\
increase both offensive and defensive capability.\n\n");
  return 1;
}

status
RangerPower(string str, string type)
{
  int cost;
  int i;
  string title;
  string name;
  string msg;
  object prev_obj;

  prev_obj = previous_object(); 

  if(prev_obj->QMorphed() || prev_obj->QNinja())
  {
    tell_object(this_player(),
      "Zordon tells you: \"You are already Morphed.\"\n");
    return 1;
  }
  if(!(prev_obj->QMorphed()) && !(prev_obj->QNinja()))
  {
    cost = 10 * ((int) prev_obj->QuerySkillLevel("morph"));
    msg = "";
    switch(prev_obj->QuerySkillLevel("morph"))
    {
      case 290..300:
        msg = this_player()->query_name() + " yells: Dino Charge!\n";
        break;
      case 270..289:
        msg = this_player()->query_name() + " yells: Super Mega Mode!\n";
        break;
      case 260..269:
        msg = this_player()->query_name() + " yells: Go Go Megaforce!\n";
        break;
      case 240..259:
        msg = this_player()->query_name() + " yells: Go Go Samurai!\n";
        break;
      case 230..239:
        msg = this_player()->query_name() + " yells: RPM, Get in Gear!\n";
        break;
      case 220..229:
        msg = this_player()->query_name() + " yells: Jungle Beast, Spirit Unleashed!\n";
        break;
      case 210..219:
        msg = this_player()->query_name() + " yells: Overdrive Accelerate!\n";
        break;
      case 190..209:
        msg = this_player()->query_name() + " yells: Mystic Force Resource!\n";
        break;
      case 170..189:
        msg = this_player()->query_name() + " yells: S.P.D. Emergency!\n";
        break;
      case 150..169:
        msg = this_player()->query_name() + " yells: Dino Thunder, Power Up!\n";
        break;
      case 130..149:
        msg = this_player()->query_name() + " yells: Ninja Storm, " +
          prev_obj->COLOR + " Ranger Form!\n";
        break;
      case 110..129:
        msg = this_player()->query_name() +
          " yells: Wild Force\n";
        break;
      case 100..109:
        msg = this_player()->query_name() +
          " yells: Time Force\n";
        break;
      case   90..99:
        msg = this_player()->query_name() +
          " yells: In Need! Lightspeed!\n";
        break;
      case   80..89:
        msg = this_player()->query_name() +
          " yells: Let's Rocket!\n";
        break;
      case   70..79:
        msg = this_player()->query_name() +
          " yells: Transmorph! Galaxy Ranger\n";
        break;
      case   60..69:
        msg = this_player()->query_name() +
          " yells: Astromorph! Space Ranger!\n";
        break;
      case   50..59:
        msg = this_player()->query_name() + " yells: Shift into Turbo!\n";
        break;
      case   40..49: 
        msg = this_player()->query_name() + " yells: Zeo Ranger " + 
          prev_obj->NUMBER+", " + prev_obj->COLOR + "!\n";
        break;
      case   30..39:
        msg = this_player()->query_name() + " yells: " + 
          prev_obj->COLOR + " Ranger Power!\n";
        break;
      case   20..29:
        msg = this_player()->query_name()+" yells: " + prev_obj->DINO + 
          " Ranger Power!\n";
        break;
      case   10..19:
        msg = this_player()->query_name() + " yells: " + 
          prev_obj->DINO + "!\n";
        break;
      default: msg = this_player()->query_name() + 
        " yells: Mighty Morphing Power Rangers!\n";
    }
    if(MASTER->QPowerPoints(type) < cost)
    {
      tell_object(this_player(),
        "Zordon tells you: \"There is not enough power for you to morph.\"\n");
      return 1;
    }
    if(prev_obj->QuerySkillLevel("morph") > 9)
    {
      "obj/user/one_chan.c"->chan_msg("" + 
        "The sky lights up a bright " + prev_obj->COLOR + ".\n" +
        "A bolt of lightning flashes down and strikes at " +
        environment(this_player())->short() + ".\n" +
        "When the smoke clears, the " + prev_obj->QRangerAnsi() +
        prev_obj->COLOR + OFF + " Ranger appears.\n","junk");
    }
    tell_room(environment(this_player()), this_player()->query_name() +
              " yells: It's Morphin' Time!\n" + msg);
    title = (string)this_player()->query_title();
    prev_obj->SOldTitle( title );
    title = (string)this_player()->query_pretitle();
    prev_obj->SOldPretitle( title );
    title = "";
    MASTER->APowerPoints(-cost, type);
    if(COMM->QuerySkillLevel("leadership") >= 20)
    {
      title += "Power Ranger Team Leader: ";
    }
    if(prev_obj->QuerySkillLevel("morph") > 9)
    {
       if(type == "Dark Ranger")
         this_player()->set_title(title+"The Dark "+prev_obj->QRangerAnsi()+
         prev_obj->COLOR+OFF+" Ranger");
       else
         prev_obj->SPlayerShort(title+"The "+prev_obj->QRangerAnsi()+
         prev_obj->COLOR+OFF+" Ranger");
    }
    title = BS;
    for(i=0; i < strlen( (string) this_player()->query_name()); i++)
    {
      title += BS;
    }
    if(this_player()->is_player())
    {
      this_player()->setmin(title + "The " + 
        prev_obj->QRangerAnsi() + prev_obj->COLOR + OFF +
        " Ranger arrives");
      this_player()->setmout(title + "The " +
        prev_obj->QRangerAnsi() + prev_obj->COLOR + OFF +
        " Ranger leaves");
      this_player()->add_player_id("the " + lower_case( (string)
        prev_obj->COLOR) + " ranger");
      this_player()->add_player_id(lower_case( (string) 
        prev_obj->COLOR) + " ranger");
      this_player()->add_player_id("ranger");
    }
    prev_obj->SMorphed();
    prev_obj->AID("player_short_object");
    return 1;
  }
  return 0;
}