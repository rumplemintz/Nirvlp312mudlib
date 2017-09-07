#include <ansi.h>
#include <strings.h>
#include <regexp.h>
#include "/sys/guilds.h"

#if 0
#define DOUB 1
#endif
#if 1
#define TRIP 1
#endif

string *my_key;

id(string str) {
#if 0
  tell_object(environment(), "Test ID called for: "+str+"\n");
#endif
   return str == "test" || str == "tester";
}

void
init() {
  add_action("test", "test");
  add_action("tst", "tst");
}
reset(arg){
  int depth;
  object wiz;

  if(arg) return;
}

short() { 
  return "Tester";
}

long() {
  cat("/players/angel/area/stargate/obj/gate");
}

test(string str) {
  object obj;
  obj = find_player("dragtst");

#ifndef DOUB 
#ifndef TRIP
  write("DOUB/TRIP Not defined, do extra exp.\n");
#endif
#endif
  if( obj && obj->query_extra_exp_check() ) 
    write("Extra EXP ON.\n");
  else
    write("Normal exp.\n");
  return 1;
}

int tst( string str) {
  string s1,s2,s3;
  s1 = "xxxxxxxxxxx";
  s2 = "yyyyyyyyyyyyyy";
  s3 = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
  write("\n"+pad("",70,'-')+"\n");
  write(pad(str,-35 - strlen(str)/2)+"\n");
  write(pad(s1,-35 - strlen(s1)/2)+"\n");
  write(pad(s2,-35 - strlen(s2)/2)+"\n");
  write(pad(s3,-35 - strlen(s3)/2)+"\n");
  write(pad("",70,'-')+"\n");
  return 1;
}

get() { return 1; }
drop() { return 1; }
query_weight() { return 0; }
query_value() { return 0; }

