inherit "/players/jareel/room";
#include "/players/jareel/define.h"

#define l1 "[ ] - Gate House"
#define l2 "S  - Lunar Shop"
#define l3 "T  - Temple of the Seven Mothers"
#define l4 "C  - Crimson Bat Temple"
#define l5 "K  - Barracks"
#define l6 "M  - Mess Hall"
#define l7 "B  - Lunar Bar"
#define l8 "H  - Lunar First Aid"
#define l9 "A  - Lunar Armorer"
#define l10 "F  - Lunar Forge"

reset(arg) {

     

     if(arg) return;
     set_light(1);
     short_desc=(RED+"The Luner Encampment"+NORM);
     long_desc=
YEL+"%%%%%%%%%%%%%%%%"+NORM+"\n"+
YEL+"%"+NORM+"+------------+"+YEL+"%    "+NORM+"[ ] - Gate House\n"+
YEL+"%"+NORM+"|"+RED+"@@@@@"+NORM+"|"+RED+"@@@@@@"+NORM+"|"+YEL+"%     "+NORM+"S  - Luner Shop\n"+
YEL+"%"+NORM+"|"+RED+"@"+NORM+"+---|"+RED+"@@@@"+NORM+""+RED+"@@"+NORM+"|"+YEL+"%     "+NORM+"T  - Temple of the Seven Mothers\n"+
YEL+"%"+NORM+"|"+RED+"@"+NORM+"|"+RED+"@@@"+NORM+"+----+-X"+YEL+"%     "+NORM+"C  - Crimson Bat Temple\n"+
YEL+"%"+NORM+"+B+T"+RED+"@@"+NORM+"M"+RED+"@@@@"+NORM+"F"+RED+"@"+NORM+"|"+YEL+"%     "+NORM+"K  - Barracks\n"+ 
YEL+"%"+NORM+"|"+RED+"@@@@@"+NORM+"K"+RED+"@@@"+NORM+"A"+RED+"@@"+NORM+"|"+YEL+"%     "+NORM+"M  - Mess Hall\n"+ 
YEL+"%"+NORM+"|"+RED+"@@@@"+NORM+"S+---+--+"+YEL+"%     "+NORM+"B  - Luner Bar\n"+
YEL+"%"+NORM+"|"+RED+"@"+NORM+"C---|"+RED+"@@@"+NORM+"H"+RED+"@@"+NORM+"|"+YEL+"%     "+NORM+"H  - Luner First Aid\n"+
YEL+"%"+NORM+"|"+RED+"@@@@@"+NORM+"|"+RED+"@@@@@@"+NORM+"|"+YEL+"%     "+NORM+"A  - Lunar Armorer\n"+
YEL+"%"+NORM+"+-----+------+"+YEL+"%     "+NORM+"F  - Lunar Forge\n"+
YEL+"%%%%%%"+HIK+"["+NORM+"|"+HIK+"]"+NORM+YEL+"%%%%%%%"+NORM+"\n";
     items = ({

     });
 
dest_dir = ({
     "/players/jareel/areas/chaos/lunercamp/road55","north",
     "/players/jareel/areas/chaos/lunercamp/road38","south",
     "/players/jareel/areas/chaos/lunercamp/road47","west",
});
}

init() {
     ::init();
       add_action("Search","search");
}

Search(str) {
     if(!str) { write("Search what?\n"); return 1; }
       write("You search the "+str+" but find nothing special.\n");
       say(this_player()->query_name()+" searches around for something.\n");
     return 1;
}