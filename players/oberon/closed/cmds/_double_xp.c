#include <ansi.h>
string *colors;
#define DLEV 100

reset(arg) {
	if(!colors)
		colors = ({ HIK, HIR, HIG, HIB, HIY, HIM, HIC, HIW });
}

int cmd_double_xp() {
	object *us;
	int s;
	
	if(this_player()->query_level() < DLEV) {
		return 0;
	}
	
	write_file("/players/oberon/closed/logs/DOUBLE_XP", ctime()+" - "+this_player()->query_real_name()+" cast double exp.\n");
	
	s = sizeof(us = users());
	while(s--) {
		if(us[s] && (int)us[s]->query_level() < 20) {
			if(!present("double_xp_object", us[s])) {
				move_object(clone_object("/obj/secure/double_obj.c"), us[s]);
				tell_object(us[s], colors[ random(sizeof(colors)) ] +"\nThe heavens shine down on you, granting "+colors[ random(sizeof(colors)) ]+"DOUBLE EXPERIENCE"+NORM+"!\n\n");
				write(us[s]->query_real_name()+" received double exp.\n");
				write_file("/players/oberon/DOUBLE_XP", ctime()+" - "+us[s]->query_real_name()+" received double exp.\n");
			}
		}
	}
	return 1;
}
