inherit "obj/armor";

#include <ansi.h>

reset(arg){
   ::reset(arg);
	set_short(GRN+"Mistletoe "+HIW+"Boxer Shorts"+NORM);
  set_long(
"For some odd reason, just peeking out of his pants, you can see\n\
the tell-tale signs of mistletoe print boxer shorts.\n");
   set_ac(1);
   set_weight(1);
   set_value(1500);
   set_name("boxers");
   SetMultipleIds( ({ "boxer shorts", "mistletoe boxer shorts","boxer" }) );
   set_type("underwear");
}

void init() 
{
  ::init();
}
