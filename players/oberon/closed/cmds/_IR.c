#include "/bin/wiz/cmd_defs.h"

int cmd_IR(string str) {
	object *ob, targ;
	int h, s;

	if(!str) {
		/* Changed by Oberon - 6/3/17 
		write("Usage: 'IR <player>'\n");
		return 1;
		*/
		str = (string)this_player()->query_real_name();
	}
	if(!(targ = find_player(str)) || !ENV(targ)) {
		write("Target not in play.\n");
		return 1;
	}
	write(CAP(str)+"'s Room Inventory.\nROOM: "+
	object_name(ENV(targ))+"\n");
	s = sizeof(ob = all_inventory(ENV(targ)));

	while(h < s) {
		write((string)call_other("/bin/wiz/_I","print_obj_info",h,ob[h])+"\n");
		h ++;
	}
	write("Done.\n");
	return 1;
}