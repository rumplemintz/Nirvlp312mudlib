/*
  nooneelse_bull_board.c - new version of bull_board that allows setting the
                           file name and directory of the saved file
*/

string board_message_file, messages, new_hd, new_body;
int num_messages;
object who;

id(str) {
  return str == "map board" || str == "board" || str == "bulletinboard";
}

long() {
  write("You can read maps here.\n");
  write("Read a map with 'read num'or type 'DOORS' to goto the hall of doors\n");
  write("\n");
  if (num_messages == 0) {
    write("It is empty.\n");
    return;
  }
  write("The map board contains "+num_messages);
  if (num_messages == 1)
      write(" map:\n\n");
  else
      write(" maps:\n\n");
  say(this_player()->query_name()+" studies the map board.\n");
  headers();
}

short() { return ("A map board"); }


get() {
  write("It is secured to the ground.\n");
  return;
}

init() {
  
  add_action("read",   "read");
  add_action("doors", "doors");
  }

reset(arg) {
  if (arg) return;

   board_message_file = "players/catwoman/maps/map_board_save";
  restore_object(board_message_file);
 
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
    write(i+":\t"+hd+"\n");
    i += 1;
 
  }
}

doors(){
	call_other(this_player(),"move_player", "doors#players/catwoman/hall2");
	return 1;
}
rummy(){
	call_other(this_player(),"move_player", "east#players/catwoman/workroom");
	return 1;
}
read(str) {
  string hd, body, rest;
  int i, tmp;

  if (str == 0 || (sscanf(str, "%d", i) != 1 && sscanf(str, "note %d", i) != 1))
    return;
 
  if (i > num_messages) {
    write("Not that number of maps.\n");
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
      say(this_player()->query_name()+" reads a map titled '"+hd+"'.\n");
      write("The map is titled '"+hd+"':\n\n");
      write(body);

      return 1;
    }
  }
  write("Hm. This should not happen.\n");
}
