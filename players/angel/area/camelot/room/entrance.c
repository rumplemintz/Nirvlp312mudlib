/*                                                                    *
 *    File:             /players/angel/area/camelot/room/entrance.c   *
 *    Function:         room                                          *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           4/15/17                                       *
 *    Notes:                                                          *
 *                                                                    *
 *                                                                    *
 *    Change History:                                                 *
 */

#include "/sys/lib.h"

#include <ansi.h>

#include "/players/angel/area/stargate/obj/dial_obj.c"

inherit "room/room";

reset(arg)
{
  ::reset(arg);
  if(!present("dhd"))
     move_object(clone_object("/players/angel/area/atlantis/obj/dhd"), this_object());
/*  if(!present("sign"))
    move_object(clone_object("/players/angel/area/lowthar/obj/sign.c"), this_object());*/
  if(arg) return;
  set_light(1);
  short_desc = HIY+"Camelot's Stargate"+NORM;
  long_desc =
"             "+HIY+"~ Village of Camelot ~"+NORM+"\n"+
"\n"+
"           /\\      /\\     /\\      /\\\n"+
"          /  \\    /  \\   /  \\    /  \\\n"+
"         /____\\  /____\\ /____\\  /____\\\n"+
"         |  __|  |  __| |  __|  |  __|\n"+
"         |__|||  |__||| |__|||  |__|||\n"+
"\n"+
""+BROWN+"    These are dangerous times in the land of camelot. Fierce Mawr\n"+
"hounds prowl the dark roads, and grymclaws patrol the skies. There\n"+
"is talk of an evil power rising in the east. Beware of what you may\n"+
"face in this realm. The stargate can be seen from here."+NORM+"\n";

  items =
  ({
    "sign",
    "Maybe you should try to 'read' the sign",
    "hounds",
    "",
    "roads",
    "",
    "grymclaws",
    "",
    "realm",
    "",
    "skies",
    "The skies are dark and gloomy",
  });

  dest_dir =
  ({
    "/players/angel/area/camelot/room/cam_01",     "road",
  });
}