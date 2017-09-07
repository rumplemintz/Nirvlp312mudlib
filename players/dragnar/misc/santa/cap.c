inherit "obj/armor";

#include <ansi.h>

reset(arg){
   ::reset(arg);
	set_short(HIW+"Fur-Lined "+HIR+"Stocking Cap"+NORM);
  set_long(
"This stocking cap is all that is keeping Santa's massively\n\
wild mane of snow white hair inside.\n");
   set_ac(1);
   set_weight(1);
   set_value(1200);
   set_name("cap");
   set_type("helmet");
   SetMultipleIds( ({ "stocking cap", "fur-lined stocking cap", }) );
}

void init() 
{
  ::init();
}
