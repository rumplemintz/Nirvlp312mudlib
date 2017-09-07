inherit "obj/armor";

#include <ansi.h>

reset(arg){
   ::reset(arg);
	set_short(HIW+"Fur-Lined "+HIR+"Pants"+NORM);
  set_long(
"These pants have the same consistency as sweat pants, because Santa\n\
 needs all the help he can in order to fit pants.\n");
   set_ac(1);
   set_weight(1);
   set_value(1200);
   set_name("pants");
   SetMultipleIds( ({ "santa pants","fur-lined pants"}) );
   set_type("pants");
}

void init() 
{
  ::init();
}
