inherit	"room/room";

reset(arg) { 
  if(!arg) {
  set_light(1);
  short_desc = "Purple Room";
  long_desc = 
   "\n"+
   "\n";
  property = ({"NT", "NC", "PK"});
  dest_dir = ({"/players/cosmo/apt/pkarea/cube/6", "north",
               "/players/cosmo/apt/pkarea/cube/7", "west",
               "/players/cosmo/apt/pkarea/cube/4", "down"});
  }
}
