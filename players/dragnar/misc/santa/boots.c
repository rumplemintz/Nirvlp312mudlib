inherit "obj/armor";

#include <ansi.h>

reset(arg){
  ::reset(arg);
  set_short(HIBLK+"Large Snow-Ready Boots"+NORM);
  set_long(
"These black boots are made primarily for stomping through mounds\n\
of snow or reindeer dung.\n");
   set_ac(2);
   set_weight(1);
   set_value(1500);
   set_name("boots");
   SetMultipleIds( ({ "large boots","snow-ready boots", "snow boots" }) );
   set_type("boots");
}

void init() 
{
  ::init();
}
