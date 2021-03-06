inherit "/obj/treasure";
string id_str;
int worn;
/*
set_short(str) { short_desc = str; }
set_long(str) { long_desc = str; }
*/
set_ident(str) { id_str = str;}
short() {
   if(worn) return short_desc + " (worn)";
   return short_desc;
   }
long() { write(long_desc + "\n");
   }
wear(str) {
   if(!str || str != id_str) {
      return 0;
      }
     if(environment() != this_player()) {
      write("You must get it first!\n");
      return 1;
      }
   if(worn) {
      write("You already wear it!\n");
      return 1;
      }
    worn = 1;
    write("You wear a "+id_str+"\n");
    say(this_player()->query_name() + " wears a "+id_str+"\n");
    return 1;
}
remove(str) {
   if(!str || str != id_str) {
      return 0;
      }
   if(!worn) {
      write("You are not wearing it!\n");
      return 1;
      }
    worn = 0;
    write("You remove a "+id_str+"\n");
    say(this_player()->query_name() + " removes a "+id_str+"\n");
    return 1;
}
init() {
   add_action("wear","wear");
   add_action("remove","remove");
short_desc="A beautiful white maternity wedding dress";
long_desc="A long white wedding, maternity dress made of light soft fabric";
id_str="dress";
set_no_clean(1);
    if(environment(this_object()))
   if(!environment(this_object())->query_pregnancy()) destruct(this_object());
   }
query_value() { return 5; }
query_weight() { return 1; }
drop(silently) {
     return 1;
   if(worn) {
    worn = 0;
    write("You remove the "+id_str+"\n");
   }
   return 0;
}
id(str) { return str == id_str || str == short_desc;
  }
generic_object() { return 1; }
restore_thing(str){
      restore_object(str);
      return 1;
   }
save_thing(str){
      save_object(str);
      return 1;
   }
query_auto_load() { return "players/boltar/things/L2.c:";}
