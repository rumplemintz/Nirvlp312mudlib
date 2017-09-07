#include <ansi.h> /* 2007-10-29 converted to std ansi.h -vital */

id(str) {
    return str == "atell";
}

long() {
    write("An Atell to Arrina\n");
    write("Usage: atell or atelle\n");
}

drop() {return 1;}

query_auto_load() {
    return "/players/arrina/closed/ztell.c:";
}

init() {
  add_action("atell","atell");
  add_action("atelle","atelle");
}
atell (str)
{
string what, who;
  if(!str) {
    write("Atell Arrina what?\n");
  return 1; }
  if(!sscanf(str, "%s",what)) {
    write("Usage: atell [what]\n");
  return 1;}
  if(!find_player("arrina")) {
    write("Arrina is not here....\n");
  return 1; }
  tell_object(find_player("arrina"),HIC+"[]"+"  "+NORM+capitalize(this_player()->query_real_name())+NORM+" atells you: "+GRN+what+NORM+"\n");
  write("You atell Arrina : "+CYN+what+NORM+"\n");
  return 1; 
}

atelle (str) {
string whats;
  if(!str) {
    write("You atelle what to Arrina?\n");
  return 1; }
  if(!sscanf(str, "%s",whats)) {
    write("Usasge: atelle [what]\n");
  return 1; }
  if(!find_player("arrina")) {
    write("Arrina is not here....\n");
  return 1; }
  tell_object(find_player("arrina"),BLU+":)"+capitalize(this_player()->query_real_name())+" "+whats+NORM+"\n");
  write(CYN+"You "+whats+NORM+"\n");
  return 1; }