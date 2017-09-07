/*
 * Usage:	new <object>
 * Desc:	Finds <object> in inventory, updates the file, and re-clones
 *				the <object> (destructing old object instance).
 */

object targ, newtarg;
string *tloc, loc;

int cmd_new(string arg) {
	if(!arg) return 0;
	targ = present(lower_case(arg), this_player());
	if(targ) {
		loc = basename(targ);
		write("Updating Object: "+arg+" ("+loc+")\n");
		if(command("update "+loc, this_player())) write("Update Success!\n");
		else write("Update Failed!\n");
		newtarg = clone_object(loc);
		destruct(targ);
		move_object(newtarg, this_player());
	}
	else { write(arg+" not found.\n"); }
	return 1;
}
