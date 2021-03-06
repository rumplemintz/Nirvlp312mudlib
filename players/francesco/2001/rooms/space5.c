#define tp this_player()
#define tpn this_player()->query_name()
#define tpp this_player()->query_possessive()
inherit "room/room";

reset(arg) {
  if(arg) return;

set_light(1);

short_desc = "Space Shuttle 5" ;
long_desc =
     "   SPACE SHUTTLE 5,  YEAR 2001\n"+
     "The walls, the ceiling and the floor of this corridor are all\n"+
     "metallic, shining a bright silver color.\n",

items = ({
   "walls","The side walls of the corridor are about 15 feet long",
   "ceiling", "The ceiling of the corridor is about 9 feet high",
   "floor","The floor has some imprinted arrows, of different colors.\n"+
           "They point to different pathways leading to different areas",
});

dest_dir = ({
  "/players/francesco/2001/rooms/space7.c","north",
  "/players/francesco/2001/rooms/space2.c","south",
  "/players/francesco/2001/rooms/space4.c","east",
  "/players/francesco/2001/rooms/space3.c","up",
});

}
