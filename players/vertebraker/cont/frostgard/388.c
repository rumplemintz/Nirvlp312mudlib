#include <ansi.h>

#define RNUM 388
inherit "players/vertebraker/cont/inherit/fgard_room";


string rtype;

reset(arg){
  ::reset(arg);
  if(arg) return;

short_desc = "a large glacier";
set_light(1);
rtype = "glacier";
long_desc = 
"                [34m~[0m [34m~[0m [34m~[0m [34m~[0m [36m#[0m [36m#[0m [36m#[0m \n"+
"                [34m~[0m [34m~[0m [34m~[0m [36m#[0m [1;36m@[0m [1;36m@[0m [1;36m@[0m    N\n"+
"                [34m~[0m [34m~[0m [36m#[0m [1;37mX[0m [1;36m@[0m [1;36m@[0m [1;36m@[0m   /|\n"+
"                [34m~[0m [34m~[0m [1;37mn[0m [1;37mn[0m [1;37mn[0m [1;36m@[0m [1;36m@[0m    | \n"+
"                [34m~[0m [34m~[0m [34m~[0m [34m~[0m [47;1mM[0m [1;37mn[0m [1;36m@[0m    | \n";
dest_dir = ({
"/players/vertebraker/cont/frostgard/356.c","north",
"/players/vertebraker/cont/frostgard/357.c","northeast",
"/players/vertebraker/cont/frostgard/420.c","south",
"/players/vertebraker/cont/frostgard/421.c","southeast",
"/players/vertebraker/cont/frostgard/419.c","southwest",
"/players/vertebraker/cont/frostgard/389.c","east",
"/players/vertebraker/cont/frostgard/387.c","west",
});
}

status is_cont_frostgard(){ return 1; }
string query_room_type(){ return rtype; }
int query_room_num(){ return RNUM; }
