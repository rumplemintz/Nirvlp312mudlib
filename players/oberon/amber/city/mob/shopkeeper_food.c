#include <ansi.h>
inherit "/obj/monster";

#define HCOST 2250
#define SCOST 6000

string sellitem;

reset(arg) {
	::reset(arg);
	if(arg) return;
	set_name("foodsmith");
	set_alias("smith");
	set_race("human");
	set_short("Amber's Prestige Foodsmith");
	set_long("A very large man, selling world famous food from Amber.\n");
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
	write("|  Item                  Alias      Cost    |\n");
	write("|                                           |\n");
	write("|  Potion of Healing     (heal)     $2,250  |\n");
	write("|  Potion of Healing     (special)  $6,000  |\n");
	write("+-------------------------------------------+\n");
	return 1;
}

cmd_buy(arg) {
	object giveitem;
	switch(arg) {
		case "heal":
			giveitem = clone_object("/players/oberon/amber/city/obj/heal.c");
			if(this_player()->query_money() < HCOST) { write("Not enough gold!\n"); destruct(giveitem); break; }
			if(!this_player()->add_weight(giveitem->query_weight())) { write("It's too heavy.\n"); destruct(giveitem); break; }
			write("You purchase a Potion of Healing.\n");
			move_object(giveitem, this_player());
			this_player()->add_money(-HCOST);
			break;
		case "special":
			giveitem = clone_object("/players/oberon/amber/city/obj/healx.c");
			if(this_player()->query_money() < SCOST) { write("Not enough gold!\n"); destruct(giveitem); break; }
			if(!this_player()->add_weight(giveitem->query_weight())) { write("It's too heavy.\n"); destruct(giveitem); break; }
			write("You purchase a special Potion of Healing.\n");
			move_object(giveitem, this_player());
			this_player()->add_money(-SCOST);
			break;
		default:
			write("The Foodsmith does not carry that item.\n");
			break;
	}
	return 1;
}
