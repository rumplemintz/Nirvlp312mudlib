inherit "obj/armor";

#include <ansi.h>

reset(arg){
   ::reset(arg);
  set_short(HIW+"White Gloves"+NORM);
  set_long(
"These white gloves were hand-sewn by Mrs. Claus herself. Rumor\n\
has it that it took her 200 years, because she's old.\n");
   set_ac(1);
   set_weight(1);
   set_value(1500);
   set_name("gloves");
   SetMultipleIds( ({ "white gloves",}) );
   set_type("gloves");
}

void init() 
{
  ::init();
}
