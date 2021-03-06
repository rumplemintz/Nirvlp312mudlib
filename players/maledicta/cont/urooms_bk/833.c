#include "/players/maledicta/ansi.h"
#define tp this_player()
#define tpn this_player()->query_name()
#define tpp this_player()->query_possessive()
#define RNUM 833
inherit "players/maledicta/cont/inherit/room2";


string rtype;
reset(arg){
  if(arg) return;

set_light(-2);
rtype = "road";
long_desc = 
"                [34m~[2;37;0m [34m~[2;37;0m [34m~[2;37;0m [33m#[2;37;0m [1;37m+[2;37;0m [1;37m-[2;37;0m [1;37m-[2;37;0m \n"+
"                [34m~[2;37;0m [34m~[2;37;0m [34m~[2;37;0m [33m#[2;37;0m [1;37m|[2;37;0m [33m#[2;37;0m [33m#[2;37;0m    N\n"+
"                [34m~[2;37;0m [34m~[2;37;0m [34m~[2;37;0m [1;37mX[2;37;0m [1;37m+[2;37;0m [33m#[2;37;0m [33m#[2;37;0m   /|\n"+
"                [34m~[2;37;0m [34m~[2;37;0m [34m~[2;37;0m [34m~[2;37;0m [33m#[2;37;0m [33m#[2;37;0m [33m#[2;37;0m    | \n"+
"                [34m~[2;37;0m [34m~[2;37;0m [34m~[2;37;0m [34m~[2;37;0m [33m#[2;37;0m [33m#[2;37;0m [33m#[2;37;0m    | \n";
dest_dir = ({
"/players/maledicta/cont/urooms/802.c","northeast",
"/players/maledicta/cont/urooms/834.c","east",
});
}


short(){ return "Dark room"; }
init(){
   ::init();

}
is_underground_mal(){ return 1; }
query_room_type(){ return rtype; }
query_room_num(){ return RNUM; }
