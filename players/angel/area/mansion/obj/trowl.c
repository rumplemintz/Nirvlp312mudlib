/*                                                                    *
 *    File:         /players/angel/area/mansion/obj/trowl.c           *
 *    Function:         OBJ                                           *
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

inherit "obj/weapon.c";

reset(arg) {
   if(arg) return;
   ::reset(arg);
   set_name("trowl");
   set_alias("trowl");
   set_short("Trowl");
   set_type("dagger");
   set_long("The square and compass with letter G inlaid is on the short handle\n\
of this gold trowl. The sides of the letter opener are very sharp.\n");
   set_class(5);
   set_weight(1);
   set_value(400);
}