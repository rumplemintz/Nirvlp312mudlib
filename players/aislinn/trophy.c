#include "std.h"

object tcase, trophy;
int door_is_open;
object tguard;
 
#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();
 
extra_reset() {
  if(!tguard || !living(tguard)) {
  object bjack, cuffs;
  tguard = clone_object("obj/monster");
  call_other(tguard, "set_name", "Trophy Guard");
  call_other(tguard, "set_alias","guard");
  call_other(tguard, "set_level",15);
  call_other(tguard, "set_hp",550);
  call_other(tguard, "set_wc",12);
  call_other(tguard, "set_ac",12);
  call_other(tguard, "set_al",350);
  call_other(tguard, "set_short","The Trophy Security Guard");
  call_other(tguard, "set_long",
    "A security guard, dressed in the club uniform, stands next to a \n" +
    "trophy case.  He is alert and looks very tough!\n");
  move_object(tguard,this_object());
  bjack = clone_object("obj/weapon");
  call_other(bjack, "set_name","blackjack");
  call_other(bjack, "set_alias","club");
  call_other(bjack, "set_short","A professional blackjack");
  call_other(bjack, "set_long",
    "A professional blackjack.  It is long, sturdy, abit flexible and\n" +
    "looks as if it could inflict severe damage.\n");
  call_other(bjack, "set_class",12);
  call_other(bjack, "set_value",450);
  call_other(bjack, "set_weight",2);
  call_other(bjack, "set_type","weapon");
  transfer(bjack,tguard);
  cuffs = clone_object("obj/treasure");
  call_other(cuffs, "set_id","handcuffs");
  call_other(cuffs, "set_alias","cuffs");
  call_other(cuffs, "set_short","A pair of handcuffs");
  call_other(cuffs, "set_long",
    "A pair of fancy handfcuffs.  They look more ornamental than\n" +
    "functional.\n");
  call_other(cuffs, "set_value",40);
  call_other(cuffs, "set_weight",1);
  transfer(cuffs,tguard);
  }
  door_is_open = 0;
  tcase = present("trophy case",this_object());
  if(!tcase) {
  tcase = clone_object("players/aislinn/objects/trophy_case");
  call_other(tcase, "set_id","A Trophy Case");
  call_other(tcase, "set_alias","case");
  call_other(tcase, "set_short","A trophy case");
  call_other(tcase, "set_long",
    "A handsomely carved, wood and glass trophy case.\n");
  call_other(tcase, "set_value",4000);
  call_other(tcase, "set_weight",400);
  move_object(tcase,this_object());
  trophy = present("crystal trophy",this_object());
  if(!trophy) {
  trophy = clone_object("obj/treasure");
  call_other(trophy, "set_id","crystal trophy");
  call_other(trophy, "set_alias","trophy");
  call_other(trophy, "set_short","The Avalon Tennis Trophy");
  call_other(trophy, "set_long",
    "An exquisite crystal trophy, which looks very valuable and fragile.\n" +
    "A small card in front of it reads:  The All-Avalon Lawn Tennis \n" +
    "Championship.\n");
  call_other(trophy, "set_value",300);
  call_other(trophy, "set_weight",3);
  transfer(trophy,tcase);
  }
  }
}
 
#undef EXTRA_INIT
#ifndef __LDMUD__ /* Rumplemintz */
#define EXTRA_INIT\
  add_action("gt"); add_verb("get");\
  add_action("gt"); add_verb("take");
#else
#define EXTRA_INIT\
  add_action("gt", "get");\
  add_action("gt", "take");
#endif
 
ONE_EXIT("players/aislinn/courts_3n4", "east",
	   "Trophy Alcove",
   "You have entered a small alcove, set back in the west side of the\n" +
   "tennis courts.  An awning, in the club colors and displaying the\n" +
   "crest of Avalon, creates a covering.  A trophy case is directly in\n" +
   "front of you and a chair sits next to it.\n" +
   "   \n", 1)
 
 
gt(str) {
  string b;
  string a;
if (sscanf(str,"%s from %s",a,b)==2) {str = b;}
  if (str == "case" || str == "all" || str == "trophy case") {
    if(tguard && present (tguard,this_object())) {
      write("The guard says: Hands off!\n");return 1;}
   }
}