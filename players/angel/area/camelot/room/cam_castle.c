/*                                                                    *
 *    File:             /players/angel/area/camelot/room/cam_castle.c *
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

inherit "room/room";

reset(arg)
{
  ::reset(arg);
  if(arg) return;
  set_light(1);
  short_desc = HIY+"Camelot"+NORM;
  long_desc =
"    "+HIY+"~ Camelot Castle ~"+NORM+"\n\
"+HIC+"\n\
                              /\\ \n\
                             /  \\ \n\
                         ^  _|..|_  ^ \n\
                       _|I|  |T.|  |.|_ \n\
                      \\II||--| |--||  / \n\
                       -\\-|-------|-/- \n\
                         \\|II I ..|/ \n\
                     /\\   |II.    |     /\\ \n\
                    /  \\ _|III .  |_   /  \\ \n\
                    |--| /(|I.I I  |)\\ |--| \n\
                  _ /(I | +-----------+ |. )\\_ \n\
                 \\------/____---____\\------/ \n\
                   |I.III|  /(===)\\ |  .. | \n\
                   /--------_________------\\ \n\
                  `##########!\\-#####%!!!!!| |\\ \n\
                  /###########!!\\---_##%!!!\\_/| \n\
                \\##############!!!!!/---_%!!!!\\ \n\
                (-)#################!!!!!/----\\_ \n\
\n\
Camelot Castle can be seen from here."+NORM+"\n";

  items =
  ({
  });

  dest_dir =
  ({
	"/players/angel/area/camelot/room/dw_04",   "west",
  });
}

init(){
  ::init();
    this_player()->set_fight_area();
   }

exit(){    if(this_player()) this_player()->clear_fight_area();     }