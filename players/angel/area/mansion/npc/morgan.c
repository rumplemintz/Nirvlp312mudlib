/*                                                                    *
 *    File:   /players/angel/area/mansion/npc/morgan.c                *
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
  set_name("William Morgan");
  set_alt_name("mason");
  set_race("Mason");
  SetMultipleIds(({"william","morgan","mayor"}));
  set_short("William Morgan (R)");
  set_long("He is the mayor of Springfield. He is a middle aged\n\
man growing the ways of the mason. He is wearing a white\n\
leather apron with the markings for Prince of Jerusalem.\n");
  set_level(19);
  set_hp(450 + random (75));
  set_ac(16 + random (5));
  set_wc(28 + random (5));
  set_al(-200);
  set_chat_chance(15);
  load_chat(query_name()+" says, \"Hey I'm in!\"\n");
  load_chat("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\
~~~~~~~~~~~~~~~~~I will take a Romeo Y Julieta any day!~~~~~~~~~~~~~\n\
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
