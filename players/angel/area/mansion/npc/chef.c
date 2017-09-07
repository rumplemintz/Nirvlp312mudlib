/*                                                                            *
 *      File:             /players/angel/area/mansion/chef.c                 *
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
  set_name("Chef");
  set_alt_name("julia");
  set_race("human");
  set_alias("chef");
  set_short("Kitchen Chef");
  set_long("A petite gal wearing a brown dress. Her name tag says Julia.\n");
  set_level(11);
  set_hp(170);
  set_al(100);
  set_wc(10);
  set_ac(15);
  set_chat_chance(3);
  load_chat("We are a bit busy in here, would you mind heading back to the dining room!\n");
  load_chat("Ladies, I need you to finish up your prep work!!!\n");
  gold=clone_object("obj/money");
  gold->set_money(random(50)+450);
  move_object(gold,this_object());
}
