#include <ansi.h>
inherit "/obj/monster";

#define BCOST 2000

reset(arg) {
	::reset(arg);
	if(arg) return;
	set_name("shopkeeper");
	set_alias("smith");
	set_race("human");
	set_short("Amber's Adventure Smith");
	set_long("A very large man, selling world famous adventure goods.\n");
	set_gender("male");
	set_level(30);
	set_hp(1000000);
	set_wc(50);
	set_ac(50);
	set_aggressive(0);
	set_al(0);
	set_heal(5000, 1);
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
	write("|  Item                 Alias       Cost    |\n");
	write("|                                           |\n");
	write("|  Adventure Backpack   (backpack)  $"+BCOST+"   |\n");
	write("+-------------------------------------------+\n");
	return 1;
}

cmd_buy(arg) {
	object giveitem;
	switch(arg) {
		case "backpack":
			giveitem = clone_object("/players/oberon/amber/city/obj/backpack.c");
			if(this_player()->query_money() < BCOST) { write("Not enough gold!\n"); destruct(giveitem); break; }
			if(!this_player()->add_weight(giveitem->query_weight())) { write("It's too heavy.\n"); destruct(giveitem); break; }
			write("You purchase an Adventure Backpack.\n");
			move_object(giveitem, this_player());
			this_player()->add_money(-BCOST);
			break;
		default:
			write("The Adventure Smith does not carry that item.\n");
			break;
	}
	return 1;
}
