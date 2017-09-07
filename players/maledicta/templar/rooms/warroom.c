#include "/players/maledicta/ansi.h"
#define tp this_player()
#define tpn this_player()->query_name()
#define tpp this_player()->query_possessive()
#define cross present("KnightTemplar", this_player())
#define DAEMON "/players/maledicta/templar/gdaemon.c"
inherit "room/room";

reset(arg) {
	if(arg) return;
	set_light(1);
	
	short_desc = HIW+"Templar "+NORM+RED+"War Room"+NORM;
	long_desc =
	"  This is the War Room of the Templars.  The stone walls here\n"+
	"are covered with detailed maps of Nirvana.  A large table stands\n"+
	"in the center of the room, a large green glowing orb on its\n"+
	"surface.  A stairway leads down to the Templar's Inner Chamber\n"+
	"room.\n";
	
	items = ({
			"walls",
			"Stone walls that are adorned with maps of the realm",
			"maps",
			"Numerous maps of the realm of Nirvana. They are very detailed",
			"table",
			"A large oak table with a green orb on it",
			"orb",
			"A huge green glowing orb. It is used to communicate to the guards\n"+
			"and control the war effort.  You can 'grasp' it for more information",
			"stairway",
			"A narrow stairway that leads down to the inner chamber",
	});
	
	dest_dir = ({
  "/players/maledicta/templar/rooms/adv_inner","down",
  "/players/jaraxle/templar/rooms/equipment.c","up",
 "/players/jaraxle/templar/rooms/storage.c","east",
	});
	
}


init(){
	::init();
	add_action("grasp_it", "grasp");
	add_action("reinforce", "reinforce");
	add_action("guards", "guards");
	add_action("close", "close");
	add_action("open", "open");
	add_action("repair", "repair");
	add_action("rebuild", "rebuild");
	add_action("funds", "funds");
	add_action("war", "war");
	add_action("status_of_all", "cstatus");
   add_action("up","up");
	this_player()->set_fight_area();
}

exit(){    if(this_player()) this_player()->clear_fight_area();     }


grasp_it(str){
	if(!cross) return 0;
	if(!str){
		write("grasp what?\n");
		return 1;
	}
	if(str == "orb"){
		if(tp->query_guild_rank() < 9){
			write("You are not high enough rank!\n");
			return 1;
		}
		write(
			HIW+"The orb "+HIG+"glows."+NORM+GRN+".."+NORM+"\n\n"+
			"Commands available:\n\n"+
			"guards    - Total guards.\n\n"+
			"reinforce - Add a guard to the castle gate.\n"+
			"            Cost: 5000 castle donation/per guard.\n"+
			"close     - Close the castle gate.\n"+
			"            Cost: 0\n"+
			"open      - Open castle gate.\n"+
			"            Cost: 0\n"+
			"rebuild   - Rebuild the castle gate.\n"+
			"            Cost: 20000 castle donation.\n"+
			"war       - Toggle between War status at the \n"+
			"            castle gate.  This will ready your\n"+
			"            guards to block intruders.\n"+
			"cstatus   - Status of all categories.\n\n"+
		   "funds     - Total funds available.\n\n\n");
		return 1;
	}
	write("grasp what?\n");
	return 1;
}

war(str){
	if(!cross) return 0;
	if(tp->query_guild_rank() < 9){
		write("You are not high enough rank!\n");
		return 1;
	}
	if(DAEMON->query_war()){
		DAEMON->set_war(0);
		write_file("/players/maledicta/templar/logs/DOWNWAR2",
		this_player()->query_real_name()+" "+ctime(time())+"\n");
		send("Standing Down War Status at Castle Gate");
		write("You stand down from War Status.\n");
		return 1;
	}
	else{
		write_file("/players/maledicta/templar/logs/UPWAR2",
		this_player()->query_real_name()+" "+ctime(time())+"\n");
		DAEMON->set_war(1);
		send("CASTLE GUARDS SET TO WAR STATUS");
		write("You raise the alarm and prepare for War!\n");
		return 1;
	}
	return 1;
}


funds(){
	if(!cross) return 0;
	if(tp->query_guild_rank() < 9){
		write("You are not high enough rank!\n");
		return 1;
	}
	write("Total castle donation is at "+DAEMON->query_donation()+".\n");
	return 1;
}

rebuild(str){
	if(!cross) return 0;
	if(tp->query_guild_rank() < 9){
		write("You are not high enough rank!\n");
		return 1;
	}
	if(DAEMON->query_donation() < 20000){
		write("You do not have enough castle donation.\n");
		return 1;
	}
	if(DAEMON->gate2_condition()){
		write("That gate is not destroyed.\n");
		return 1;
	}
	DAEMON->set_gate2_condition(1);
	DAEMON->add_castle_donation(-20000);
	write("You order the Castle Gates rebuilt.\n");
	send("Order sent to rebuild Castle Gate.");
	return 1;
}

guards(){
	if(!cross) return 0;
	if(tp->query_guild_rank() < 9){
		write("You are not high enough rank!\n");
		return 1;
	}
	write(
		"Location:      Total Guards:\n"+
		"Castle Gate    "+DAEMON->query_gl(2)+"\n");
	return 1;
}

close(str){
	if(!cross) return 0;
	if(tp->query_guild_rank() < 9){
		write("You are not high enough rank!\n");
		return 1;
	}
	if(!DAEMON->gate2_condition()){
		write("That gate is destroyed!\n");
		return 1;
	}
	if(DAEMON->gate2() == 1){
		DAEMON->gate2(2);
		send("Closing Castle Gates");
		write_file("/players/maledicta/templar/logs/CLOSEG2",
		this_player()->query_real_name()+" "+ctime(time())+"\n");
		write("You order the Castle Gates closed.\n");
		return 1;
	}
	else{ write("They are already closed.\n"); return 1; }
}

open(str){
	if(!cross) return 0;
	if(tp->query_guild_rank() < 9){
		write("You are not high enough rank!\n");
		return 1;
	}
	
	if(DAEMON->gate2() == 2){
		DAEMON->gate2(1);
		send("Opening Castle Gates");
		write_file("/players/maledicta/templar/logs/OPENG2",
		this_player()->query_real_name()+" "+ctime(time())+"\n");
		write("You order the Castle Gates opened.\n");
		return 1;
	}
	else{ write("They are already opened.\n"); return 1; }
	
	return 1;
}

reinforce(str){
	if(!cross) return 0;
	if(tp->query_guild_rank() < 9){
		write("You are not high enough rank!\n");
		return 1;
	}
	if(DAEMON->query_donation() < 5000){
		write("You do not have enough castle donation.\n");
		return 1;
	}
	
	if(DAEMON->query_gl(2) + DAEMON->query_training(2) > 199){
		write("You already have the maximum number of guards, either in training or\n"+
		"present, for that gate.\n");
		return 1;
	}
	write_file("/players/maledicta/templar/logs/CASTLE_REINFORCE",
	this_player()->query_real_name()+" "+ctime(time())+"\n");
	DAEMON->add_training(2);
	send("Reinforcing Castle Gate Guards");
	DAEMON->add_castle_donation(-5000);
	write("You begin training a guard for duty at the castle gates.\n");
	return 1;
}

status_of_all(){
if(!cross) return 0;
if(tp->query_guild_rank() < 9){
	write("You are not high enough rank!\n");
	return 1;
}
write("Castle status is currently at:\n\n"+
"Castle Gate -  ");
if(!DAEMON->gate2_condition()){
	write("DESTROYED.\n");
}
else{
	write("Ok[");
	if(DAEMON->gate2() == 1){
		write("OPEN]\n");
	}
	else{
		write("CLOSED]\n");
	}
}

write("Castle Gate Guards in training: "+DAEMON->query_training(2)+"\n");
write("Castle Gate Guards: "+DAEMON->query_gl(2)+" ");
if(DAEMON->query_war()){
	write("(WAR)\n");
}
else{ write("\n"); }

write("Castle Funds: "+DAEMON->query_donation()+"\n");
return 1;
}





send(str) {
object list;
object woot;
int i;
list = users();
for(i=0; i<sizeof(list); i++) {
	woot = present("KnightTemplar",list[i]);
	if (woot && !woot->query_block()) {
		tell_object(list[i],
		HIR+"(Templar War) "+str+NORM+"\n");
	}
}
}

up(){
if(!present("KnightInvite",this_player())){
write("You are not allowed access.\n");
return 1; }
}