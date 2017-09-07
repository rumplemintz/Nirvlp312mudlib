/*                                                                    *
 *    File:         /players/angel/area/mansion/obj/masonic_pin.c     *
 *    Function:         OBJ                                           *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           02/7/17                                       *
 *    Notes:       The Masonic Pin is recognition of                  *
 *                           Compeleting the Masonic Quest            *
 *                                                                    *
 *    Change History:                                                 *
 */

#include <ansi.h>

inherit "obj/treasure";

reset(arg) {
  if(arg) return;
set_id("Masonic Pin");
set_alias("masonic pin");
set_short(HIY+"M"+HIW+"asonic"+NORM+" "+HIY+"P"+HIW+"in"+NORM);
set_long(
  "  The Square and Compasses are joined together. Each leg of the\n\
compass is pointing in opposite directions. The letter G is inlaid\n\
in the center of the square and compass. This is the single most\n\
universally identifiable symbol of Freemasonry. Only those who\n\
defeat Hiram Abif and complete the quest given by Mayor Ray\n\
will adorn this pin!\n");
set_weight(0);
set_value(0);
set_no_clean(1);
}

drop() { return 1; }

query_auto_load(){return "players/angel/closed/masonic_pin.c:";}