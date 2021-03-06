/* Not for sale, only available on the Fog Giant kill */

#include <ansi.h>
inherit "/players/daranath/qualtor/newstuff/heals/generic_heal.c";

void reset(int arg)
{
  ::reset(arg);
  if(arg) return;

  set_name("cheese");
  add_alias("wheel");
  set_short("A wheel of "+HIY+"cheese"+NORM);
  set_long("A wheel of "+HIY+"cheese"+NORM+" that you can "+HIW+"eat"+NORM+".\n");

  set_msg("You bite into the "+HIY+"cheese"+NORM+" and feel something gooey in the center.\n");
  set_msg2(" bites into the "+HIY+"cheese"+NORM+" and gets a strange expression.\n");
  add_cmd("eat");
  set_type("bite");

  set_heal(30,30);
  set_charges(5);
  set_stuff(7);
  set_value(75);
}

query_save_flag(){
  return 1;
  }
