#include "/players/wocket/closed/ansi.h"
inherit "/players/wocket/std/wiztell.c";

reset(arg){
  if(arg) return;
  owner = "angel";
   cap_owner = "Angel";
  color = HIC;
  extra_look = "Angel the grey wise Wiz!";
}
