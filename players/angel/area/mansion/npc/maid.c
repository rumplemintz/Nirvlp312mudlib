/*                                                                            *
 *      File:             /players/angel/area/mansion/maid.c                  *
 *      Function:         NPC                                                 *
 *      Author(s):        Angel@Nirvana                                       *
 *      Copyright:        Copyright (c) 2017 Angel                            *
 *                                All Rights Reserved.                        *
 *      Source:           02/2/17                                             *
 *      Notes:                                                                *
 *                                                                            *
 *                                                                            *
 *      Change History:                                                       *
 */

#include "/sys/lib.h"

#include <ansi.h>

inherit "obj/monster";

reset(arg)
{
  object gold,armor,weapon;
  ::reset(arg);
  if(arg) return;
  set_name("Maid");
  set_alt_name("junita");
  set_race("human");
  set_alias("maid");
  set_short("Maid");
  set_long("A slender girl in a brown dress. Her name tag has Junita on it.\n");
  set_level(8);
  set_hp(120);
  set_al(-100);
  set_wc(12);
  set_ac(7);
  gold=clone_object("obj/money");
  gold->set_money(random(60)+300);
  move_object(gold,this_object());
}
