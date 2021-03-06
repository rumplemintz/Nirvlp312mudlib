#include "def.h"

inherit MYROOM;

reset(arg) {
  if (arg) return;
  set_pk(1);
  set_light(1);
  short_desc=HIB+"Dark City"+NORM;
  long_desc=
"     Shadows rule this city of darkness and mystery.  This crowded\n\
street is filled with shops closed down for the perpetual night.\n\
Skyscrapers from different eras of history block the skyline, making\n\
you doubt whether or not there is an end to these maze-like streets.\n\
To the east is the police station.\n";
  items=({
    "shadows","Inky blots of darkness spread by the occasional streetlight",
    "street","Dark-hued cars roll through the streets of the city",
    "shops","Pawn shops, toy stores, repair shops, barber shops, everything you\n"+
            "can imagine, but none of it is open",
    "skyscrapers","Bleak edifices of humanity's achievements block the sky as far\n"+
                  "as you can see",
    "skyline","Buildings, large and small, as far as you can see",
    "station","A brick and mortar building slightly obscured by shadows",
  });
  dest_dir=({
    PATH+"street7","north",
    PATH+"squadrm","east",
    PATH+"street5","south"
  });
  set_config(call_other(PATH+"controller","query_config"));
}   

void set_config(int arg) {
  switch(arg) {
    case 0:
      dest_dir=({
        PATH+"street7","north",
        PATH+"squadrm","east",
        PATH+"street5","south"
      });
      break;
    case 1:
    case 2:
      dest_dir=({
        PATH+"street7","north",
        PATH+"squadrm","east",
      });
      break;
    case 3:
      dest_dir=({
        PATH+"street7","north",
        PATH+"street5","west",
        PATH+"squadrm","east",
      });
      break;
  }
}
