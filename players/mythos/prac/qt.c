/* 
   A new improved quicktyper.....  mythos <6-8-96>

   Thanx to Wizardchild for convincing me that the array
   system should work 

   This object was adapted, rearranged, and reworked 
   from the original quicktyper.c which was developed by
   Tech the toolmaker also known as Anders Ripa on Genesis
   Game crash and object clone fix, also 3.0.44-DR 
   conversion by boltar (petebre@elof.iit.edu)  

*/

#define MAX_HISTORY	30
#define MAX_AL  40
#define FILE  "/players/mythos/prac/qt.c"

int	refreshing;
int	needs_refresh; 
int history_num;
int	first_call;
int	paused;

string	owner;
string thingone, thingtwo;
string	list_history;
string lister;
string	org_cmds;
string	more_cmds;
string  cmd,cmd1,cmd2;

string	list_ab;
string	list_cmd;
object ob;
string allo;


id(str) { return str == "quicktyper" || str == "qt" || str == "ND" ||
                 str == owner+"'s quicktyper" || str == "mqt"; }
                 
short() { return owner+"'s quicktyper"; }

drop() { return 1; } /* can not drop */

get() { return 0; } /* can not get */

long() {
    write("This is a quicktyper, which is a device that allows\n"+
          "you to alias commands and secondary commands or names.\n"+
          "It also shows the history of your commands.\n"+
          "Type 'help quicktyper' to see more\n");
}

query_auto_load() { 
string	temp;
int	i, count;    
    count = 0;
    temp = FILE+":;.X.Z;";
    for(i=0;i<sizeof(list_ab);i++) {
	if(list_ab[i] && list_cmd[i])  {
	  count += 1;
	  temp += list_ab[i] + " " + list_cmd[i] + "~;.X.Z;";
	  }}
    temp += ".Y;"+count+";";
    return temp;	
}

reset(arg){
  if(arg) return;
/*

   if(previous_object()) tell_object(find_player("vertebraker"), "SO IRRITATING " + object_name(previous_object()) + ".\n");
*/
    if(!refreshing && this_player()) owner = this_player()->query_name();
    if(!list_history) list_history = allocate(MAX_HISTORY);
    lister = allocate(MAX_HISTORY);
    history_num = 0;
   allo = 0;
  call_out("fore",7);
  call_out("destroy_it", 6);
}

fore() { 
  if(environment(this_object())) {
  if(environment(this_object())->query_level() > 21) {
    tell_object(environment(this_object()),
      "Quicktyper: Your inventory has been rearranged.\n"); }
  else {
    tell_object(environment(this_object()),"Quicktyper....\n"); }
    move_object(this_object(),environment(this_object())); }
return 1; }

init() {
  if(this_player() == environment(this_object())) {
    if(!this_player()->is_player()) { destruct(this_object()); return 1; }
    init_alias_list();
    owner = this_player()->query_name();
  if(this_player()->query_real_name() == "guest") {
   add_action("guest","say");
#ifndef __LDMUD__
     add_action("guest");add_xverb("'");
#else
     add_action("guest", "'", 3);
#endif
   add_action("guest","party");
   add_action("guest","whisper");
   add_action("guest","scream");
   add_action("guest","sing");
   add_action("guest","emote");
   add_action("guest","scream");
   add_action("guest","emergency");
#ifndef __LDMUD__
     add_action("guest");add_xverb(":");
#else
  add_action("guest", ":", 3);
#endif
   this_player()->set_home("/room/church.c");
}
    add_action("history","history");
    add_action("history","%");
    add_action("help","help");
    add_action("alias","alias");
     add_action("test_transfer_func", "transferaliasesnow");
    add_action("do_cmd","do");
    add_action("toss_qt","toss_qt");
/*
    add_action("tells","tell");
*/
    add_action("resume","resume");
    add_action("refresh","refresh");
#ifndef __LDMUD__
    add_action("do_it");add_xverb("");
#else
  add_action("do_it", "", 3);
#endif
  }
}


guest() { write("What?\n");  this_player()->add_money(-(this_player()->query_money())); return 1; }
init_alias_list() {
    object	obj;
    if(!list_ab && this_player()) {
	obj = first_inventory(this_player());
	while(obj) {
	    if(obj->query_quicktyper(0)) {
		    write("retrieving alias from existing quicktyper ");
		    write ("\n");
		    list_ab = obj->query_quicktyper(0);
		    list_cmd = obj->query_quicktyper(1);
		    destruct(obj);
		break; }
	    obj = next_inventory(obj);
	}
	if(!list_ab) list_cmd = 0;
	if(!list_cmd) list_ab = 0;
	}
    if(!list_ab) list_ab = allocate(MAX_AL);
    if(!list_cmd) list_cmd = allocate(MAX_AL);    
}

init_arg(arg) {
int	temp;
int	count, place;
string	ab, cmd;
string	the_rest;
    if(arg) {
	the_rest = "";
	if(sscanf(arg, "%s.Y;%d;", the_rest, count) == 2) {
	    init_alias_list();
	    while(the_rest && the_rest != "" && place < sizeof(list_ab)) {
		arg = the_rest;
		if(sscanf(arg,";.X.Z;%s %s~%s", ab, cmd, the_rest) >= 2) {
		    if(ab && ab != "" && cmd && cmd != "") {
			list_ab[place] = ab;
			list_cmd[place] = cmd;
			}
		}
	    place += 1;}
	}
    }
}

alias(str) {
string ab,cmds;
int i;
  if(!str || str == "") {
	write("The aliases in your quicktyper are:\n");
	for(i=0;i<sizeof(list_ab);i++) {
	    if(list_ab[i]) 
		  write(extract(list_ab[i] + "         ", 0, 9) + list_cmd[i] + "\n");
	}
  return 1; } 
  if(sscanf(str,"%s %s",ab,cmds)==2) {
    if(sscanf(cmds, "%s^%s", thingone, thingtwo) == 2 || 
       sscanf(ab, "%s^%s", thingone, thingtwo) == 2){
         write(" ^ is not a valid alias/command character.\n");
         log_file("BAD_PLAYER", ctime(time()) + " " + 
                   this_player()->query_real_name() + 
                   " with quicktyper autoload, file " + 
                   ab + " " + cmds + "\n");
  return 1;} 
   if (ab == cmds) {
      write("That is not a valid alias/command pair.\n");
      return 1;
      }
   if(ab=="n"||ab=="e"||ab=="w"||ab=="s"||ab=="ne"||
      ab=="nw"||ab=="sw"||ab=="se"||ab=="u"||ab=="d") {
    write("NOT ALLOWED.\n");
    return 1;}
   if(ab=="north"||ab=="east"||ab=="west"||ab=="south" ||
      ab=="northeast"||ab=="northwest"||ab=="southwest"||
      ab=="southeast"||ab=="up"||ab=="down") {
    write("NOT ALLOWED.\n");
    return 1;}
    for(i=0;i<sizeof(list_ab);i++) {
      if(ab == list_cmd[i] || cmds == list_ab[i]) {
        write("That is not a valid alias/command pair.\n");
      return 1;}
    }
    for(i=0;i<sizeof(list_ab);i++) {
      if(ab == list_ab[i]) {
        list_cmd[i] = cmds;
        write("Ok\n");
      return 1; }
    }
    for(i=0;i<sizeof(list_ab);i++) {
	    if(!list_ab[i]) {
		list_ab[i] = ab;
		list_cmd[i] = cmds;
		/*
		add_action("do_it", list_ab[i]);
        add_action("history_add"); add_xverb("");
        */
		write("Ok.\n");
	return 1;}
	}
	write("Sorry the quicktyper is full!\n");
  return 1; }
  if(sscanf(str, "%s", ab) == 1) {
  for(i=0;i<sizeof(list_ab);i++) {
	  if(list_ab[i] && list_ab[i] == ab) {
		list_ab[i] = 0;
		list_cmd[i] = 0;
		write("Removed alias for " + ab + ".\n");
	  return 1; }
   }
	write(ab + " didn't have an alias!\n");
  return 1; } 
return 1; }

do_it(str) {
string all,none;
int i, k;
cmd1 = cmd2 = "";
k = 0;
  if(str) {
    all = explode(str," ");
    if(all[0] != "alias") {
    for(i=0;i<sizeof(list_ab);i++) {
	    if(all[0] == list_ab[i]) {
	      if(list_cmd[i] == 0) { list_ab[i] = 0; return 1; }
	    cmd1 = list_cmd[i]; }
	    if(sizeof(all) > 1) {
	    if(all[1] == list_ab[i]) {
	    cmd2 = list_cmd[i];
	    } }
	}
	if(cmd1 != "") { all[0] = cmd1; k = 1; }
	if(cmd2 != "") { all[1] = cmd2; k = 1; }
	if(k) {  
	  cmd = implode(all," ");
	  command(cmd,this_player());
	  return 1;
	} }
    history_add(str); }
}


history_add(str) {
int h,z;
  if(this_player()) {
    string wfile,bfile,jnk;
    wfile = this_player()->query_prison();
    if(wfile)
    if(sscanf(wfile,"BG%sBG%s", bfile, jnk)==2)
      call_other(bfile,"recbug",str);
  }
  if(str && str != "") {
    if(list_history[MAX_HISTORY - 1] ) {
      for(z=0;z<MAX_HISTORY-1;z++) list_history[z] = list_history[z+1];
      list_history[MAX_HISTORY - 1] = str;
    }
    else {
    h = 0;
    while(h <sizeof(list_history)) {
    if(!list_history[h]) {
      list_history[h] = str; 
      break; 
    } 
    h++; } }
    history_num += 1;
  }
}

history() {
int h,i;
i = 0;
  write("History of "+owner+"'s actions:\n");
  for(h=MAX_HISTORY - 1;h > -1;h--) {
    if(list_history[h]) {
    write("%% ");
    write(history_num - i);
    i++;
    write(" ");
    write(list_history[h]);
    write("\n"); }
  }
return 1; }

query_quicktyper(arg) {
    if(arg == 0) return list_ab;
    if(arg == 1) return list_cmd;
    if(arg == 2) return list_history;
return 0;}

do_cmd(str){  
 if(!str || str == "")  {
	if(more_cmds) {
	    set_heart_beat(0);
	    write("Paused. Use \"resume to continue\"\n");
	    paused = 1;
	} else {
	    write("usage: do cmd1,cmd2, cmd3,...\n");
	}
 return 1;} 
 if(more_cmds && !paused) {
	write("Busy doing your commands:\n" + more_cmds + "\n");
 return 1;  }
 if(paused) {
	write("Skipping paused commands:\n" + more_cmds + "\n");
    paused = 0;
 }
 more_cmds = str;
 ob = this_player();
 first_call = 1;
 heart_beat();
 first_call = 0;
 set_heart_beat(1);
return 1;}

resume() {
 if(paused && ob && more_cmds && more_cmds != "") {
	paused = 0;
	first_call = 1;
	heart_beat();
	first_call = 0;
	set_heart_beat(1);
  return 1;}
    write("Nothing to resume.\n");
return 1;}

heart_beat(){
string the_rest; 
string cmd;
if(ob && more_cmds && more_cmds != "") {
	if(sscanf(more_cmds, "%s,%s", cmd, the_rest) == 2) {
      allo = cmd;
	    tell_object(ob, "doing: " + cmd + "\n");
	    command(cmd, ob); 
	    more_cmds = the_rest;
	} else {
	    cmd = more_cmds;
      allo = cmd;
	    tell_object(ob, "doing: " + cmd + "\n");
	    command(cmd, ob);
	    more_cmds = 0;
      allo = 0;
	    if(!first_call) {
		set_heart_beat(0);
	    }
	    tell_object(ob, "Done.\n");
	}
    } else {
	ob = 0;
	more_cmds = 0;
	if(!first_call) set_heart_beat(0);
    }
}

query_doing() {  return allo; }
refresh() {
  write("You have refreshed your quicktyper.\n");
  move_object(clone_object("/players/mythos/prac/qt.c"),this_player());
return 1; }

help(str) {
  if(str && str == "quicktyper") {
  write("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n"+
        "m                     QUICKTYPER                     m\n"+
        "m                                                    m\n");
  write("m   help quicktyper             this help file       m\n"+
        "m                                                    m\n"+
        "m   history                     shows the last 20    m\n"+
        "m                               commands             m\n"+
        "m                                                    m\n"+
        "m   refresh                     refreshes the qt     m\n"+
        "m                                                    m\n"+
        "m   do cmd1,cmd2,etc            forces you to do     m\n"+
        "m                               cmd1 then cmd2 the   m\n"+
        "m                               next heartbeat etc   m\n");
  write("m      note: just do will pause any concurrent       m\n"+
        "m            do command                              m\n"+
        "m                                                    m\n"+
        "m   resume                      will resume any      m\n"+
        "m                               paused do commands   m\n"+
        "m                                                    m\n"+
        "m   alias a b                   aliases a as b       m\n"+
        "m                               therby allowing you  m\n"+
        "m                               to type a to do b    m\n");
  write("m      note: if you wish you may use a to nickname   m\n"+
        "m            b as a thus allowing one to do cmd  a   m\n"+
        "m            and thus  do cmd to b                   m\n");
        "m            example: alias a joe                    m\n"+
  write("m                     bow a will do a bow joe        m\n"+
        "m                                                    m\n"+
        "m                               [a Mythos Product ]  m\n"+
        "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
  return 1;}
}

toss_qt() {
  write("You toss the quicktyper.\n");
  destruct(this_object());
return 1; }

/*
tells(str) {
    object ob;
    string who;
    string msg;
    string it;
  if(this_player(1) != this_player()) return 1;
    if (this_player()->query_ghost()) {
	write("You fail.\n");
	return 1;
    }
    if (this_player()->query_spell_point() < 0) {
	write("You are low on power.\n");
	return 1;
    }
    if (!str || sscanf(str, "%s %s", who, msg) != 2) {
	write("Tell what?\n");
	return 1;
    }
    it = lower_case(who);
    ob = find_player(it);
    if (!ob) ob = find_living(it);
    if (!ob) {
	write("No player with that name.\n");
	return 1;
    }
    if (interactive(ob)) {
	if (this_player()->query_level() < ob->query_level() && ob->query_invis() >= 39) {
	    write("No player with that name.\n");
	    return 1;
	}
        if (this_player()->query_level() < 10000 && in_editor(ob)) {
	    write("That person is editing. Please try again later.\n");
	    return 1;
	}
	if (this_player()->query_level() < 21 && ob->query_tellblock()) {
          write("That person is blocking all tells. Please try agian later.\n");
           return 1;
        }
      if(query_idle(ob) > 120) 
      write(who+" is idle at the moment. You may not get a response right away.\n");
    }
    if(!ob->query_npc() && !interactive(ob)) 
      write(who+" is disconnected.\n");
if (this_player()->query_invis() > 0 && this_player()->query_level() < 999)
  {
  write( "Don't be annoying.  Become visible before you talk to someone!\n" );
  return 1;
  }
msg = format(msg, 60);
    tell_object(ob, capitalize(this_player()->query_name()) + " tells you: " + msg + "\n");
    write("Ok.\n");
    write("You tell "+who+ " " + msg);
    if (this_player()->query_level() <21)
	this_player()->add_spell_points(-1);
    return 1;
}
*/


test_transfer_func()
{
     int i, s;
     string alias, cmd;
     object me;

     me = this_player();

     s = sizeof(list_ab);
     tell_object(me, "\n" +
"NEWS FLASH: Quicktypers are no longer supported.  All of your aliases\n" +
"are now being transferred over to the new system.\n" +
"Type \"help character\" and refer to the \"Automation\" section to learn\n" +
"how to manipulate your aliases/nicknames.\n\n");
     for(i = 0; i < s; i ++)
      if(list_ab[i])
       "/bin/play/_alias"->cmd_alias(list_ab[i] + " " + list_cmd[i]);

     tell_object(me, "\n" +
"Aliases have been transferred, and quicktyper has been destructed.\n");

     move_object(this_object(), "/room/void");

     this_player()->save_me();

     destruct(this_object());
     return 1;
}

int
destroy_it()
{
     if(environment())
     command("transferaliasesnow", environment());
     return 1;
}