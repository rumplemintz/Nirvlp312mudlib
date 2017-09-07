inherit "obj/container.c";
#include <ansi.h>
#define SHOP "/obj/daemons/shop_daemon"

id(str) { return str=="backpack" || str=="pack"; }
short() { return "An Adventure Backpack"; }
long() {
	write("A backpack hand made by the Adventure Smith of Amber! It's got lots\n"+
			"of large pockets to hold all of your very cool treasures! Neat!\n");
	return 1;
}

reset(arg) {
	::reset(arg);
	if (arg) return;
	set_name("bag");
	set_weight(1);
	set_value(550);
	set_max_weight(1000);
}

init() {
	::init();
	add_action("baginv","baginv");
}

baginv(string str) {
	if(this_player() && environment(this_object()) == this_player())
		return SHOP->list(str);
	else
		return 0;
}

query_empty_shop() { return short_desc+" is empty."; }
query_backshop() { return this_object(); }
query_save_flag() { return 1; }
