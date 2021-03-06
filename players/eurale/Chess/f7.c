#include "DEF.h"
inherit "room/room";

reset(arg) {
  if(arg) return;
set_light(0);

short_desc = GRY+"Chess Board"+NORM;
long_desc =
  "  The floating feel of the board underneath your feet makes you uneasy.  A \n"+
  "strange mist surrounds the area preventing vision in any direction.  Muffled\n"+
  "sounds like people whispering can be heard somewhere deep within the mist.\n";

items = ({
 "board","The board is some kind of smooth, grey material",
 "mist","A thick, watery fog that moistens your skin",
});

dest_dir = ({
});

}

realm() { return "NT"; }

init() {
  ::init();
  add_action("North","north");
  add_action("South","south");
  add_action("East","east");
}

East() {
  TP->move_player("into the mist#players/eurale/Chess/g7.c");
  return 1; }

West() {
  TP->move_player("into the mist#players/eurale/Chess/e7.c");
  return 1; }

North() {
  TP->move_player("into the mist#players/eurale/Chess/f6.c");
  return 1; }

South() {
  TP->move_player("into the mist#players/eurale/Chess/f8.c");
  return 1; }
