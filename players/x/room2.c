inherit "/room/room";

reset(arg) {
  ::reset(arg);
  if(arg) return;
  set_short("X habitat");
  set_light(1);
  set_long("This is a habitat.\n");
  dest_dir = ({ "/players/x/room", "south" });
}

init() { write("::init() called.  \n");  ::init(); }
