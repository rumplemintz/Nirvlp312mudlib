/*                                                                            *
 *      File:             /players/angel/area/mansion                         *
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
  set_name("Fly");
  set_race("fly");
  set_alias("fly");
  set_short("A Fly");
  set_long("A hairy fly.\n");
  set_level(1);
  set_al(0);
  set_chat_chance(2);
  load_chat("bzz..bzz..bzz..\n");
  load_chat("bzz..bzz..bzz..\n");
}
