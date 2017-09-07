/*                                                                    *
 *    File:             /players/angel/area/mansion/npc/hiram_02.c    *
 *    Function:         NPC                                           *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           02/7/17                                       *
 *    Notes:                                                          *
 *                                                                    *
 *                                                                    *
 *    Change History:                                                 *
 */
#include "/players/angel/define.h"

#include "/obj/ansi.h";

inherit "obj/monster";

#define tpn this_player()->query_name()

int x;

reset(arg)
{
  object gold,armor,weapon;
  ::reset(arg);
  if(arg) return;
  set_name("Hiram Abif Reborn");
  set_alt_name("mason");
  set_alt_name("abif");
  set_race("master mason");
  set_alias("hiram");
  set_short(HIW+"Hiram Abif Reborn"+NORM);
  set_long("\Grand Master Hiram Abif is the Grand Architect of\n\
King Solomon’s Temple. Hiram knows secret which, by its mere\n\
possession, a person would be allowed to pass himself off as a\n\
Master Mason, or journeyman builder. Secrets that can only be\n\
obtained by the death of Hiram Abif.\n");
  set_level(24);
  set_hp(1200 + random (400));
  set_ac(30 + random (12));
  set_wc(44 + random (12));
  set_al(-600);
  set_dead_ob(this_object());
  set_aggressive(1);
  set_chat_chance(5);
  load_chat(query_name()+" says, \"Come be "+HIW+"Re-Born"+NORM+"!\"\n");
  gold=clone_object("obj/money");
  gold->set_money(45000);
  move_object(gold, this_object());
  weapon=clone_object("/players/angel/area/mansion/obj/masonic_sword_01.c");
  move_object(weapon, this_object());
  command("wield sword", this_object());
  armor=clone_object("/players/angel/area/mansion/obj/masonic_ring.c");
  move_object(armor, this_object());
  command("wear ring", this_object());
  add_spell("rath",
"#MN# releases a massive  $HR$BLAST$N$-$HR$OF RATH$N$ burning your flesh!\n"+
"\n"+
"$HR$BLAST$N$-$HR$OF RATH$N$\n"+
"\n"+
"                       $HR$BLAST$N$-$HR$OF RATH$N$\n"+
"\n"+
"                                              $HR$BLAST$N$-$HR$OF RATH$N$\n"+
"\n",
"#MN# releases a massive  $HR$BLAST$N$-$HR$OF RATH$N$!\n"+
"\n"+
"$HR$BLAST$N$-$HR$OF RATH$N$\n"+
"\n"+
"                       $HR$BLAST$N$ $HR$OF RATH$N$\n"+
"\n"+
"                                              $HR$BLAST$N$-$HR$OF RATH$N$\n"+
"\n",
50,100,"other|fire");

  add_spell("vengeance",
"#MN#'s Masonic Sword searches for more "+HIW+"light"+NORM+".\n"+
"\n"+
"The sword sucks up the "+HIW+BLINK+"light"+NORM+" and goes after you with "+HIW+BLINK+"God's Vengeance"+NORM+"\n"+
"\n",
"#MN#'s Masonic Sword searches for more "+HIW+"light"+NORM+".\n"+
"\n"+
"The sword sucks up the "+HIW+BLINK+"light"+NORM+" and goes after you with "+HIW+BLINK+"God's Vengeance"+NORM+"\n"+
"\n",
15,({25,35}),({"other|fire","other|laser"}),1);
}

heart_beat(){
  ::heart_beat();
    corpse_grab();
}

  corpse_grab()    {
    object ob;
      if((ob = present("corpse", environment())) && (int)ob->is_corpse()) {
        tell_room(environment(),
          "Hiram snatches: "+(string)ob->short()+".\n");
            move_object(ob, this_object());
return 1;
}}

  monster_died() {

  say(""+BOLD+"I have protected this treasure for King Soloman to the day!\n\
\n\
I will not give up my secrets, however I now entrust in\n\
\n\
you King Soloman's Masonic Sword as a token for completing\n\
\n\
the Maonic Quest!"+NORM+"\n");

this_player()->set_quest("masonic_quest");

while(x < 6)
  {
MOCO("/players/angel/area/mansion/obj/hscript.c"),this_object());
    x++;
  }
MOCO("players/angel/closed/masonic_pin.c"),this_player());



write_file("/players/angel/log/QUEST",ctime(time())+"   "+
              capitalize(TPN)+" has solved the Masonic Quest.\n");
}