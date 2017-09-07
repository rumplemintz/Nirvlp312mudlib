#include <ansi.h>

object who;

reset(arg)
{
  if(arg) return;
  set_light(1);
  enable_commands();
}

long()
{
  write(BOLD+"A large bubble of Dark Matter.\n"+
             "There is only one visible exit: leave.\n\n");
  write(NORM);
  return 1;
}
      
short(){ return BOLD+"Dark Matter Arena"+NORM; }

init()
{ 
  add_action("leave_it", "leave");
  add_action("quit","quit");
  add_action("enter", "enter");
}

realm(){ return "NT"; }

leave_it()
{
  tell_object(this_player(), 
    "You leave the arena.\n");
  write_file("/players/chip/venom2/log/left_arena",
  this_player()->query_name()+" left the arena.");
  
  if(present("symbiote", this_object()))
  {
    present("symbiote", this_object())->remove_recruit_attempt();
    write_file("/players/chip/venom2/log/left_arena",
               "Symbiote was still there!\n");
  }
  
  else
  {
    write_file("/players/chip/venom2/log/left_arena",
               "Symbiote was dead!\n");
  }
  
  move_object(this_player(), "/players/fred/closed/venom/symb_room");
  command("look", this_player());
  destruct(this_object());
  return 1;
  }

catch_tell(string str)
{
  string what;
  string what1;
  tell_room("/players/chip/workroom.c",
  str);
}			
