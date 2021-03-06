#define NPC "lupus"
#include "def.h"

#define LENGTH 110
inherit ROOM;

reset(arg) {
  if(arg) return;
  set_no_teleport(1);
  short_desc="Arena";
  long_desc="This is the default room description.";
}
query_spar_area() {
  return 1;
}
query_grand_arena() {
  return 1;
}

init() {
  ::init();
  add_action("cmd_quit","quit");
  add_action("cmd_comm","arena");
  add_action("cmd_awho","awho");
  add_action("block","feign");
  add_action("block","regenerate");
  add_action("block","shadows");
  add_action("block","wolf");
}

cmd_quit() {
  write("You cannot quit from here.\n");
  return 1;
}

arena_channel(str) {
  object *world;
  int i;
  world=users();
  for(i=0;i < sizeof(world);i++) {
    if(environment(world[i]) &&
       environment(world[i])->query_grand_arena() ) 
         tell_object(world[i],
           HIR+"*"+HIB+"ARENA"+HIR+"*"+NORM+
           " "+str+"\n");
  }
}
cmd_comm(str) {
  if(!str) { notify_fail("What do you want to communicate?\n"); return 1; }
    if(str[0]==':')
      arena_channel(TP->query_name()+" "+str[1..strlen(str)]);
    else
      arena_channel(TP->query_name()+" says: "+str);
  return 1;
}
cmd_awho(str) {                       
  object *world;
  object room;
  object npc;
  int i;
  world=users();
  if(npc=find_living(NPC)) world+=({ npc });
  write(
"[--------------------------------------------------------------------]\n"+
" Name                Opponent            Location\n"+
"[--------------------------------------------------------------------]\n");
  for(i=0; i<sizeof(world);i++) {
    room=environment(world[i]);
    if(room && room->query_grand_arena() && !world[i]->query_ghost() &&
       !room->is_arena_central()) {
       write(" "+pad(world[i]->query_name(),20));
       if(world[i]->query_attack())
         write(pad((world[i]->query_attack())->query_name(),20));
       else
         write(pad("  ----",20));
       write(environment(world[i])->short());
      write("\n");
    }
  }          
  write(
"[--------------------------------------------------------------------]\n");
  return 1;
}
view_room(str) {
  object targ,ob;
  
  targ=find_object(str);
  write(targ->short()+"\n");
  targ->long();
  ob=first_inventory(targ);  
  while(ob) {
    write(ob->short()+"\n");
    ob=next_inventory(ob);    
  }
  write("\n");
}
remove_exit(str) {
  string junk;
  int i;

  for(i=0; i<sizeof(dest_dir); i+=2)
    if(sscanf(dest_dir[i],"%s"+str,junk) > 0) {
      dest_dir-=({ dest_dir[i] });
      dest_dir-=({ dest_dir[i] });
    }
}
block() {
  write("You cannot do that here.\n");
  FTELL(TPN+" attempted to "+query_verb()+".\n");
  return 1;
}
