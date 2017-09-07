/*                                                                            *
 *      File:             /players/angel/area/mansion/mayor_ray.c             *
 *      Function:         Quest                                               *
 *      Author(s):        Angel@Nirvana                                       *
 *      Copyright:        Copyright (c) 2017 Angel                            *
 *                                All Rights Reserved.                        *
 *      Source:           02/01/17                                            *
 *      Notes:                                                                *
 *                                                                            *
 *                                                                            *
 *      Change History:                                                       *
 */

#include "/sys/lib.h"
 
#include <ansi.h>

inherit "obj/monster";
int hscript;

reset(arg)
{
  object gold,armor,weapon;
  ::reset(arg);
  if(arg) return;
  set_name("Bob Ray");
  set_alt_name("ray");
  set_alt_name("mayor");
  set_race("Master Mason");
  set_alias("bob");
  set_short(""+HIY+"Bob Ray"+NORM+" Mayor of Gas City");
  set_long("\Before you is the Mayor of Gas City. He appears to be in his\n\
late 60's. The mayor is a General Contractor running his own business.\n\
Although he is an older man, do not underestimate his ability to act\n\
fast and crush you! Master Mason Bob Ray has much power when he calls\n\
on his God for vengeance!\n");
  set_level(24);
  set_hp(899 + random (100));
  set_ac(20 + random (10));
  set_wc(38 + random (10));
  set_heal(3,1);
  set_al(0);
  set_chat_chance(10);
  load_chat(query_name()+" says, \"Hello, How are you today?\"\n");
  load_chat("You stand in the Mayors office looking around and feel inspired by what you see!\n");
  gold=clone_object("obj/money");
  gold->set_money(3000);
  move_object(gold, this_object());
  add_spell("saber",
"#MN# slices his "+HIY+"M"+HIW+"asonic"+NORM+" "+HIY+"S"+HIW+"word"+NORM+" through you.\n",
"#MN# slices his "+HIY+"M"+HIW+"asonic"+NORM+" "+HIY+"S"+HIW+"word"+NORM+" through #TN#.\n",
                     50,60,"other|fire");
  set_dead_ob(this_object());
  add_spell("purging light",
"#MN# calls for $HW$PURGING LIGHT\n\
~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n\
~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n\
~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~$N$\n",
"$HY$From the Void of the Universe the Master Mason calls upon\n\
\t\tThe Great Architect to Purge #TN# with light!$N$\n\
$HW$~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n\
~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~$N$\n",
                     15,30,"other|fire");
}

monster_died() {
  object hscript;
  hscript = clone_object("/players/angel/area/mansion/obj/hscript.c");
  tell_room(environment(this_object()),
  "\n"+HIM+"Mayor Ray"+NORM+" falls to his knee's and prays out\n\
"+HIW+"I ask for the light to illuminate the dark path as I ascend in victory!\n\
\n\
                     The radiant light burns your eyes!"+NORM+"\n");
  this_player()->hit_player(7 + random(9));
  move_object(hscript,this_object());
}

init() {
  ::init();
  add_action("ask","ask"); }

ask(str) {
string s1,s2;
  if(!str) { write("Who did you want to ask?\n"); return 1; }
  sscanf(str,"%s %s",s1,s2);
  if(s1 != "mayor") { write("Be a little more formal.\n");
        return 1; }
if( (s1 == "mayor") && (s2 == "ray") )
  {write("    An order of European Knights amassed a huge amount of\n\
priceless treasure. It was brought to the United States and\n\
hidden by the Founding Fathers after the Revolutionary War. The\n\
Masons hid the treasure in a secret location to keep it out of\n\
the hands of the British. To this day the treasure has not been\n\
found. If you seek out the treasure you must find Hiram's Key to\n\
start unlocking the clues. \n");
return 1;
}}