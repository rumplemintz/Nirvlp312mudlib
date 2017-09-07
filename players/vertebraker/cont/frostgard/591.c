#include <ansi.h>

#define RNUM 591
inherit "players/vertebraker/cont/inherit/fgard_room";


string rtype;

reset(arg){
  ::reset(arg);
  if(arg) return;

short_desc = "an ice sheet";
set_light(1);
rtype = "ice sheet";
long_desc = 
"                [36m#[0m [34m~[0m [34m~[0m [34m~[0m [36m#[0m [1;36m@[0m [1;36m@[0m \n"+
"                [36m#[0m [1;37m=[0m [36m#[0m [1;36m@[0m [1;36m@[0m [1;36m@[0m [1;36m@[0m    N\n"+
"                [34m~[0m [34m~[0m [36m#[0m [1;37mX[0m [1;36m@[0m [1;36m@[0m [1;36m@[0m   /|\n"+
"                [34m~[0m [36m#[0m [36m#[0m [34m~[0m [36m#[0m [1;36m@[0m [34m~[0m    | \n"+
"                [34m~[0m [34m~[0m [34m~[0m [36m#[0m [1;37mn[0m [36m#[0m [36m#[0m    | \n";
dest_dir = ({
"/players/vertebraker/cont/frostgard/559.c","north",
"/players/vertebraker/cont/frostgard/560.c","northeast",
"/players/vertebraker/cont/frostgard/558.c","northwest",
"/players/vertebraker/cont/frostgard/624.c","southeast",
"/players/vertebraker/cont/frostgard/622.c","southwest",
"/players/vertebraker/cont/frostgard/592.c","east",
"/players/vertebraker/cont/frostgard/590.c","west",
});
}

status is_cont_frostgard(){ return 1; }
string query_room_type(){ return rtype; }
int query_room_num(){ return RNUM; }