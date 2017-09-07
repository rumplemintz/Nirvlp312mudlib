inherit "obj/armor";

#include <ansi.h>

reset(arg){
   ::reset(arg);
	set_short(HIBLK+"Wide Buckled Belt"+NORM);
  set_long(
"This belt is more of a life preserver, because it is saving\n\
the lives of everyone around if it were to fail and Santa's pants\n\
were to fall.\n");
   set_ac(1);
   set_weight(1);
   set_value(1200);
   set_name("belt");
   set_type("belt");
   SetMultipleIds( ({ "wide buckled belt", "buckled belt" }) );
}

void init() 
{
  ::init();
}
