inherit "/room/room";

reset(arg) {
  ::reset(arg);
  if(arg) return;
  set_short("X habitat");
  set_light(1);
  set_long("This is a habitat.\n");
  dest_dir = ({ "/players/x/room2", "north" });
}

init() { ::init(); add_action("button", "button"); }

button() { write("Calling init in room2.\n"); call_other("/players/x/room2", "???"); return 1; }
