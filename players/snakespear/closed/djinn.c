#define LOGPATH "/players/snakespear/log/"
#define OWNER "snakespear"
#include "/players/snakespear/closed/defines.h"
inherit "/obj/monster";

  string log_file;
  string invited;
  object follow;
  int snooping;
  int invis;
  int muffled;
reset(arg) {
  ::reset(arg);
  if(arg) return;
  set_name("A warrior");
  set_alt_name("djinn");
  set_long(
"    A warrior, not only a warrior, but a Djinn Warrior.  Fierce\n"+
"in battle and mighty visionary into the future.\n"
  );
  set_gender("male");
  set_race("terrorist");
  set_level(10);
  set_wc(25);
  set_ac(50);
  set_hp(150);
  snooping=0;
  set_al(0);
  set_heal(50,1);
  set_aggressive(0); 
  enable_commands();
}

catch_tell(str) {
  out_put("~"+str);
}

set_snooping() {
  snooping=!snooping;
  write("Grunt "+(snooping?"on":"off")+"\n");
}
heart_beat() {
  ::heart_beat();
  if(!find_player("snakespear")) destruct(this_object());
}

go_invis() {
  invis=!invis;
}

short() {
  if(invis) return 0;
  else return short_desc;
}
query_invis() {
  return invis;
}
init() {
  add_action("snoop");add_xverb("");
}
snoop(str) {
  if(snooping) {
    out_put("~"+TPN+"~"+str+"\n");
  }
}
set_follow(ob) {
  follow=ob;
  call_out("follow",3);
}
follow() {
  if(follow && !present(follow,environment())) {
    move_object(this_object(),environment(follow));
    out_put("~"+environment()->short()+"\n");
  }
  call_out("follow",3);
}

set_muffle(int x) {
  muffled=!muffled;
  write("You "+(muffled?"ignore":"listen to")+" the raven.\n");
}
set_file(str) {
  if(!str) log_file=0;
  else log_file=str;
}
out_put(str) {
  if(log_file) {
    write_file(LOGPATH+log_file,str);
  }
  if(!muffled) {
    tell_object(find_player(OWNER),str);
  }
}
