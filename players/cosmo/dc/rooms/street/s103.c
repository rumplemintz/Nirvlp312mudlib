#include "/players/cosmo/dc/defs.h"
inherit "players/cosmo/dc/dc_room";

reset(arg) {
  if(arg) return;
  set_room_type("street");
  short_desc=GRN+"3rd and Independence"+NORM;
  long_desc=
"nothing\n"+
"to\n"+
"the\n"+
"north\n"+
"\n"+
"\n"+
".\n\n";

  items=({
"grass","The plush green grass is off in the distance to the north",
"buildings", "Old dirty buildings of no particular significance",
  });

  dest_dir=({
    DCSTR+"sms02", "northeast",
    DCSTR+"s104", "west",
    DCSTR+"sms03", "north",
  });
}

init() {
  ::init();
}
