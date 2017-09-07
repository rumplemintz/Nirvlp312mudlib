	/*  */
	/*  */

#include "/players/wren/ansi.h"; 
inherit "/players/vertebraker/closed/std/room.c";
int w;

reset(arg)  {   
     if(arg) return; 
 
   set_light(1);
   short_desc = "Big Top";
   long_desc = 
" Big Top 2 \n\
   \n\
   \n\
   \n\
   \n\
   \n\
   \n";

      items=({		/*Remember two deep on noun descriptions*/
          "","",
	  "","",
          "","",
	  "","",
	  "","",
	  "","",
	  "","",
	  "","",
          "","",
          "","",
          "","",
          "","",
          "","",
          "",""
             });

        
      dest_dir = ({
          "/players/wren/Area/evilcircus/rooms/bigtop1.c","west",
          "/players/wren/Area/evilcircus/rooms/bigtop3.c","southwest",
          "/players/wren/Area/evilcircus/rooms/bigtop5.c","south",
          "/players/wren/Area/evilcircus/rooms/ringb2.c","ring_two",
                 }); 
 
set_chance(5);       
add_msg(" \n");
add_msg(" \n");
add_msg(" \n");
add_msg(" \n");
add_msg(" \n");

add_listen("main"," ");
add_listen(" "," ");
add_listen(" "," ");

add_smell("main"," ");
add_smell(" "," ");
add_smell(" "," ");

add_touch(" "," ");

add_exit_msg("dir","message to mover\n",
                    "movement seen by others\n");
}

  init() {
    ::init();
    add_action("search_room","search");
         }

  search_room()  {
        write(" \n");
        say (this_player()->query_name() +" searches the area. \n");
        return 1;
                 }


  	/*      */
	/*      */
	/*      */
	/*      */