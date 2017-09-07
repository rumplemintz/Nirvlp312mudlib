/*                                                                    *
 *    File:   /players/angel/area/mansion/npc/ashley.c                *
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
#include <ansi.h>

inherit "obj/monster";

reset(arg)
{
  object gold,armor,weapon;
  ::reset(arg);
  if(arg) return;
  set_name("Albert Ashley");
  set_alt_name("mason");
  set_race("Mason");
  SetMultipleIds(({"albert","ashley","mayor"}));
  set_short("Albert Ashley(D)");
  set_long("\He is the mayor of Boonville. He is a middle aged\n\
man growing the ways of the mason. He is wearing a white\n\
leather apron with the markings for Provost and Judge.\n");
  set_level(19);
  set_hp(450 + random (75));
  set_ac(16 + random (6));
  set_wc(28 + random (6));
  set_al(-200);
  set_chat_chance(15);
  load_chat(query_name()+" says, \"How much are you willing to lose tonight?\"\n");
  load_chat(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\
~~~~~~~~These Cohiba Lancero are the finest cuban cigar there is!~~~\n\
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  gold=clone_object("obj/money");
  gold->set_money(4000);
  move_object(gold, this_object());
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