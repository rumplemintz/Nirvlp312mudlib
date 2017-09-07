/*
  walchemist_oven_skin.c - larger skin woven from skins from corpses.
                           used by alchemists to make items.
*/

#include "/players/nooneelse/Alchemist/lib/defs.h"

inherit "obj/treasure";

string skin_msg;
int skin_strength;

query_save_flag() { return 1; }

reset(arg) {
  set_id("woven skin");
  set_alias("skin");
  set_value(0);
  set_weight(1);
}

short() { return NORM+CYN+"A pcocessed skin"+NORM; }

long(str) {
  write(NORM+CYN+"It is a large skin processed from several skins ["+
        skin_strength+"]"+".\n"+NORM);
}

set_skin_strength(arg) { skin_strength=arg; }
query_skin_strength() { return skin_strength; }