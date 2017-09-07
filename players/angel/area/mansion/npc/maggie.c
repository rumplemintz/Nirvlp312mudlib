/*                                                                    *
 *    File:             /players/angel/area/mansion/npc/maggie.c      *
 *    Function:         npc                                           *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           2/17/17                                       *
 *    Notes:                                                          *
 *                                                                    *
 *                                                                    *
 *    Change History:                                                 *
 */

#include "/sys/lib.h"

#include <ansi.h>

inherit "obj/monster";

reset(arg)
{
  object gold,armor,weapon;
  if(arg) return;
  ::reset(arg);
  set_name("maggie");
  set_race("human");
  set_alias("woman");
  set_alt_name("marguerite");
  set_short("Marguerite Ray");
  set_long("Marguerite is Bob Ray's wife. She is elderly with gray hair.\n");
  set_level(10);
  set_hp(150);
  set_wc(15);
  set_ac(8);
  set_al(200);
  set_aggressive(0);
  set_chat_chance(8);
  load_chat(query_name()+" asks, \" Hello, who might you be?\"\n");
  load_chat("Maggie says,  Yes! It is nice to have visitors!\n");
  load_chat("Maggie says, Have a seat on my chair.\n");
  weapon=clone_object("/players/angel/area/mansion/obj/swatter.c");
  move_object(weapon,this_object());
  init_command("wield swatter");
  gold=clone_object("obj/money");
  gold->set_money(random(50)+350);
  move_object(gold, this_object());
  add_spell("lazer","#MN# swings her flyswatter with all her might $HR$SWAT$N$.\n",
                     "#MN# says, look at that fly on #TN# nose, $HR$SWAT$N$.\n",
                     10,10,"other|lazer");
}
