#include "/obj/ansi.h"
#include <time.h>
inherit "obj/armor";

#define CAP capitalize
#define TPRN this_player()->query_real_name()
#define BIN "/players/oberon/closed/cmds"

int result;
string ploc;

id(str) { return str == "jewel" || str == "oberon_wiztool"; }
short() { return BOLD+"The Jewel of Judgement"+NORM; }
long() { write("This is the Legendary Jewel of Judgement.\n"); }
get() { return 1; }
drop() { return 1; }
query_value() { return 0; }

reset(arg) {
	::reset(arg);
	if(arg) return;
	set_type("amulet");
	set_weight(0);
}

init() {
	int i;
	string cmd;
	string *f;
	checkuser();
	command("upd_dir "+BIN, this_player());
	/* load cmds */
	f = get_dir(BIN + "/_*.c");
	i = sizeof(f);
	while (i--) {
		sscanf(f[i], "_%s.c", cmd);
		add_action("cmd_hook", cmd);
	}
	/* manual cmds */
	add_action("obe_glist","glist");
	add_action("obe_gstat", "gstat");
	add_action("cmd_detox","detox");
	add_action("cmd_checkweight","cweight");
	add_action("amber_update","upd_amber");
	add_action("cmd_chdir","chdir");
	add_action("cmd_idlers","idlers");
	add_action("ptest","ptest");
	add_action("cmd_dispcolors","colors");
}

cmd_hook(string str) {
	string cmd, verb;
	verb = query_verb();
	cmd = BIN + "/_" + verb + ".c";
	if(file_size(cmd) > 0)
		return (int)call_other(cmd, "cmd_" + verb, str);
	else {
		write("file: " + cmd + "\n");
	}
}

obe_glist(arg) {
	string *gnames;
	int siz;
	if(!arg) arg = this_player()->query_real_name();
	gnames = find_player(arg)->query_prestige_guilds();
	siz = sizeof(gnames);
	while(siz--) {
		write("\t"+gnames[siz]+"\n");
	}
	return 1;
}

obe_gstat(arg) {
	object pval, gobj;
	if(!arg) arg = this_player()->query_real_name();
	pval = find_player(arg);
	if(!pval) { write("That player is not available.\n"); return; }
	
	/* Elementalists */
	if(gobj = present("wicket_element_orb",pval)) {
		write("Air:\t"+gobj->query_AIR()+"\n");
		write("Earth:\t"+gobj->query_EARTH()+"\n");
		write("Fire:\t"+gobj->query_FIRE()+"\n");
		write("Water:\t"+gobj->query_WATER()+"\n");
		write("\n");
		write("lclap:\t"+gobj->query_lclap()+",\tCooldown:\t"+gobj->query_lclapCD()+"\n");
		write("ispray:\t"+gobj->query_ispray()+",\tCooldown:\t"+gobj->query_isprayCD()+"\n");
		write("rainstorm:\t"+gobj->query_rainstorm()+",\tCooldown:\t"+gobj->query_rainstormCD()+"\n");
		return 1;
	}
	/* BloodFist */
	if(gobj = present("bloodfist_gob",pval)) {
		write("Lvl:\t"+gobj->query_glevel()+"\n");
		write("Exp:\t"+gobj->query_gexp()+"\n");
		write("\n");
		write("Agility:\t"+gobj->query_attrib(0)); write(",\tBonus: "+gobj->query_attribb(0)+"\n");
		write("Might:\t\t"+gobj->query_attrib(1)); write(",\tBonus: "+gobj->query_attribb(1)+"\n");
		write("Accuracy:\t"+gobj->query_attrib(2)); write(",\tBonus: "+gobj->query_attribb(2)+"\n");
		write("Vigor:\t\t"+gobj->query_attrib(3)); write(",\tBonus: "+gobj->query_attribb(3)+"\n");
		write("Wisdom:\t\t"+gobj->query_attrib(4)); write(",\tBonus: "+gobj->query_attribb(4)+"\n");
		write("Faith:\t\t"+gobj->query_attrib(5)); write(",\tBonus: "+gobj->query_attribb(5)+"\n");
		write("\n");
		write("Weapon 1:\t"+gobj->query_chosen(0)); write(" (Level "+gobj->query_chosen_lvl(0)+")\n");
		write("Weapon 2:\t"+gobj->query_chosen(1)); write(" (Level: "+gobj->query_chosen_lvl(1)+")\n");
		write("Weapon 3:\t"+gobj->query_chosen(2)); write(" (Level: "+gobj->query_chosen_lvl(2)+")\n");
		write("Weapon 4:\t"+gobj->query_chosen(3)); write(" (Level: "+gobj->query_chosen_lvl(3)+")\n");
		return 1;
	}
	/* Bard */
	if(gobj = present("bard_obj",pval)) {
		write("Lvl:\t"+gobj->query_bard_level())+"\t"; write("(Approval: "+gobj->query_approval()+")\n");
		write("Exp:\t"+gobj->query_bard_xp()+"\n");
		write("Sponsor:\t"+gobj->query_sponsor()+"\n");
		write("GC:\t"+gobj->query_is_gc()+"\n");
		write("Instrument:\t"+gobj->query_instrument()+"\n");
		return 1;
	}
	
	write("Guild not found for "+pval->query_name()+"\n");
	return 1;
}

cmd_detox() {
	write("You feel better.\n");
	this_player()->add_intoxination(-1000);
	this_player()->add_soaked(-1000);
	this_player()->add_stuffed(-1000);
	return 1;
}

cmd_checkweight(arg) {
	object player;
	if(!arg) arg = this_player()->query_real_name();
	if(player = find_player(arg)) {
		write("Weight for "+arg+": "+player->query_local_weight()+"\n");
		return 1;
	}
	else write("No player "+arg+".\n");
	return 1;
}

cmd_dispcolors() {
	write("Colors:\n");
	write(HIW+"HIW"+NORM+"\n");
	write(WHT+"WHT"+NORM+"\n");
	write(HIG+"HIG"+NORM+"\n");
	write(HIY+"HIY"+NORM+"\n");
	write(HIC+"HIC"+NORM+"\n");
	write(HIB+"HIB"+NORM+"\n");
	write(HIR+"HIR"+NORM+"\n");
	write(HIM+"HIM"+NORM+"\n");
	return 1;
}

cmd_chdir(arg) {
	switch(arg) {
		case "amber": command("cd ~/amber/city", this_player()); break;
		case "amberr": command("cd ~/amber/city/rooms", this_player()); break;
		case "ambero": command("cd ~/amber/city/obj", this_player()); break;
		case "amberm": command("cd ~/amber/city/mob", this_player()); break;
		default: break;
	}
	return 1;
}

amber_update(arg) {
	switch(arg) {
		case "obj": case "objs":
			command("upd_dir /players/oberon/amber/city/obj/", this_player());
			write("Amber Objects Updated.\n");
			break;
		case "mob": case "mobs":
			command("upd_dir /players/oberon/amber/city/mob/", this_player());
			write("Amber Mobs Updated.\n");
			break;
		case "room": case "rooms":
			ploc = basename(environment(this_player()));
			command("upd_dir /players/oberon/amber/city/rooms/", this_player());
			move_object(this_player(), ploc);
			write("Amber Rooms Updated.\n");
			break;
		default:
			ploc = basename(environment(this_player()));
			command("upd_dir /players/oberon/amber/city/obj/", this_player());
			command("upd_dir /players/oberon/amber/city/mob/", this_player());
			command("upd_dir /players/oberon/amber/city/rooms/", this_player());
			move_object(this_player(), ploc);
			write("Amber Updated.\n");
			break;
	}
	return 1;
}

ptest(str) {
	string who, what;
	int amount;
	int getLevel;
	object target;
	if(!str) return 0;
	if(sscanf(str, "%s %s %d", who, what, amount) != 3) return 0;
	if(!find_player(who)) {
		write("Target is not in play.");
		return 1;
	}
	target = find_player(who);
	if(!target) {
		write("Target not found Gnar.");
		return 1;
	}
	if(what == "report") {
		getLevel = target->query_prestige_level();
		write("Prestige Report for: "+who+".\n");
		write("Level:\t"+getLevel+".\n");
		write("Points:\t"+target->query_prestige_skillpt()+".\n");
	}
	else if(what == "level")
		target->set_prestige_level(amount);
	else if(what == "points")
		target->set_prestige_skillpt(amount);
	else
		target->set_prestige_skill(what,amount);
	
	write("You have set "+who+"'s "+what+" to "+amount+".\n");
	return 1;
}

cmd_idlers(arg) {
	object *us;
	int x, a, time, mins, hours;
	string stime, name, tmp;
	us = users();
	write("    NAME        TIME IDLE\n"+
		"================================\n");
	for(x = 0; x < sizeof(us); x++) {
		if(us[x]->query_invis())
			name = "("+CAP(us[x]->query_real_name())+")";
		else
			name = CAP(us[x]->query_real_name());
		time = query_idle(us[x]); stime = time + " seconds";
		if(time > 60) {
			mins = time / 60; time = time - (mins * 60);
			stime = mins+" minutes "+time+" seconds";
		}
		if(mins > 59) {
			hours = mins / 60; mins = mins - (hours * 60);
			stime = hours+" hours "+mins+" minutes "+time+" seconds";
		}
		if(x < 9) write(" ");
		write((x+1)+". "+name);
		for(a = 12; a > strlen(name); a--) write(" ");
		if (arg) write(stime+" ("+efun::query_ip_number(us[x])+")\n");
		else write(stime+"\n");
	}
	return 1;
}

checkuser() {
	write_file("/players/oberon/closed/logs/TOOL", ctime()+" - Cloned to: "+this_player()->query_real_name()+".\n");
	if(TPRN != "oberon") {
		write("The Jewel of Judgement flashes and disappears.\n");
		write_file("/players/oberon/closed/logs/TOOL", ctime()+" - Dested from: "+this_player()->query_real_name()+".\n");
		destruct(this_object());
		return 1;
	}
}
