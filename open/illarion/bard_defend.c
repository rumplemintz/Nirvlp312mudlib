/*
Created by: Feldegast
Date: 1-1-01
Description:
  A defensive field for the Healer defend spell.  The old defend
spell didn't work with the new armor system.
Stolen By Jaraxle for Bards guild.
Date: 03-15-02
*/

#include "/players/jaraxle/ansi.h"

object target;

int id(string str) {
  return str=="defend_spell";
}

extra_look(){
	return environment()->query_name()+"'s body is distorted by waves of "+HIB+"sound"+NORM;
}

int drop() { return 1; }
int get() { return 0; }

void start(object targ, int ac, int dtime) {
	int time;
    mixed *parms;
	time = dtime;
  target = targ;
  parms = ({ "physical", ac, 0, "do_special" });
  move_object(this_object(),targ);
  targ->RegisterArmor(this_object(), parms);
  call_out("stop", time);
}

void stop() {
  target->RemoveArmor(this_object());
  tell_object(target, HIB+"The distortion field surrounding you dissipates.\n"+NORM);
  destruct(this_object());
}

int do_special(object owner) {
  if(!random(10))
    tell_object(owner, HIB+"The air around you distorts.\n"+NORM);  
  return 0;
}

void remove_object(object ob) {
  target->RemoveArmor(this_object());
}