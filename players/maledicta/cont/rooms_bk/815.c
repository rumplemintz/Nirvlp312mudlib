#include "/players/maledicta/ansi.h"
#define tp this_player()
#define tpn this_player()->query_name()
#define tpp this_player()->query_possessive()
#define RNUM 815
inherit "players/maledicta/cont/inherit/room";


string rtype;
reset(arg){
  if(arg) return;

short_desc = "foothills";
set_light(1);
rtype = "hills";
long_desc = 
"                [1mM[2;37;0m [1mM[2;37;0m [33mn[2;37;0m [32m#[2;37;0m [1;32m@[2;37;0m [1;32m@[2;37;0m [1;31m+[2;37;0m \n"+
"                [33mn[2;37;0m [1mM[2;37;0m [33mn[2;37;0m [32m#[2;37;0m [32m#[2;37;0m [1;32m@[2;37;0m [1;31m|[2;37;0m    N\n"+
"                [33mn[2;37;0m [1mM[2;37;0m [1mM[2;37;0m [1;37mX[2;37;0m [32m#[2;37;0m [32m#[2;37;0m [1;31m|[2;37;0m   /|\n"+
"                [1mM[2;37;0m [1mM[2;37;0m [1mM[2;37;0m [33mn[2;37;0m [32m#[2;37;0m [32m#[2;37;0m [32m#[2;37;0m    | \n"+
"                [1mM[2;37;0m [1mM[2;37;0m [1mM[2;37;0m [33mn[2;37;0m [32m#[2;37;0m [32m#[2;37;0m [32m#[2;37;0m    | \n";
dest_dir = ({
"/players/maledicta/cont/rooms/783.c","north",
"/players/maledicta/cont/rooms/784.c","northeast",
"/players/maledicta/cont/rooms/782.c","northwest",
"/players/maledicta/cont/rooms/847.c","south",
"/players/maledicta/cont/rooms/848.c","southeast",
"/players/maledicta/cont/rooms/816.c","east",
});
}


init(){
   ::init();

}
is_cont_mal(){ return 1; }
query_room_type(){ return rtype; }
query_room_num(){ return RNUM; }