/*                                                                            *
 *      File:             /players/angel/area/mansion/gardener.c              *
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
  set_name("Gardener");
  set_alt_name("jose");
  set_race("human");
  set_alias("gardener");
  set_short("A Gardener");
  set_long("A short fellow wearing a brown uniform. His name tag says Jose.\n");
  set_level(10);
  set_hp(150);
  set_al(-100);
  set_wc(8);
  set_ac(15);
  set_chat_chance(3);
  load_chat("What do you think about the bonsai trees?\n");
  load_chat("Me too, I think seeing them in the large pottery keeps me in awe!!!\n");
  gold=clone_object("obj/money");
  gold->set_money(random(50)+400);
  move_object(gold,this_object());
}
