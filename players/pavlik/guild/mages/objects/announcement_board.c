#include "/players/pavlik/guild/mages/macs2"
#define NOTES "players/pavlik/guild/mages/obj/announcements"
string messages, new_hd, new_body;
int num_messages;
object who;

id(str) {
  return str == "announcements" || str == "bboard" || str == "book"
  || str == "board";
}

long() {
  write(
  "This board is now open to all Mages for posting questions, comments, etc.\n"+
  "Feel free to write whatever you like but please be respective of others\n"+
  "thoughts and feelings.\n\n"+
  "Use 'post <subject>' to write a note.\n\n");

  if (num_messages == 0) {
    write("There are no entries at this time.\n");
        return;
  }
  if (num_messages == 1)
    write("There is 1 notice on the board.\n");
  else
    write("There are "+num_messages+" notes posted.\n");
  
  headers();
}

short() {
  return CYN+"The Mages Announcement Board ["+num_messages+"]"+NORM;
}

get() {
    return 0;
}

init() {
    add_action("new","post");
    add_action("read","read");
    add_action("remove","remove");
}

reset(arg) {
  if (arg)
     return;
  restore_object(NOTES);
}

headers() {
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
    write("page "+i+": "+hd+"\n");
        i += 1;
    }
}

new(hd) {
    if (!hd)
        return 0;
    if (who && environment(who) == environment(this_object())) {
        write(call_other(who, "query_name") + " is busy writing.\n");
        return 1;
    }
    if (strlen(hd) > 50) {
        write("Too long header to fit the paper.\n");
        return 1;
    }
    new_hd = hd;
    input_to("get_body");
    write("Sciribing new note.  End note with '**'.\n");
    write("]");
    new_body = "";
    return 1;
}

get_body(str) {
    if (str == "**") {
        string wday,surplus,month,day;
        int number;
        sscanf(ctime(time()),"%s %s %s %d:%s",wday,month,day,number,surplus);
        new_hd = wday+" "+month+" "+day+"\t | "+new_hd+
        " ("+capitalize(this_player()->query_real_name()) +")";
        messages = messages + new_hd + ":\n**\n" + new_body + "\n**\n";
        num_messages += 1;
        new_body = 0;
        new_hd = 0;
        save_object(NOTES);
        write("Ok.\n");
        who = 0;
        return;
    }
    new_body = new_body + str + "\n";
    write("]");
    input_to("get_body");
}

read(str) {
    string hd, body, rest;
    int i, tmp;

    if (str == 0 || (sscanf(str, "%d", i) != 1 &&
                     sscanf(str, "note %d", i) != 1))
        return 0;
    if (i > num_messages) {
        write("There is no such announcement.\n");
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
                  " reads an entry titled '" + hd + "'.\n");
            write("The entry is titled '" + hd + "':\n\n");
            write(body);
            return 1;
        }
    }
    write("Hm. This should not happen.\n");
}

remove(str) {
    string hd, body, rest,contname;
    int i, tmp;
    contname=this_player()->query_real_name();
    if(this_player()->query_guild_rank() < 72) 
    {
       write("You cannot remove a notice from this board.\n");
       return 1;
     }   

    if (str == 0 || (sscanf(str, "%d", i) != 1 &&
                     sscanf(str, "note %d", i) != 1))
        return 0;
    if (i > num_messages) {
        write("Not that number of messages.\n");
        return 1;
    }
    rest = messages;
    messages = "";
    while(rest != 0 && rest != "") {
        i -= 1;
        tmp = sscanf(rest, "%s:\n**\n%s\n**\n%s", hd, body, rest);
        if (tmp != 2 && tmp != 3) {
            write("Corrupt.\n");
            return;
        }
        if (i == 0) {  
            say(call_other(this_player(), "query_name") +
                  " removed a note titled '" + hd + "'.\n");
            write("Ok.\n");
            messages = messages + rest;
            num_messages -= 1;
        save_object(NOTES);
            return 1;
        }
        messages = messages + hd + ":\n**\n" + body + "\n**\n";
    }
    write("Hm. This should not happen.\n");
}