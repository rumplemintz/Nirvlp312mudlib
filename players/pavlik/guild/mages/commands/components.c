inherit "players/pavlik/guild/mages/inherit/command";
#include "/players/pavlik/guild/mages/defs.h"
#include "../include/string.h"

mapping components;
mapping component_names;

reset(arg) {
  int i;
  if(arg) return;
  set_verb("components");
  set_name("Components");
  set_color_name(HIC+"Components"+NORM);
  set_rank(1);
  set_descrip(
"The components command will show the amount of spell\n\
components that you have saved. Any components that are\n\
stored in a mage pouch will be saved for you.\n"
  );
  component_names = ([
    "leather cord"      : "Leather Cords:"
    ,"gemstone"         : "Gemstone:"
    ,"sulfur_powder"    : "Sulfur Powder:"
    ,"heartstone"       : "Heartstones:"
    ,"silver_needle"    : "Silver Needles:"
    ,"onyx_powder"      : "Onyx Powder:"
    ,"platinum_mirror"  : "Platinum Mirrors:"
    ,"tespian orb"      : "Tespian Orbs:"
    ,"amber rod"        : "Amber Rods:"
    ,"granite_powder"   : "Granite Powder:"
    ,"spider"           : "Spiders:"
    ,"orb of souls"     : "Orbs of Souls:"
    ,"light feather"    : "Light Feathers:"
  ]);
}

query_footer() {
  return CYN+pad("",70,'~');
}

cmd(str) {
  int x;
  object gob;

  gob = present( GOBID, this_player() );
  if( !gob )
    return 0;

  components = gob->query_components();

  print_header();

  x = sizeof(COMPONENT_IDS);
  for( x=0; x < sizeof(COMPONENT_IDS); x++ ) 
    write(pad(component_names[COMPONENT_IDS[x]],18) + components[COMPONENT_IDS[x]]+ "\n");

  write( query_footer() + NORM+ "\n" );
  return 1;
}

print_header()
{
  write(CYN+ pad("Component", 18) + "Amount\n" + query_footer() + "\n"+NORM);
}

