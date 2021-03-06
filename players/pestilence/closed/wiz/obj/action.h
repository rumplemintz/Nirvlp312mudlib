#define CMD_DIR "/players/pestilence/closed/wiz/cmds/"
#define ATT USER->query_attack()
/* defined elsewhere. duplicate. ld no like -Bp
static string *cmds;
*/
int here;

/*
guild_update() {
    if (USER->query_attack()){
        write("You can't update while fighting.\n");
        return 1;
    }
  move_object(clone_object("/players/pestilence/closed/dark/dark.c"),tp);
  write("<"+
HIK+"Dark Order"+NORM+"> Guild Status Updated.\n");
  destruct(this_object());
return 1; }
*/


add_cmds() 
  {
   int x; string cmd;
   cmds = get_dir(CMD_DIR);
   for(x=0;x<sizeof(cmds);x++)
   if(sscanf(cmds[x],"%s.c",cmd)) 
     {
#ifndef __LDMUD__ /* Rumplemintz */
     if(cmd == "\"") 
       { 
       add_action("cmd_hook"); add_xverb(cmd); 
       }
     else if(cmd == "'") 
       { 
       add_action("cmd_hook"); add_xverb(cmd); 
       }
     else add_action("cmd_hook",cmd); 
#else
    add_action("cmd_hook", cmd, 3);
#endif
     }
#ifndef __LDMUD__ /* Rumplemintz */
   add_action("cmd_emote"); add_xverb(":");
#else
  add_action("cmd_emote", ":", 3);
#endif
  }

cmd_hook(str) 
  {
  string verb;
  verb = query_verb();
  /* sloppy communication bug fix */
  if(verb == "'") 
   { 
    call_other(CMD_DIR+"say.c","main",str); 
      return 1; 
    }
  if(call_other(CMD_DIR+verb+".c","main",str)) 
    return 1; 
  }

cmd_emote(str)
  {
  if(!str) return;
  write("You "+str+"\n");
  TP->remote_say(capitalize(TPRN)+" "+str+"\n");
    return 1;
  }

/*
guild_login(str) {
  if(!str){write("Where do you want to login? (church/guild)\n"); return 1;}
  if(str == "church") {tp->set_home("/room/church.c"); }
  if(str == "guild") {tp->set_home("/players/pestilence/closed/dark/room/hall.c"); }
 write("<"+HIK+"Dark Order"+NORM+"> Your login position has been changed.\n");
  return 1;
}

guild_quit() {
      tp->set_guild_name(0);
      tp->add_exp(tp->query_guild_exp());
     tp->set_home("room/church");
      tp->add_guild_exp(-tp->query_guild_exp());
      tp->add_guild_rank(-tp->query_guild_rank());
          tp->add_exp(-(tp->query_exp()/2));
      tp->set_attrib("sta",1);
          tp->reset(1);
          command("save",tp);
          write("Silly fool, see u on the flip side!\n");
          destruct(this_object());
return 1; } 
*/

save_me(object ob) {
  string file;
  int tellme;
  if(ob) tellme++;
  if(!ob) ob = ENV();
  file = "players/pestilence/closed/dark/members/" + ob->query_real_name();
  if(!save_object(file)) {
    if(tellme) tell_object(ob,"Save error...\n");
    return 0;
    }
  if(tellme) tell_object(ob,"Saving the Dark Order...\n");
  write(""+HIK+"Saving the Dark Order"+NORM+"...\n");
  return 1;

}


restore_me(object ob) {
  string file2;
  int tellme;
  if(ob) tellme++;
  if(!ob) ob = ENV();
  file2 = "players/pestilence/closed/dark/members/" + ob->query_real_name();
  if(!restore_object(file2)) {
  if(tellme) tell_object(ob,"Dark order restoration order...\n");
    return 0;
    }
  if(tellme) tell_object(ob,"Your mark of the Dark Order darkens...\n");
  return 1;
}

