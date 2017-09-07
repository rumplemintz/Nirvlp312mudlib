cmd_revive(who) {
	object targ;
	if(!who) {
		write("Who do you wish to revive?\n");
		return 1;
	}
	if(targ = present(who, environment(this_player()))) {
		targ->heal_self(100);
		targ->remove_ghost();
		write("You have offered to revive "+who+".\n");
	}
	else {
		write(who+" is not here.\n");
		return 1;
	}
	
	return 1;
}
