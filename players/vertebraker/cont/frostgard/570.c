#include <ansi.h>

#define RNUM 570
inherit "players/vertebraker/cont/inherit/fgard_room";


string rtype;

reset(arg){
  ::reset(arg);
  if(arg) return;

short_desc = "a large glacier";
set_light(1);
rtype = "glacier";
long_desc = 
"                [36m#[0m [1;37mn[0m [1;36m@[0m [1;36m@[0m [1;36m@[0m [36m#[0m [36m#[0m \n"+
"                [1;37mn[0m [47;1mM[0m [1;37mn[0m [1;36m@[0m [1;36m@[0m [36m#[0m [36m#[0m    N\n"+
"                [36m#[0m [1;37mn[0m [36m#[0m [1;37mX[0m [36m#[0m [36m#[0m [34m~[0m   /|\n"+
"                [36m#[0m [36m#[0m [36m#[0m [36m#[0m [36m#[0m [36m#[0m [36m#[0m    | \n"+
"                [36m#[0m [36m#[0m [36m#[0m [36m#[0m [34m~[0m [36m#[0m [36m#[0m    | \n";
dest_dir = ({
"/players/vertebraker/cont/frostgard/538.c","north",
"/players/vertebraker/cont/frostgard/539.c","northeast",
"/players/vertebraker/cont/frostgard/537.c","northwest",
"/players/vertebraker/cont/frostgard/602.c","south",
"/players/vertebraker/cont/frostgard/603.c","southeast",
"/players/vertebraker/cont/frostgard/601.c","southwest",
"/players/vertebraker/cont/frostgard/571.c","east",
"/players/vertebraker/cont/frostgard/569.c","west",
});
}

status is_cont_frostgard(){ return 1; }
string query_room_type(){ return rtype; }
int query_room_num(){ return RNUM; }
