#include "/players/mythos/closed/guild/def.h"
demon_pact() {
object ob;
int c;
if(present("demon_pact",tp) || present("demon_spell",tp)) { 
   write("You are already in the demon pact process!\n");
return 1;}
if(qtf < 10) { write("Your control over fae is not enough!\n"); return 1;}
if(scrp < 500) { write("The darkness calls for a sacrifice.\n"); return 1;}
if(tsp < 100) { write("You do not have enough energy!\n"); return 1;}
tp->add_spell_point(-100);
pp->add_sacrifice(-500);
write("You call upon the demons of the underworld......\n");
move_object(clone_object("/players/mythos/closed/guild/spells/pact1.c"),tp);
ob = users();
for(c=0;c<sizeof(ob);c++) {
  if(present("demon_watcher",ob[c]) || ob[c]->query_real_name() == "mythos") { 
  tell_object(ob[c],HIR+"\n\t"+tpn+" has called a demon pact!\n\n"+NORM); } }
return 1;}
