/*                                                                    *
 *    File:         /players/angel/area/mansion/obj/masonic_saber_01.c*
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
  ::reset(arg);
  if (arg) return;
  set_name("Masonic Saber");
  set_alias("saber");
  set_type("sword");
  set_short(HIY+"M"+HIW+"asonic"+NORM+" "+HIY+"S"+HIW+"aber"+NORM);
  set_long("  This popular saber has a quality stainless-steel blade with a central\n\
vein from top to bottom. The hilt and quillons are engraved with\n\
numerous Masonic designs. The metallic protection (pipe and head),\n\
in an aged-silver style, with a scabbard that is made of premium\n\
quality black leather adds to the majestic appearance of the\n\
decorative saber. Looks like it should be displayed on a shelf!\n");
  set_class(16);
  set_weight(1);
  set_value(1000);

}