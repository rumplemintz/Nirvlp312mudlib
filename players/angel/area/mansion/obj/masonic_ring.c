#include <ansi.h>
inherit "/obj/armor";

reset(arg) {
  if(arg) return;
  ::reset(arg);
  set_name("masonic ring");
  set_alias("ring");
  set_short(HIY+"M"+HIW+"asonic"+NORM+" "+HIY+"R"+HIW+"ing"+NORM);
  set_long("\
A Square and Compass set in gold with the G inlaid.\n");
  set_ac(1);
  set_type("ring");   
  set_weight(1);
  set_value(1500);
}

do_special(owner){
  if(!worn) return;
  if (!owner || !owner->query_attack())
    return;
  if(random(20) < 4)
  {
    tell_object(owner,
      "The mason ring summons forth a massive "+HIW+"B U R S T"+NORM+",\n"+
      "               of "+HIW+"Pure Energy"+NORM+" from his Devine Architect!\n");
    tell_room(environment(owner),
      owner->query_name()+" BLASTS "+owner->query_attack()->short()+" with Pure Energy!!!\n", ({ owner }));
    owner->add_hit_point(random(3));
    return 1;
  }
  return;
}