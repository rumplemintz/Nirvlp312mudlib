/******************************************************************************
 *
 *  File:         dest_rift.c
 *
 *  Function:     move a player to Saber's rift from guild hall
 *
 *  Author(s):    Vital
 *
 *  Copyright:    Copyright (c) 2007 Vital-Dev
 *                All Rights Reserved.
 *
 *  Source:       Started anew.
 *
 *  Change History:
 *      2007-06-15    Added Header
 *  
 *****************************************************************************/

#include "/players/guilds/vampires/headers/player_object.h"
#include "/players/guilds/vampires/headers/guild.h"

int
main()
{
  if (TP && PFANGS)
  {
    PFANGS->tell_my_room(capitalize((string)TPN) + "extends " + TPPOS +
      "wings and flies off to rift.\n");
    write("You extend your wings and fly off to the rift.\n");
    TP->move_player("into the mist#players/saber/ryllian/rift.c");
    return 1;
  }
  return 0;
}
