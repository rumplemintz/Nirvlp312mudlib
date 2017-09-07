/*                                                                            *
 *      File:             /players/angel/area/town/obj/knife.c                *
 *      Function:         weapon                                              *
 *      Author(s):        Angel@Nirvana                                       *
 *      Copyright:        Copyright (c) 2006 Angel                            *
 *                                All Rights Reserved.                        *
 *      Source:           11/20/06                                            *
 *      Notes:                                                                *
 *                                                                            *
 *                                                                            *
 *      Change History:                                                       *
 */

#include <ansi.h>

inherit "obj/weapon";

reset(arg){
  ::reset(arg);
  if (arg) return;

set_name("boyscout knife");
set_alias("knife");
set_alt_name("scout");
set_short(HIY+"Boyscout Knife"+NORM);
set_long(
  "This small, knife has several blades with the scout emblem!\n");
set_type("knife");
set_class(16);
set_weight(1);
set_value(250);
}