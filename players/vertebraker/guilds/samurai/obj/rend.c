#include "../def.h"

int r;
int beats;

id(str) {
 return str=="rend_object" || str=="poison";
}

load_it(rank){
  r = rank;
  beats = rank;
  set_heart_beat(1);
}

drop() { return 1; }

heart_beat()
{
  if(!ENV() || !living(ENV()) || ENV()->query_ghost() || beats <=0 ) 
    return destruct(this_object());
  tell_object(ENV(), HIR+"Your wound bleeds profusely!\n"+NORM);
  tell_room(ENV(ENV()),
    HIR+ENV()->QN+"'s wound pours out blood.\n"+NORM);
  ENV()->hit_player(1+random(r), "other|blood");
  beats--;
}
