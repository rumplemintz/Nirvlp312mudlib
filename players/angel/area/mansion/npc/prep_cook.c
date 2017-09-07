/*                                                                            *
 *      File:             /players/angel/area/mansion/prep_cook.c             *
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
  set_name("Prep Cook");
  set_alt_name("cook");
  set_race("human");
  set_alias("cook");
  set_short("Prep Cook");
  set_long("A frumpy girl in a brown dress. Her name tag is not quite legible.\n");
  set_level(8);
  set_hp(120);
  set_al(-100);
  set_wc(12);
  set_ac(7);
  set_chat_chance(3);
  load_chat("Well!\n");
  load_chat("Yes ma'am, I am right on it!\n");
  gold=clone_object("obj/money");
  gold->set_money(random(60)+300);
  move_object(gold,this_object());
}
