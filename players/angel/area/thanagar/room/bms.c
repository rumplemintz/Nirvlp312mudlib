/*                                                                    *
 *    File:             /players/angel/area/thanagar/room/bms.c       *
 *    Function:         room                                          *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2008 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           08/08/08                                      *
 *    Notes:                                                          *
 *                                                                    *
 *                                                                    *
 *    Change History:                                                 *
 */

#include "/sys/lib.h"

#include <ansi.h>

inherit "room/room";

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(1);
  short_desc = "Thanagar";
  long_desc =
"Bottom of Market Square      \n";

  items =
  ({
  });
  dest_dir =
  ({
	"/players/angel/area/thanagar/room/ .c",	"",
	"/players/angel/area/thanagar/room/ .c",	"",
  });
}