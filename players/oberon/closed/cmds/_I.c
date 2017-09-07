#include "/bin/wiz/cmd_defs.h"

int cmd_I(string str) {
  object *ob, targ;
  int h, s;
	
  if (!str) {
		/* Changed by Oberon - 6/3/17 
		write("Usage: 'I <player>'\n");
		return 1;
		*/
		str = (string)this_player()->query_real_name();
	}
	
	if(!(targ = find_player(str))) {
		write("Target not in play.\n");
		return 1;
	}
	s = sizeof(ob = all_inventory(targ));
	write(CAP(str) + "'s inventory.\nROOM: " +
		object_name(ENV(targ)) + "\n");
	for (h = 0, s = sizeof(ob); h < s; h++) {
		/* write((string)TO->print_obj_info(h, ob[h])+" ("+ob[h]->query_info()+")\n"); */
		write((string)TO->print_obj_info(h, ob[h])+"\n");
	}
	write("Done.\n");
	return 1;
}

string print_obj_info(int i, object ob) {
	string sh, nm;

	if(!ob) return "";
	return i + "\t" + object_name(ob) + " " +
		((sh = (string)ob->short()) ? sh
		: ((nm = (string)ob->QN) ? nm
		: "INVIS"));
}