#include "/players/wocket/closed/ansi.h"
inherit "/obj/monster.c";

reset(arg){
  ::reset(arg);
  if(arg) return;
  set_name("rathe");
  switch(random(4)){
    case 0:  set_short(HIR+"Aamoth"+OFF+", a rathe guard.\n");  set_alt_name("aamoth"); break;
  case 1:  set_short(HIR+"Faltker"+OFF+", a rathe guard.\n");  set_alt_name("faltker"); break;
  case 2:  set_short(HIR+"Zepht"+OFF+", a rathe guard"); set_alt_name("zepht"); break;
  case 3:  set_short(HIR+"Hassi"+OFF+", a rathe guard"); set_alt_name("hassi"); break;
  }
  set_alias("guard");
  set_long("not written yet.\n");
  set_hp(450);
  set_wc(28+random(5));
  set_ac(16+random(3));
  set_level(19);
  set_al(-500);
  set_race("rathe");
}
