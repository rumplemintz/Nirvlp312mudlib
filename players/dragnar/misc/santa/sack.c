inherit "obj/armor";

#include <ansi.h>

reset(arg){
   ::reset(arg);
  set_short(HIR+"Gigantic Red Christmas Sack"+NORM);
  set_long(
"Who doesn't want to see what surprises are inside Santa's wrinkled red sack?\n");
   set_ac(0);
   set_weight(1);
   set_value(1200);
   set_name("sack");
   SetMultipleIds( ({ "christmas sack","red christmas sack", "gigantic red christmas sack", }) );
   set_type("misc");
}

void init() 
{
  ::init();
}
