#include "/players/tristian/lib/goblin_define.h"
inherit "/players/vertebraker/closed/std/room.c";
int climb;
int rope;

reset(arg) {
  if(arg) return;
set_light(1);

short_desc = "Goblin Sentry Outpost";
long_desc =
" This area seems barren compared to the other areas of the camp. Tall\n"+
"grass dominates the area, and a crude wooden tower sits off to the west\n"+
"side providing a good view of the camp and out into the forest which crowds\n"+
"the clearing on two sides.\n";

items = (
{
"clearing",
  "An open area of the woods, mostly beaten down grass and dirt with tents strewn around",
"tents", 
  "Crude tents that leak at the seams, made from some\n"+
  "unknown tanned material",
"material",
  "Tanned hides, possibly human mixed with other animals",
"camp",
  "Some tents scattered about with small goblinlike humanoids milling around",
"pines",
  "Evergreen pines well over 100' tall",
"forest",
  "An array of hardwoods and evergreens with a dazzaling display\n"+
  "of light that falls down through the tree tops that tower far above",
"trees",
  "Tall pines, probably been growing since this forest was new",
"grass",
  "Taller grass, about waist high for you, makes a perfect\n"+
  "hiding area for a goblin",
"tower",
  "A crude tower with a rope ladder hanging from it",
"ladder",
  "A rope ladder with wooden rungs, perhaps you can 'climb' the 'rope'",
"rope",
  "A rope ladder with wooden rungs, perhaps you can 'climb' the 'rope'",
}
);

if(!present("goblin1",this_object()))
  move_object(clone_object(NPC+"goblin_sentry1.c"),
  this_object());

if(!present("goblin2",this_object()))
  move_object(clone_object(NPC+"goblin_sentry2.c"),
  this_object());

if(!present("goblin3",this_object()))
  move_object(clone_object(NPC+"goblin_sentry1.c"),
  this_object());


dest_dir = (
{
RMS+"g_room1.c",    "west",
}
);

}

init()
{
  ::init();
  add_action("climb","climb");
  add_action("Smell","smell");
  add_action("Search","search");
  add_action("Listen","listen");
}

climb(str)
{
if(!str)
{
write("Climb what?\n");
return 1;
}

if(str == "rope")
{
write("You climb up into the tower.\n");
say (TPN+" climbs the rope into the tower.\n");
move_object(this_player(),RMS+"tower1.c");
command("look",this_player()); 
return 1; 
}

write("Climb what?\n");
return 1;
}

Smell(str)
{
if(!str || str == "air") {
write("The smells of pine trees and dirty goblins wafts through the air.\n");
return 1;
}
return 1;
}

Search()
{
write("You find nothing special.\n");
return 1;
}

Listen()
{
write("The general din of the goblin camp, and off further into the forest,\n"+
  "the sounds of birds chirping float on the afternoon breeze.\n");
return 1;
}
