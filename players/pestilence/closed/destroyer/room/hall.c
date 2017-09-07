#include "/players/pestilence/define.h"
#include "/players/pestilence/ansi.h"
#define TP this_player()
inherit "/players/vertebraker/closed/std/room";
int OPEN;

reset(arg) {
  if(arg) return;

long_desc =
"    This is a large room where players can join Pestilence's Army.\n"+
"To the east is the main training room.  In the south direction is the\n"+
"entrance to the guild complex.  The ceiling is very high.\n"+
"The description of this room will be made more entertaining once Pesty\n"+
"thinks of something to add to it.\n";
set_light(1);

items = ({
});

dest_dir = ({
  "/players/pestilence/closed/destroyer/room/adv.c","east",
  "/players/pestilence/closed/destroyer/room/brief.c","south",
  "/players/pestilence/closed/destroyer/room/whall.c","west",
  "/players/pestilence/hall.c","north",
});
} 
short() {
    return ""+YEL+"Camo"+GRN+"ufla"+YEL+"ged "+GRN+"Ha"+YEL+"ll"+NORM+"";
}

realm() { return "NT"; }

init() {
  ::init();
   add_action("join", "join");
   add_action("join_yes","join_yes");
}

join() {
object spbrd;
int myexp;
object wgob;
int wok;
  if (this_player()->query_guild_name() == "Destroyers") {
    write("You have already joined this guild :)\n");
    return 1;
  }
  if (this_player()->query_guild_exp() >= 1) {
        write("You are already in a guild.\n");
        return 1;
        }
  if(present("destroyer_ob", tp)){
   write("You are already a member of this guild.\n");
   return 1;
   }
if(!wok){
   if(tp->query_guild_name() != 0 || tp->query_guild_exp() || tp->query_guild_rank() || tp->query_guild_file()){
      write("You are already in another guild.\n");
      return 1; 
      }
   if(this_player()->query_level() < 10 || this_player()->query_level() > 10) {
      write("You must be level 10 to join the Destroyers.\nIf you are greater than level 10 you may have your level set\nto 10 and join, by typing join_yes.\n");
      return 1;
      }
  }

  myexp = this_player()->query_exp();
  this_player()->add_exp(-myexp);
  this_player()->add_exp(90000);
  this_player()->add_guild_rank(-this_player()->query_guild_rank());
  this_player()->add_guild_rank(1);
  if(this_player()->query_attrib("mag") > 15) this_player()->set_attrib("mag",15);
  if(this_player()->query_attrib("int") > 10) this_player()->set_attrib("int",10);
  call_other(this_player(),"reset",1);
  call_other(this_player(),"save_me",0);
  write(""+YEL+"Your puny DNA has been removed"+NORM+".\n");
  write("Enhanced DNA has been injected into your body.\nYou are now a member of the Destroyers.\n");
  write_file("/players/pestilence/closed/destroyer/log/join",ctime(time())+" "+this_player()->query_name()+" has joined the Destroyers.\n");
  move_object(clone_object("players/pestilence/closed/destroyer/gob.c"), this_player());
  present("destroyer_ob", TP)->add_combat(1);
  write("You feel your muscles tensing with an unknown strength.\n");
                command("dsave",this_player());
  return 1;
}

join_yes() {
object spbrd;
object wgob;
int myexp;
int wok;
  if (this_player()->query_guild_name() == "Destroyers") {
    write("You have already joined this guild :)\n");
    return 1;
  }
   if(this_player()->query_level() < 10 ) {
      write("You must be atleast level 10 to join the Destroyers.\n");
      return 1;
      } 
  if (this_player()->query_guild_exp() >= 1) {
        write("You are already in a guild.\n");
        return 1;
        }
  if(present("destroyer_ob", tp)){
   write("You are already a member of this guild.\n");
   return 1;
   }
if(!wok){
   if(tp->query_guild_name() != 0 || tp->query_guild_exp() || tp->query_guild_rank() || tp->query_guild_file()){
      write("You are already in another guild.\n");
      return 1; 
      }
  }

  this_player()->add_guild_rank(-this_player()->query_guild_rank());
  this_player()->add_guild_rank(1);
  this_player()->add_guild_exp(1);
  myexp = this_player()->query_exp();
  this_player()->add_exp(-myexp); 
  this_player()->add_exp(90000);
  this_player()->set_level(10);
  this_player()->set_extra_level(0);
  if(this_player()->query_attrib("int") > 10) this_player()->set_attrib("int",10);
  call_other(this_player(),"reset",1);
  call_other(this_player(),"save_me",0);
  write(""+YEL+"Your puny DNA has been removed"+NORM+".\n");
  write("Enhanced DNA has been injected into your body.\nYou are now a member of the Destroyers.\n");
  write_file("/players/pestilence/closed/destroyer/log/join",ctime(time())+" "+this_player()->query_name()+" has joined the Destroyers.\n");
  move_object(clone_object("players/pestilence/closed/destroyer/gob.c"), this_player());
  present("destroyer_ob", TP)->add_combat(1);
  write("You feel your muscles tensing with an unknown strength.\n");
                command("dsave",this_player());
  return 1;
}