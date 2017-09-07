/*
  welp since i rmed my old one here is the 'cleaner' verison :)   
                                              -wocket 
  to remove the orb from game play .. edit ~/castle.c
  change value of x to 1 in function touch();
*/

#include "/players/wocket/closed/ansi.h"
#define LOGFILE "/players/wocket/closed/log/ORB"
inherit "obj/treasure.c";

int hpcost;
int spcost;
int chargecost;
int charges;

reset(arg){
    set_id("aglowingorb");
    set_alias("orb");
    set_short("An orb"+HIY+" @"+OFF);
    set_long("A glowing orb of swirling light.  This mystic energy source will teleport\n"+
             "you to a various list of 'places'.  You need only 'go' to them.  You may\n"+
             "also 'rip' the orb away destroying it forever.\n");
    set_no_clean(1);
    set_weight(0);
}

drop(){ return 1; }
get(){ return 0; }

init(){
  charges = (5+random(3))*3;
  add_action("places","places");
  add_action("rip","rip");
  add_action("goport","go");
}

places(){
  write("The orb whispers to you: \n");
  write(HIB+"\t\tchurch\n"+NORM);
  write(HIB+"\t\tangel\n"+NORM);
  write(HIB+"\t\twarp\n"+NORM);
  write(HIB+"\t\tshrine\n"+NORM);
  write(HIB+"\t\tchamber\n"+NORM);
  write(HIB+"\t\tvortex\n"+NORM);
  write(HIB+"\t\trift\n"+NORM);
  write("\n\n");
  return 1;
}

rip(string str){
  if(str != "orb"){
    notify_fail("What would you like to rip?\n");
    return 0;
  }
  if(this_player()->query_hp() < 51 || this_player()->query_spell_point() < 51){
    notify_fail("You are not strong enought to rip the orb away.\n");
    return 0;
  }
  this_player()->add_hit_point(-50);
  this_player()->add_spell_point(-50);
  write("You tear at the orb ripping it away from you.  Pain spreads through the wound.\n");
  write(HIY+"The orb shatters.\n"+NORM);
  say(this_player()->query_name()+" rips the orb away.\nThe orb shatters.\n");
  destruct(this_object());
  return 1;
}

goport(str){
int didnt_fail;
object where;
  if(!str || (str != "warp" && str != "angel" && str != "shrine" && str != "chamber" && str != "vortex" && str != "church" && str != "rift") ){
      notify_fail("Usage: go <place>\n");
      return 0;
  }
  if(charges < 1){
    write(HIY+"\nThe orb glimmers and then fades.\n\n"+OFF);
    write_file(LOGFILE,this_player()->query_real_name()+" -orb faded\n");
    destruct(this_object());
    return 1;
  }
  if(environment(this_player())->realm() == "NT"){
    notify_fail("The warping of space prevents you.\n");
    return 0;
  }
  if(environment(this_player())->realm() == "NM"){
    notify_fail("There is not enought energy in the surrounding area to teleport.\n");
    return 0; 
  }
  if(location_okay()){
    where = get_location(str);
    hpcost = random(10);
    spcost = 25;
    chargecost = 1;
    if(cost_check())
      return 1;
    write(HIB+"\nYou touch the orb.\n"+
              "Energy rips through your soul stealing essense.\n"+
              "A mist of blue light surrounds you.\n"+
              "Your surroundings have changed.\n\n"+OFF);
  }
  else{
    where = "obj/base_tele"->teleport();
    if(!where){
      where = get_location(str);
      didnt_fail = 1;
    }
    hpcost = random(10);
    spcost = 25;
    chargecost = 3;
    if(cost_check())
      return 1;
      write(HIY+"\nYou touch the orb.\n"+
                "Energy rips through your soul stealing essense.\n"+
                "A mist of yellow light surrounds you.\n");
      if(didnt_fail == 0)
        write(FLASH+"Confusion and disorientation spreads through your body.\n"+OFF+HIY);          
      write("Your surroundings have changed.\n\n"+OFF);
  }
  say("A mist of light envelopes "+this_player()->query_name()+".\n");
  move_object(this_player(),where);
  write_file(LOGFILE,ctime(time())+"  "+this_player()->query_real_name()+" -moved "+where+" -didnt fail: "+didnt_fail+"\n");
  command("glance",this_player());
  say("A mist of light unfolds and "+this_player()->query_name()+" steps out.\n");
  return 1;
}

cost_check(){
  if(this_player()->query_sp() < spcost || this_player()->query_hp() < hpcost){
    write("You don't have enough energy to teleport.\n");
    return 1;
  }
  this_player()->add_spell_point(-spcost);
  this_player()->add_hit_point(-hpcost);
  charges = charges - chargecost;
}

get_location(str){
object dest;
  switch(str){
    case "church":  return "/room/church.c";
    case "chamber": return "/players/mythos/enterance.c";
    case "rift":    return "/players/saber/ryllian/rift.c";
    case "warp:    return "/players/eurale/RMS/warp.c";
    case "vortex":  return "/players/snow/gate.c";
    case "shrine":  return "/players/feldegast/shrine.c";
    case "angel":   return "/room/south/sforst45.c";
  }
}

location_okay(){
object env;
string filename_env;
  env = environment(this_player());
  filename_env = file_name(env);
  switch(filename_env){
    case "room/church":                return 1; break;
    case "players/saber/ryllian/rift": return 1; break;
    case "players/mythos/enterance":   return 1; break;
    case "players/eurale/RMS/warp": return 1; break;
    case "players/snow/gate":          return 1; break;
    case "room/south/sforst45":        return 1; break;
    case "players/feldegast/shrine":   return 1; break;
    default: return 0;
  }
}