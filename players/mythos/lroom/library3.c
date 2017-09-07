#include "/players/mythos/closed/guild/def.h"
inherit "room/room";
string p;
reset(arg) {
if(!present("guard")) {
  move_object(clone_object("/players/mythos/lmon/guard.c"),this_object()); }
  if(!arg) {
  set_light(1);
    short_desc = "Library: ** 3 **";
    long_desc =
    "You stand in a large dark hall connected to rooms filled with books.\n"+
    "People move silently back and forth, to and fro, room to room, as they\n"+
    "search for the knowledge they seek- lands, guilds, people, history, magic,\n"+
    "meaning, life, etc.  This is a place of peace- remember this.\n\n";
  items = ({
    "south","Goes back to the rest of the library",
    "misc","Here are where the odd books are- treatise on war, magic, etc",
  });

  dest_dir = ({
    "/players/mythos/lroom/library2.c","south",
    "/players/mythos/lroom/misc.c","misc",
/*
    "/players/mythos/closed/guild/seclib.c", "north",
*/
  });
} }
realm() {return "NT"; }
init() {
  ::init();
  if( read_file("/players/mythos/lroom/enforcement/"+lower_case(this_player()->query_name())) == "12") {
  write("A Big Buff Guard grabs you by the neck and tosses you out of the Library!\n"+
        "\nYou have disturbed the peace far too much here!\n");
  say("A Big Buff Guard grabs "+this_player()->query_name()+" by the neck and tosses "+
        this_player()->query_objective()+"out of the Library! \n");
  move_object(this_player(),"/players/mythos/lroom/pun.c"); return 1;}

  if(present(fear,this_player())) {
   present(fear,this_player())->set_defence(0);}

  if(this_player()->query_real_name() != "vertebraker") {
    this_player()->stop_hunter();}

  add_action("ssay","say");
  add_action("ssay",";");
#ifndef __LDMUD__
  add_action("ssay");add_xverb("'");
#else
  add_action("ssay", "'", 3);
#endif
  add_action("ssay","gossip");
  add_action("ssay","farsong");
  add_action("ssay","farsonge");
  add_action("ssay","risque");
  add_action("ssay","babble");
  add_action("ssay","junk");
  add_action("zap","kill");
  add_action("zap","magic missle");
  add_action("zap","missle");
  add_action("zap","mi");
  add_action("zap","fireball");
  add_action("zap","fire ball");
  add_action("zap","fi");
  add_action("zap","shock");
  add_action("zap","sh");
  add_action("zap","sonic");
  add_action("zap","so");
  add_action("open","open");
  add_action("initiation","initiation");
  add_action("search","search");
}

ssay() {
  write("The Guard tells you that talking is not allowed here!\n");
return 1;}

zap() {
  if( read_file("/players/mythos/lroom/enforcement/"+ lower_case(this_player()->query_name())) == "1") {
  write_file("/players/mythos/lroom/enforcement/"+ lower_case(this_player()->query_name()),"2");}
  if(!read_file("/players/mythos/lroom/enforcement/"+ lower_case(this_player()->query_name()))) {
    write_file("/players/mythos/lroom/enforcement/"+ lower_case(this_player()->query_name()),"1");}
  write(BOLD+"\n\tNO FIGHTING OR DISTURBANCES HERE!\n\n"+NORM);
  write("A Big Buff Guard grabs you by the neck and tosses you\n"+
        "out of the Library!  Remember, three strikes and you are out!\n");
  say("A Big Buff Guard grabs "+this_player()->query_name()+" by the neck and tosses "+
        this_player()->query_objective()+"out of the Library! \n");
  this_player()->set_crime();
  move_object(this_player(),"/players/mythos/lroom/hall.c");
  return 1;}

initiation() {
if(this_player()->query_real_name() == "vertebraker") {
  write("You press a small indentation in the wall...\n"+
        "You step beyond to the Room of Ceremonies.\n");
  move_object(this_player(),"/players/mythos/closed/guild/init.c");
  return 1;}
  else{ write("What?\n"); return 1;}
  return 1;}

search() {
  if(0==random(2)) { write("You notice a door disguised in the wall.\n"+
                            "Perhaps you could open it.\n");
                            return 1;}
  else {write("You find nothing of interest.\n"); return 1;}
  return 1;}

static open(str) {

  if(str != "door" || !str) {write("What?\n"); return 1;}
   if(this_player()->query_real_name() == "guest") {
    destruct(this_player()); return 1; }
  write("The door opens quietly...\n"+
        "Something asks you:  What is the 1st Principle?\n\nAnswer: ");
  input_to("check",1);
  return 1;}

static check(p) {
  if(!p  || p=="") {write("Denied!\nThe door shuts.\n"); return 1;}
  if(p != answer) {write("Denied!\nThe door shuts.\n"); return 1;}
  write("The door fully opens and you enter the secret library.\n");
  if(!present(pact,this_player())) {write_file("/players/mythos/closed/guild/ill",
            ctime(time())+"\t"+this_player()->query_real_name()+"\n"); }
  move_object(this_player(),"/players/mythos/closed/guild/seclib.c");
  return 1;}