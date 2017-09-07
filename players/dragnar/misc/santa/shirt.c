inherit "obj/armor";

#include <ansi.h>

reset(arg){
   ::reset(arg);
	set_short(HIW+"A White Christmas Shirt"+NORM);
  set_long(
"This shirt is pretty plain and is white, with a small Christmas\n\
tree in the center.\n");
   set_ac(0);
   set_weight(1);
   set_value(1200);
   set_name("shirt");
   set_type("chest");
   SetMultipleIds( ({ "white shirt", "christmas shirt", "white christmas shirt", }) );
}

void init() 
{
  ::init();
}
