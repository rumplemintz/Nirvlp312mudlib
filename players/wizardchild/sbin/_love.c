#include "/bin/ghost.c"
 
#pragma strict_types
#pragma save_types
 
int cmd_love(string str) {
  object who;
  if(ghost() || !str)
    return 0;
  who = present(str, environment(this_player()));
  if(who && living(who)) {
    if(who == this_player())
      return 0;
    write("You tell your true feelings to "+capitalize(str)+".\n");
    tell_object(who, this_player()->query_name()+" whispers to you sweet words of love.\n");
    say(this_player()->query_name()+" whispers softly to "+capitalize(str)+".\n", who);
  } else {
    who = find_player(str);
    if(!who || who == this_player() || in_editor(who) || who->query_invis() >= 20)
      return 0;
    write("You tell your true feelings to "+capitalize(str)+" from afar.\n");
    tell_object(who, this_player()->query_name()+" whispers to you sweet words of love from afar.\n");
  }
  return 1;
}
