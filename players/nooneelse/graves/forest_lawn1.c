/*
  forest_lawn1.c
*/

inherit "room/room";

reset(arg) {
if(!present("girl"))  {
move_object(clone_object("/players/saber/monsters/flower.c"),this_object());
        }
  if (arg) return 0;

  set_light(1);
  short_desc="Quiet path";
  long_desc="You are walking along a quiet, peaceful path.  The grass is\n"+
            "a lush deep green and the trees bordering it are strong\n"+
            "and tall.  There is a gentle, warm breeze causing the drooping\n"+
            "branches of the weeping willows to sway gently.\n";
  items=({
    "grass", "The deep green grass is tall and looks comfortable to sit on",
    "tree",  "It is a marvelous example of it's kind.  Tall and strong",
    "trees", "They are marvelous examples of their kind.  Tall and strong",
  });
  dest_dir=({
    "room/vill_green", "north",
    "/players/nooneelse/graves/forest_lawn3", "south",
  });
}