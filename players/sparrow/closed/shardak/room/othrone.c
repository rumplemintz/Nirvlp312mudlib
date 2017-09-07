#include "/players/caelin/universal.h"
inherit ROOM;

status Flag_Unlocked;

void set_unlocked(status arg) { Flag_Unlocked = arg; }

reset(arg) {
   if(arg) return;
   set_light(1);
   set_short(RED+"The Master's Waiting Chambers"+NORM);
   set_long("\
 Less a room than an empty chamber, this the Summoning Hall\n\
for the Shardak Master. Only the unpenitent may pass.\n");
add_exit("/players/vertebraker/closed/shardak/room/grotto.c","grotto");
}

okay_follow() { return 1; }
init() {
  ::init();
  add_action("down","down"); }
down() {
  if (Flag_Unlocked) move_object(TP, "/players/tristian/closed/worm_throne/worm_throne");
  else if(TPRN == "worm") { /* SEE SEE the double ==  HUH HUH */
    move_object(TP, "/players/tristian/closed/worm_throne/worm_throne");
    return 1; }
  else write("Ask Worm nicely, scum!\n");
  return 1;
}