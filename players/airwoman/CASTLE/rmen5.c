#include "std.h"
object grendel, money, claws;
#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
if (!grendel || !living(grendel)) {
	grendel = clone_object("obj/monster.c");
        call_other(grendel, "set_name", "grendel"); 
call_other(grendel, "set_level", 14);  

        call_other(grendel, "set_whimpy", 475);
        call_other(grendel, "set_al", 250);
        call_other(grendel, "set_wc", 18);
call_other(grendel, "set_short", "Grendel");
        call_other(grendel, "set_long",
		"Grendel, Ruiner of Meadhalls, Wrecker of Kings!\n");
    call_other(grendel, "set_chat_chance", 40);
    call_other(grendel, "load_chat",
	"Grendel says:  You only think you think.\n");
       call_other(grendel, "load_chat",
        "Grendel says:  You think me a witless fool.\n");
        call_other(grendel, "load_chat",
	"Grendel says: Damn Humans..You and your theories.\n"+

	"You are nothing but a slight wrinkle in time.\n"); 
         call_other(grendel, "set_a_chat_chance", 40);
	call_other(grendel, "load_a_chat",
	"Grendel says: Hey asshole!  You are asking for it!\n");
	call_other(grendel, "load_a_chat", "Grendel picks you up"+
" and decides to squeeze the feces out of you between his hands.\n");  

        move_object(grendel, this_object());
        money = clone_object("obj/money");
        call_other(money, "set_money", random(1000));
        move_object(money, grendel); 
       claws=clone_object("players/airwoman/ARMORS/claws.c");
	move_object(claws, grendel);
	command ("wear claws", grendel);
         call_other(grendel, "set_ac", 11);
   }
}

ONE_EXIT("players/airwoman/CASTLE/rmen4", "south",
	"A room with a grendel.",
	"The dark clouds hover over your body.\n"+
	"Sure hope it's an omen (NOT!)\n"+
	"Beware of Grendel!  Where is\n"+
	"Beowulf when we need him?!\n",1)



