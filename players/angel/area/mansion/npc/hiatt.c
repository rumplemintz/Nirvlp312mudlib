/*                                                                    *
 *    File:   /players/angel/area/mansion/npc/hiatt.c                 *
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
  set_name("William Hiatt");
  set_alt_name("mason");
  set_race("Mason");
  SetMultipleIds(({"william","hiatt","mayor"}));
  set_short("William Hiatt (R)");
  set_long("He is the mayor of Union City. He is a middle aged\n\
man growing the ways of the mason. He is wearing a white\n\
leather apron with the markings for Grand Inspector Inquisitor.\n");
  set_level(19);
  set_hp(450 + random (75));
  set_ac(16 + random (6));
  set_wc(28 + random (6));
  set_al(-200);
  set_chat_chance(15);
  load_chat(query_name()+" says, \"Well, we all know I can take everyone here out!\"\n");
  load_chat("This is one fantastic cigar! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\
~~~~MONTECRISTO! MONTECRISTO! MONTECRISTO! ~~~~~~~~~~~~~~~~~~~~~~~~~\n\
~~~~~~~~~~~~~~~~~~~How could you not see it's the Best!~~~~~~~~~~~~\n");
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
