#include "/room/clean.c"
/*
 * This is a proposal of a replacement to std.h. It is used with
 * 'inherit "room/room";'.
 * All global variables below are supposed to be setup by the reset()
 * in the function that inherits this file.
 */

/* An array with destinations and directions: "room/church", "north" ... */
string dest_dir;

/* Short description of the room */
string short_desc;

/* Long description of the room */
string long_desc;

/* Special items in the room. "table", "A nice table", "window", "A window" */
string items;

/* Fact about this room. ex: "no_fight", "no_steal" */
string property;

string listens;
string smells;
/* No castles are allowed to be dropped here */
int no_castle_flag;
int no_exits;
int pk;

gravesite() { return "YES"; }
init() {
    int i;
    add_action("listen","listen");
    add_action("smell","smell");
    if (!dest_dir)
	return;
    i = 1;
    while(i < sizeof(dest_dir)) {
	add_action("move", dest_dir[i]);
	i += 2;
    }
if(pk == 1){
if(this_player()->is_player())
    this_player()->set_fight_area();
}
call_out("getweather",1);
}

exit(){
  if(this_player())
  if(this_player()->is_player()) this_player()->clear_fight_area();
remove_call_out("getweather");
}
id(str) {
    int i;
    if (!items)
	return;
    while(i < sizeof(items)) {
	if (items[i] == str)
	    return 1;
	i += 2;
    }
    return 0;
}

getweather(){
if(random(60) == 2){
say("Rain gently falls from the dark sky above.\n");
}
if(random(55) == 2){
say("A frigid wind wails by, making you shiver to the bone.\n");
}
call_out("getweather",10);
}
listen(str){
int i;
    if(!listens){
      notify_fail("You don't hear anything.\n");
   return 0;
}
  if(!str){
    str = "default"; }
    while(i < sizeof(listens)){
    if(listens[i] == str){
    write(listens[i+1] + ".\n");
    return 1;
}
    i+= 2;
}
write("You can't hear that.\n");
return 1;
}

smell(str){
int i;
    if(!smells){
      notify_fail("You dont smell anything.\n");
    return 0;
}
    if(!str){
    str = "default"; }
    while(i < sizeof(smells)){
    if(smells[i] == str){
    write(smells[i+1]+".\n");
    return 1;
}
    i+= 2;
}
write("You can't smell that.\n");
return 1;
}

long(str) {
    int i;
    if (set_light(0) == 0){
       write("It is dark.\n");
       return;
    }
    if (!str) {
	write(long_desc);
if(!dest_dir || no_exits)
	    write("    No obvious exits.\n");
	else {
	    i = 1;
	    if (sizeof(dest_dir) == 2)
		write("    There is one obvious exit:");
	    else
		write("    There are " + convert_number(sizeof(dest_dir)/2) +
		      " obvious exits:");
	    while(i < sizeof(dest_dir)) {
		write(" " + dest_dir[i]);
		i += 2;
		if (i == sizeof(dest_dir) - 1)
		    write(" and");
		else if (i < sizeof(dest_dir))
		    write(",");
	    }
	    write("\n");
	}
	return;
    }
    if (!items)
	return;
    i = 0;
    while(i < sizeof(items)) {
	if (items[i] == str) {
	    write(items[i+1] + ".\n");
	    return;
	}
	i += 2;
    }
}

reset(){
int i;
int n;
n = 0;
while(random(2) == 1 && n != 3){
n++;
move_object(clone_object("/players/wocket/graveyard/niblet.c"),this_object());
}
if ( random(2) == 1 ){
    pk = 1;
}
}

/*
 * Does this room has a special property ?
 * The 'property' variable can be both a string and array of strings.
 * If no argument is given, return the 'property' variable.
 */
query_property(str) {
    int i;
    if (str == 0)
	return property;
    if (!property)
	return 0;
    if (stringp(property))
	return str == property;
    while(i < sizeof(property)) {
	if (property[i] == str)
	    return 1;
	i += 1;
    }
    return 0;
}

move(str) {
    int i;

    i = 1;
    while(i < sizeof(dest_dir)) {
	if (query_verb() == dest_dir[i]) {
	    this_player()->move_player(dest_dir[i] + "#" + dest_dir[i-1]);
	    return 1;
	}
	i += 2;
    }
}

short() {
  int i;
  string temp;
    if (set_light(0))
	{
	  temp = short_desc + " [";
	  if (!dest_dir || no_exits) temp += "no exits";
	  else
	    for (i=1;i<sizeof(dest_dir);i+=2)
                {
	          temp += translate_exit(dest_dir[i]);
                  if (i < sizeof(dest_dir)-2) temp += ",";
		}
	  temp += "]";
          return temp;
	}
    return "Dark room";
}

translate_exit(str) {
  if (str == "north") return "n";
  if (str == "south") return "s";
  if (str == "east") return "e";
  if (str == "west") return "w";
  if (str == "northeast") return "ne";
  if (str == "northwest") return "nw";
  if (str == "southeast") return "se";
  if (str == "southwest") return "sw";
  if (str == "up") return "u";
  if (str == "down") return "d";
  return str;
}

query_dest_dir() {
    return dest_dir;
}

query_long() {
    return long_desc;
}

/*
 * Convert a number to a word. The array is being created by the
 * standard room/room, and shared by all rooms.
 */
string numbers;

convert_number(n) {
    if (!pointerp(numbers))
	numbers = query_numbers();
    if (n > 9)
	return "lot of";
    return numbers[n];
}

query_numbers() {
    if (!numbers) {
	if (object_name(this_object()) == "room/room")
	    numbers = ({"no", "one", "two", "three", "four", "five",
			    "six", "seven", "eight", "nine" });
	else
	    numbers = call_other("room/room", "query_numbers");
    }
    return numbers;
}

query_drop_castle() {
    return no_castle_flag;
}
