practice_arts(str){
   object comm;
   string who;
   string what;
   string msg;
   string name;
   name = capitalize(this_player()->query_real_name());
   if(sscanf(str,"%s on %s",what,who) !=2){
      return 0;
   }
   comm = present("ranger_communicator", this_player());
   if(!comm->check_offense(what) && !comm->check_defense(what)){
      write("You don't know that move.\n");
      return 1;
   }
   if(!present(who, environment(this_player()))){
      write(capitalize(who)+" is not here.\n");
      return 1;
   }
   if(!living(present(who, environment(this_player())))){
      write("You get better by practicing with things that are alive!\n");
      return 1;
   }
   if(present(who, environment(this_player())) == this_player()){
      write("You can't practice the martial arts on yourself!\n");
      return 1;
   }
   if(comm->check_offense(what)){
      msg = show_offense(what,name,who,"");
      comm->set_offense_pro(what, comm->query_offense_pro(what)+1);
      tell_room(environment(this_player()),msg+"\n");
present("ranger_communicator", this_player())->add_skill_practice(1);
      return 1;
   }
   if(comm->check_defense(what)){
      msg = show_defense(what,name,who,"");
      comm->set_defense_pro(what, comm->query_defense_pro(what)+1);
      tell_room(environment(this_player()),msg+"\n");
present("ranger_communicator", this_player())->add_skill_practice(1);
      return 1;
   }
   return 1;
}