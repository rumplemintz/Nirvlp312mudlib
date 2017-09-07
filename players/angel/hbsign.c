#include <ansi.h>

id(str) { return str == "sign"; }

reset () {}

short() {
   return HIR+ BLINK + "Happy Birthday Joab!" + NORM;
}

long() {
   return 1;
}

get() { return 0; }
query_weight() { return 0; }
query_value() { return 0; }
