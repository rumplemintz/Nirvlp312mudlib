/*                                                                    *
 *    File:         /players/angel/area/mansion/obj/hscript.c         *
 *    Function:         OBJ                                           *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           02/7/17                                       *
 *    Notes:       A Reward for solving the Masonic Quest             *
 *                                                                    *
 *                                                                    *
 *    Change History:                                                 *
 */

#include <ansi.h>;
inherit "/obj/generic_heal.c";

void reset(int arg)
{
  ::reset(arg);
  if(arg) return;
  set_name("masonic healing script");
  add_alias("script");
  add_alias("hscript");
  set_short(HIR+"["+HIW+"Masonic Healing Script"+HIR+"]"+NORM);
  set_long("The Masonic Healing Script calls upon the Great Architect\n\
of the Universe to bless thy children. Mason's invoke thy blessing in\n\
times of great need.\n");
  set_type("blessing");
  set_type_single("blessing");
  set_msg("Thy blessing has been invoked upon Thy child with reverence of the Great Architect.\n");
  set_msg2(" invokes Thy blessing upon Thy child with reverence of the Great Architect.\n");
  add_cmd("invoke");
  set_heal(50,50);
  set_charges(2);
  set_soak(-3);
  set_stuff(-3);
  set_value(0);
}

query_save_flag(){
  return 1;
  }