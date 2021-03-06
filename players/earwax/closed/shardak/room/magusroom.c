/*
 * Shardak guild is (tm) Dragnar/John
 * Change log:
 * 2000 - verte wrote this.
 */
#include "/players/balowski/lib.h"
#include "../include/def.h"
#include "../include/daemons.h"
#include "../include/people.h"
#include "../include/macros.h"
#include "../include/ansi.h"
#include <security.h>
#define VBOARD "/players/earwax/closed/misc/board2"
#ifndef __FILE__
#define __FILE__ file_name(this_object())
#endif

inherit ROOM;

void
create()
{
    ::create();
    set_short(RED+"Magus"+HIK+" Meeting Room"+NORM);
    set_long(HIK+"\
The tunnel stops here in a small room cut from the earthen\n\
tunnels around you.  Dimly lit torches glow alongside you,\n\
proving an eerie ethereal glow to the area.  The passageways\n\
around you have been blocked off on all sides by loose,\n\
crumbling rock.  You can type 'magus_title' to set your guild title.\n\
A staircase leads back up to the throne of Shardak.\n"+NORM);
    set_exits(([
        "up" : (PATH+"throne"),
        ]));
    set_items(([
        ({ "earthen tunnels", "tunnels", "passageways" }) :
    "Smooth earthen tunnels carved from the dirt and rock around you,\n"+
    "they extend back up towards Shardak's throne room.\n",
    "torches" : "The glow from the torches emanates throughout the room.\n",
    ({ "rock", "crumbling rock" }) :
    "Loose, large amounts of crumbling granite rest on the ground,\n"+
    "sealing off all passageways except above you.\n",
    "staircase" : "A blackened staircase leads back up to the throne room.\n",
    ]));
    set_light(1);
    set_property("fight area", 1);
    set_property("no teleport", 1);
}

void reset(int arg)
{
    object          board;
    ::reset(arg);
    if (!present("bulletin board")) {
        board = clone_object(VBOARD);
        board->set_name("magi");
        board->set_size(50);
        board->set_short("A magus board stands here openly");
        board->set_editors(LAW);
        board->set_readers(symbol_function("allow_read", this_object()));
        move_object(board, this_object());
    }
}

int magus_title() {

  this_player()->set_title("the "+HIR+"Magus"+NORM+" of "+HIK+"Shardak"+NORM);
  write("You have set your guild title.\n");
  return 1;
}

void init()
{
    ::init();
    add_action("cmdUp","up");
    add_action("magus_title","magus_title");
}

cmdUp()
{
    write("You walk back up to the throne room.\n");
}

status
allow_read(object who)
{
    if (who && (string) who->query_guild_name() == GUILDNAME) return 1;
}

