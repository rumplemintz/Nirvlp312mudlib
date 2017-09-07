inherit "room/room";
#include <ansi.h>
#define tp this_player()->query_name()

reset(arg){

    if(!arg){
move_object(clone_object("/players/daranath/mons/kobold5.c"),this_object());
move_object(clone_object("/players/daranath/mons/kobold5.c"),this_object());
move_object(clone_object("/players/daranath/mons/kobold0a.c"),this_object());
    set_light(1);
short_desc= (BOLD+"DarkenWood"+NORM+" (Kobold Village)");
    long_desc=
  "Set in a large clearing within the DarkenWood, the kobold village\n"+
  "extends north and west from here. Small mud and straw huts dot the\n"+
  "clearing, the bulk of which are much too small for you to enter. A\n"+
  "large stockade wall rises up above the huts, a large wooden gate set\n"+
   "into its front. A small trash dump rests to the side.\n";

items=({
  "shadows", "The shadows move as the wind moves the trees.\n",
  "gate", "The gate within the stockade wall leads into the keep",
  "wall", "A large stockade fence stands to the west",
  "huts", "The crude huts are not what you would consider luxury",
  "mud", "The mud is common to this area",
  "straw", "Its straw, you know.....   straw",
  "dump", "All the kobolds dump thier garbage over to the side",
  "village", "The kobold village is a staging point for kobold invasions\n"+
             "all about Nirvana",
 });


dest_dir=({
 "/players/daranath/clearing/kobold3.c","north",
 "/players/daranath/clearing/trash_dump.c","dump",
           });
        }
        }

init(){
  ::init();
  add_action("search","search");
}

search() {
write("You find nothing about the kobold village.\n");
say (tp +" searches the area.\n");
  return 1;
}
