#include <ansi.h>
inherit "/obj/monster";

#define COST 500

reset(arg) {
	::reset(arg);
	if(arg) return;
	set_name("shopkeeper");
	set_alias("keeper");
	set_race("human");
	set_short("Information Shopkeeper");
	set_long("A very large man, selling information about Amber.\n");
	set_gender("male");
	set_level(16);
	set_hp(600 + random(1000));
	set_wc(30);
	set_ac(20);
	set_aggressive(0);
	set_al(0);
	add_money(1000+random(1000));
}

init() {
	::init();
	add_action("cmd_list", "list");
	add_action("cmd_buy", "buy");
}

heart_beat() {
	::heart_beat();
}

cmd_list() {
	write("+-------------------------------------------+\n");
	write("|  Item                  Alias      Cost    |\n");
	write("|                                           |\n");
	write("|  Map of Amber          (map)      $"+COST+"    |\n");
	write("+-------------------------------------------+\n");
	return 1;
}

cmd_buy(arg) {
	object giveitem;
	switch(arg) {
		case "map":
			giveitem = clone_object("/players/oberon/amber/city/obj/map.c");
			if(this_player()->query_money() < COST) { write("Not enough gold!\n"); destruct(giveitem); break; }
			if(!this_player()->add_weight(giveitem->query_weight())) { write("It's too heavy.\n"); destruct(giveitem); break; }
			write("You purchase a Map of Amber.\n");
			move_object(giveitem, this_player());
			this_player()->add_money(-500);
			break;
		default:
			write("The Shopkeeper does not carry that item.\n");
			break;
	}
	return 1;
}
