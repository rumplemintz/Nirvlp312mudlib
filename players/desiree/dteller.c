#include "/players/wocket/closed/ansi.h"
inherit "/players/wocket/std/wiztell.c";

reset(arg){
  if(arg) return;
  owner = "desiree";
   cap_owner = "Desiree";
  color = HIW;
  extra_look = "Desiree is riding her Unicorn!";
}