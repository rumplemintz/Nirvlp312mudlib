#include "../def.h"

string messages, new_hd, new_body;
string nm;
int num_messages;
object who;

id(str){ return str == "board" || str == "bulletin board"; }

long(){
  if(TP->query_guild_name() != "samurai") return;
  write(
"This bulletin board is attached to the northern wall of the room.  It\n"+
"is here so that important messages can be saved for everyone to 'read'.\n\
You can also type \"note <msg>\" to post a note of your own.\n");
  if(num_messages == 0)
  {
    write("Right now the board is empty.\n");
    return;
  }
  write("The bulletin board contains "+num_messages);
  if(num_messages == 1)
    write(" messages:\n\n");
  else
    write(" messages:\n\n");
  say(this_player()->query_name()+" studies the bulletin board.\n");
  headers();
}

short(){
  if(num_messages)
    return ("GC bulletin board "+GRN+"[" + num_messages + "]"+NORM);
  else
    return "GC bulletin board";
}

drop(){              return 1; } 
get(){               return 0; }
can_put_and_get(){   return 0; }

init(){
  add_action("new","note");
  add_action("read","read");
  add_action("remove","remove");
}

reset(arg){
  if(arg) return;
  
  restore_object("players/vertebraker/guilds/samurai/obj/gc_board");
}

headers(){
    string hd, body, rest;
    int i, tmp;

    i = 1;
    rest = messages;
    while(rest != 0 && rest != "") {
	tmp = sscanf(rest, "%s:\n**\n%s\n**\n%s", hd, body, rest);
	if (tmp != 2 && tmp != 3) {
	    write("Corrupt.\n");
	    return;
	}
	write(i + ":\t" + hd + "\n");
	i += 1;
    }
}

new(hd) {
  if(this_player()->query_guild_name() != "samurai"
    && this_player()->query_level() < 60) return 0;
    if (!hd)
	return 0;
    if (who && environment(who) == environment(this_object())) {
	write(call_other(who, "query_name") + " is busy writing.\n");
	return 1;
    }
    if (num_messages == 50) {
	write("An old note must be erased first.\n");
	return 1;
    }
    if (strlen(hd) > 50) {
	write("Too long header to fit the board.\n");
	return 1;
    }
    new_hd = "";
    new_hd = hd;
    input_to("get_body");
    write("Give message, and terminate with '**'.\n");
    write(">");
    new_body = "";
    return 1;
}

get_body(str) {
    if (str == "**") {
	new_hd = new_hd + "("+this_player()->query_real_name()+")";
	messages = messages + new_hd + ":\n**\n" + new_body + "\n**\n";
	num_messages += 1;
	new_body = 0;
	new_hd = 0;
        save_object("players/vertebraker/guilds/samurai/obj/gc_board");
	write("Ok.\n");
	who = 0;
	return;
    }
    new_body = new_body + str + "\n";
    write(">");
    input_to("get_body");
}

read(str) {
    string hd, body, rest;
    int i, tmp;

  if(this_player()->query_guild_name() != "samurai"
    && this_player()->query_level() < 60) return 0;

    if (str == 0 || (sscanf(str, "%d", i) != 1 &&
		     sscanf(str, "note %d", i) != 1))
	return 0;
    if (i > num_messages) {
	write("Not that number of notes.\n");
	return 1;
    }
    rest = messages;
    while(rest != 0 && rest != "") {
	i -= 1;
	tmp = sscanf(rest, "%s:\n**\n%s\n**\n%s", hd, body, rest);
	if (tmp != 2 && tmp != 3) {
	    write("Corrupt.\n");
	    return;
	}
	if (i == 0) {
	    say(call_other(this_player(), "query_name") +
		  " reads a note titled '" + hd + "'.\n");
	    write("The note is titled '" + hd + "':\n\n");
	    write(body);
	    return 1;
	}
    }
    write("Hm. This should not happen.\n");
}

remove(str) {
    string hd, body, rest;
    string jun2,jun;
    int i, tmp;
    if (str == 0 || (sscanf(str, "%d", i) != 1 &&
		     sscanf(str, "note %d", i) != 1))
	return 0;
    if (i > num_messages) {
	write("Not that number of notes.\n");
	return 1;
    }
    rest = messages;
    jun2 = messages;
    messages = "";
    while(rest != 0 && rest != "") {
	i -= 1;
	tmp = sscanf(rest, "%s:\n**\n%s\n**\n%s", hd, body, rest);
	if (tmp != 2 && tmp != 3) {
	    write("Corrupt.\n");
	    return;
	}
	if (i == 0) {
        nm = this_player()->query_real_name();
        if(sscanf(lower_case(hd),"%s"+nm, jun) != 1 && TP->query_guild_rank() < 11)
        {
          write("You cannot remove somebody else's note.\n");
          messages = jun2;
          return 1;
        }
            write("Ok.\n");
            say(capitalize(nm)+" removed a note titled "+hd+".\n");
      	    messages = messages + rest;
	    num_messages -= 1;
            save_object("players/vertebraker/guilds/samurai/obj/gc_board");
	    return 1;
	}
	messages = messages + hd + ":\n**\n" + body + "\n**\n";
    }
    write("Hm. This should not happen.\n");
}
