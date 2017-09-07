inherit "obj/armor";

#include <ansi.h>

reset(arg){
  ::reset(arg);
  set_short(RED+"Red "+NORM+"and"+GRN+" Green "+HIY+"Glowing Wedding Ring"+NORM);
  set_long(
"This wedding ring appears to be hand-crafted, likely by some\n\
poor elf who was forced to work hundreds of hours in Santa's\n\
sweatshop, I mean, workshop.\n");
   set_ac(1);
   set_weight(1);
   set_value(1200);
   set_name("ring");
   set_type("ring");
   SetMultipleIds( ({ "red and green glowing wedding ring", "wedding ring", "glowing wedding ring", }) );
}

void init() 
{
  ::init();
}
