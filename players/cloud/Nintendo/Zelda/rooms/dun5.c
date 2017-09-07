/*  Zelda Dungeon5
 *  /Nintendo/Zelda/rooms/dun5.c
 *  Cloud 2013
 */
 
#include "/obj/ansi.h"
inherit "room/room";

reset(arg) 
{	
	::reset(arg);
	
	if(!present("digdogger")) 
	{		
		if(!present("minidogger")) 
		{
			move_object(clone_object("/players/cloud/Nintendo/Zelda/mobs/dig.c"),this_object());
		}	
	}
	
	if(!arg)
 	{
		set_light(1);

		short_desc = ""+HIB+"Death Mountain"+NORM+"" ;
		
		long_desc =
		""+HIB+"         ***"+NORM+"\n"+
     	""+HIB+"        *"+HIK+"["+HIR+"B"+HIK+"]"+HIB+"*"+NORM+"\n"+
     	""+HIB+"       **"+HIK+"[ ]"+HIB+"**"+NORM+"\n"+
     	""+HIB+"      ***"+HIK+"[ ]"+HIB+"***"+NORM+"\n"+
     	""+HIB+"     ****"+HIK+"[ ]"+HIB+"****"+NORM+"\n"+
     	""+HIB+"    *****"+HIK+"["+HIR+"@"+HIK+"]"+HIB+"*****"+NORM+"\n"+
     	""+HIB+"   ******"+HIK+"[ ]"+HIB+"******"+NORM+"\n"+
     	""+HIB+"  *******"+HIK+"[ ]"+HIB+"*******"+NORM+"\n"+
     	""+HIB+" ********"+HIK+"[ ]"+HIB+"********"+NORM+"\n"+
     	""+HIB+"*********"+HIK+"[ ]"+HIB+"*********"+NORM+"\n";
   
     	  			
		dest_dir = 
		({	
			"players/cloud/Nintendo/Zelda/rooms/dun6.c","up",
			"players/cloud/Nintendo/Zelda/rooms/dun4.c","down",
			
		});
		
	}
}