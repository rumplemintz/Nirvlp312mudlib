int cmd_history(string arg) {
	int s, history_ticker, i;
	string *my_history;
	object me;

	if(!arg) me = this_player();
	else me = find_player(arg);

	if(!me) {
		write("Player not found.\n");
		return 1;
	}

	my_history = (string *)me->query_action_history();
	history_ticker = (int)me->query_action_ticker();

	if(!my_history || !history_ticker || !(s = sizeof(my_history)))
		return (write("No History\n"), 1);

	write("\n");
	for(i=0;i<s;i++)
		write(my_history[i] + "\n");

	write("\n");
	return 1;
}