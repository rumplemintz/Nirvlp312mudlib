/************************************/
/*    Owner:      Vital@Nirvana     */
/*    Created:    4/9/01            */
/*    Modified:   4/16/01           */
/*    Realm:      Acadie            */
/************************************/

#include <ansi.h>
#include "/players/vital/closed/headers/vital.h"                 /*universal header*/
#include "/players/vital/dest/include/dest.h"             /*area header     */

inherit "room/room";

reset(arg) {
    if(!arg) { 
    set_light(1);
    short_desc = "Sidewalk";
    long_desc =
"  The Sidewalk\n\
The sidewalk comes to an end here in the extreme northwest corner of \n\
EdmonTown. To the south the sidewalk continues back into town. The \n\
building to the northwest is finally within reach, but looks abandoned.\n";

items = ({
    "sidewalk",
    "The sidewalk is a hard, composite material that has been fashioned from\n\
the materials readily at hand here on Acadie",
    "town",
    "This town is composed of several standard, common buildings that all look\n\
similar in form. The basic building is a low structure of stone that \n\
looks very sturdy",
    "edge",
    "The edge of town is a sharp contrast to the surrounding urban conditions. \n\
The western side of the sidewalk ends abruptly and dirt and vegetation \n\
begins. Before long the vegetation will grow back over the sidewalk",
    "east",
    "The edge of town is a sharp contrast to the surrounding urban conditions. \n\
The western side of the sidewalk ends abruptly and dirt and vegetation \n\
begins. Before long the vegetation will grow back over the sidewalk",
    "dirt",
    "The dirt is pale yellow, and very powdery",
    "vegetation",
    "The vegetation is a spindly, sparse-looking plant that has survived many \n\
storms, people and machines, only to increase and grow stronger",
    "south",
    "The sidewalk continues on to the south and enters a residential area",
    "corner",
    "This is as far as you can go on the sidewalk in this part of town",
    "building",
    "The building to the northwest is very old and looks like it has not been \n\
used in years. There are signs of fire and vandalism",
    "signs",
    "The signs of fire and vandalism are readily apparent in the scorched \n\
walls, broken windows and graffiti",
    "graffiti",
    random_color()+"You "+NORM+random_color()+"su"+NORM+random_color()+"ck"+NORM+random_color()+" at"+NORM+random_color()+" this."+NORM
});

dest_dir = ({
    ACADIE+"room/sidewalk27.c","south",
    ACADIE+"room/train2.c","northwest"
  });

  }
}

init() {
    ::init();
    add_action("search_me","search");
}

search_me(str) {
    if(!str) {
        notify_fail("What are trying to search?\n");
        return 0;
    }
    else write("You furiously search the "+str+" but find nothing.\n");
}