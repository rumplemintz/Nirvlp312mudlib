inherit "obj/armor";

#include <ansi.h>

reset(arg){
   ::reset(arg);
	set_short(HIW+"Fur-Lined "+HIR+"Jacket"+NORM);
  set_long(
"This jacket is custom-made just for Santa Claus, as only Christmas magic\n\
x (and Dragnar) could make a jacket big enough to fit this guy.\n");
   set_ac(3);
   set_weight(1);
   set_value(1200);
   set_name("jacket");
   set_type("armor");
   SetMultipleIds( ({ "fur-lined jacket", }) );
}

void init() 
{
  ::init();
}
