inherit "/room/room.c";

#define MAPDM "/players/dragnar/SevenSpires/daemons/mapDM"

string room_name;

reset(arg) {
  if(arg) return;
  set_light(1);
  set_short("The Forest of Fear");
room_name = "r15c3";
set_long(MAPDM->get_map( basename( this_object() )));
dest_dir=({
	 "/players/dragnar/SevenSpires/rooms/forest/f1/r14c3","north",
	 "/players/dragnar/SevenSpires/rooms/forest/f1/r15c2","west",
	 "/players/dragnar/SevenSpires/rooms/forest/f1/r15c4","east",
}); 
}
