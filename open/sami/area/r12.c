inherit "/players/vertebraker/closed/std/room.c";

reset(arg) {
   if(arg) return;
   set_light(1);
   set_short("A room");
set_long("blah\n");

add_exit("/players/sami/area/carnival/room/r5","north");
add_exit("/players/sami/area/carnival/room/r11","west");
add_exit("/players/sami/area/carnival/room/r13","east");
}