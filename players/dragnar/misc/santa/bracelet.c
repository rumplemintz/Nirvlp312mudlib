inherit "obj/armor";

#include <ansi.h>

reset(arg){
  ::reset(arg);
  set_short(HIW+"Coca Cola Bracelet"+NORM);
  set_long(
"Santa's always been a shill, but he always shills Coca Cola products.\n\
This guy is blatant about his willingness to sell anything for a buck.\n");
   set_ac(1);
   set_weight(1);
   set_value(1200);
   set_name("bracelet");
   set_type("bracelet");
   SetMultipleIds( ({ "coca cola bracelet", "coca cola", }) );
}

void init() 
{
  ::init();
}
