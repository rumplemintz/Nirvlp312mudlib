inherit "/players/dune/closed/guild/boards/board";
#include "../DEFS.h"
#define BOARD_NAME ALTDUNEPATH+"/boards/ideaboard"


init() {
    add_action("new",    "note");
    add_action("read",   "read");
    add_action("remove", "remove");
    add_action("new",    "input");
    add_action("read",   "output");
    add_action("remove", "erase");}

void description() {
  write("Before you stands the guild idea board.\n");
  write("You glance upon the radiance of a Light Board.\n"+
        "Light Boards are high resolution flat panel displays.\n"+
        "Use this board to post any ideas you have about guild\n"+
        "improvement, or other guild modifications.\n"+
        "Usage:   'note headline'\n"+
        "         'read messageNumber'\n"+
        "         'remove messageNumber'\n");
}

string short() {
  return ("The "+FUNKYNAME+" Idea Light Board(" + num_messages + " msgs)");
}

void restore_me() { restore_object(BOARD_NAME); }
void save_me(int arg) { save_object(BOARD_NAME); }
