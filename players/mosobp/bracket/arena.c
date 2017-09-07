inherit "room/room";
#include "/players/zeus/museum/arena/file.h"

object ctob;

reset(arg){
 if(arg) return;

  if(!present("Invisible_catch_tell_Object"), this_object())
  {
    ctob = clone_object("/players/mosobp/bracket/ctobj.c");
    ctob->set_location("N ");
    move_object(ctob, this_object());
  }
  
	short_desc = "Mob Battle Arena";
	long_desc =
"You are in the arena'.\n";
	items=({
	});
	set_light(1);
	dest_dir=({
		
	});
}