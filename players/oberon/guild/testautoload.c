#include <ansi.h>

id(str) { return str == "test_autoload" || str == "piece"; }
short() { return 0; }
query_auto_load() { return "/players/oberon/guild/testautoload:"; }
get() { return 1; }
drop() { return 1; }
query_value() { return 0; }

long() { write("A mark of Oberon.\n"); }

extra_look() {
	if (this_player() == environment())
		return "A piece of Oberon's soul";
	else {
		return environment()->query_name()+" holds a piece of Oberon's soul";
	}
}
