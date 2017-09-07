/*                                                                    *
 *    File:             /players/angel/area/mansion/npc/hiram.c       *
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
#include "/obj/ansi.h";

inherit "obj/monster";

  int lives;
  int H;

reset(arg)
{
  object gold,armor,weapon;
  ::reset(arg);
  if(arg) return;
  set_name("Hiram Abif");
  set_alt_name("hiram");
  set_alt_name("abif");
  set_race("master mason");
  set_alias("hiram");
  set_short(HIB+"Hiram Abif"+NORM);
  set_long("\Grand Master Hiram Abif is the Grand Architect of\n\
King Solomon’s Temple. Hiram knows secret which, by its mere\n\
possession, a person would be allowed to pass himself off as a\n\
Master Mason, or journeyman builder. Secrets that can only be\n\
obtained by the death of Hiram Abif.\n\
\n\
Hiram is a Master Mason\n\
Hiram is surrounded by the aura of the righteous.\n\
Hiram has a small "+HIY+"gold star"+NORM+" tattoo on his inside right ankle.\n");
  set_level(29);
  set_hp(4600 + random (666));
  set_ac(68 + random (6));
  set_wc(88 + random (6));
  set_heal(4,1);
  set_al(-100);
  set_dead_ob(this_object());
  set_aggressive(0);
  set_chat_chance(15);
  load_chat(query_name()+" says, \"Come be "+HIW+"Re-Born"+NORM+"!\"\n");
/*  gold=clone_object("obj/money");
  gold->set_money(40000);
  move_object(gold, this_object()); This gold will be moved to Hiram_02 so player has to kill both mob to get reward*/

  set_multi_cast(1);

  add_spell("dodge",
"#MN# $HY$dodged your pathetic, $HR$wretched,$N$ $H$feeble,$N$ $HB$woeful,$N$ $HM$sorry,$N$ $HY$poor,$N$ $HR$pitiful,$N$\n"+
"\n"+
"$HW$lamentable,$N$ $HG$deplorable,$N$ $HB$contemptible,$N$ $HM$inadequate,$N$ $HR$paltry,$N$ $HY$insufficient attack.$N$\n"+
"\n",
"#MN# $HY$dodged your pathetic, $HR$wretched,$N$ $H$feeble,$N$ $HB$woeful,$N$ $HM$sorry,$N$ $HY$poor,$N$ $HR$pitiful,$N$\n"+
"\n"+
"$HW$lamentable,$N$ $HG$deplorable,$N$ $HB$contemptible,$N$ $HM$inadequate,$N$ $HR$paltry,$N$ $HY$insufficient attack.$N$\n"+
"\n",
20,({30,40}),({"physical","physical"}));

  add_spell("pure energy",
"#MN# summons forth a massive $HW$B U R S T$N$, of pure energy from his Devine Architect!\n"+
"\n"+
"$HW$PURE ENERGY B U R S T$N$\n"+
"                         $HW$PURE ENERGY B U R S T$N$\n"+
"                                                      $HW$PURE ENERGY B U R S T$N$\n"+
"\n",
"#MN# summons forth a massive $HW$B U R S T$N$, of pure energy from his Devine Architect!\n"+
"\n"+
"$HW$PURE ENERGY B U R S T$N$\n"+
"                         $HW$PURE ENERGY B U R S T$N$\n"+
"                                                      $HW$PURE ENERGY B U R S T$N$\n"+
"\n",
20,({10,40}),({"physical","other|eletric"}));

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

  add_spell("sword",
"#MN# slices his "+HIY+"M"+HIW+"ASONIC"+NORM+" "+HIY+"S"+HIW+"WORD"+NORM+" through you.\n",
"#MN# slices his "+HIY+"M"+HIW+"ASONIC"+NORM+" "+HIY+"S"+HIW+"WORD"+NORM+" through #TN#.\n",
30,50,"other|fire");

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
15,({25,35}),({"other|fire","other|laser"}),1);

  set_dead_ob(this_object());
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
  object mob;

  say(""+BOLD+"King Solomon comes forward!\n\
\n\
\n\
King Solomon starts praying for the salvation of the fallen martyr!\n\
\n\
\n\
O' come to life again, RISE from the dead!\n\
\n\
\n\
O' come to LIFE again, RISE from the DEAD!\n\
\n\
\n\
O' COME TO LIFE AGAIN AND NOW RISE FROM THE DEAD!"+NORM+"\n");

  mob = clone_object("/players/angel/area/mansion/npc/hiram_02.c");
  move_object( mob, environment(this_object()));
  if( attacker_ob ) {
    mob->attacked_by( attacker_ob );
    attacker_ob->attacked_by( mob );
  }
}
