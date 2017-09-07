inherit "obj/armor";

#include <ansi.h>

string *colors;

#define RCOLOR colors[ random(sizeof(colors)) ]

reset(arg){
   ::reset(arg);

  if( !colors )
    colors = ({ HIR, HIG, HIB, HIY, HIM, HIC, HIW });

  set_short(BLINK+RCOLOR+"C"+RCOLOR+"h"+RCOLOR+"r"+RCOLOR+"i"+RCOLOR+"s"+RCOLOR+"t"+RCOLOR+"m"+RCOLOR+"a"+RCOLOR+"s L"+RCOLOR+"i"+RCOLOR+"g"+RCOLOR+"h"+RCOLOR+"t"+RCOLOR+"s"+NORM);
  set_long(
"Wrapped around Santa's neck, this 'necklace' is just some Christmas\n\
lights lit up, blinking and twinkling away.\n");
   set_ac(0);
   set_weight(1);
   set_value(1200);
   set_name("lights");
   set_type("necklace");
   SetMultipleIds( ({ "christmas lights",  }) );
}

void init() 
{
  ::init();
}
