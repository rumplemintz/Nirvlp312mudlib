#include "/players/maledicta/ansi.h"
#define USER environment(shadwep)

object shadwep;
int no_wear_out;

add_shadow(object ob){
        shadwep = ob;
        shadow(shadwep, 1);
}

remove_shadow(){
        shadow(shadwep, 0);
        destruct(this_object());
        return 1;
}

query_value(){ return 0; }

query_pro_weapon(){ return 1; }

drop(){
        this_object()->stopwield();
        return 0;
}

proficiency_hit(){
 int total;
 total = 10;
 return total;
 }

stopwield(){
        USER->stop_wielding();
        this_object()->un_wield();
        tell_object(USER, "As your tendrils extricate themselves from the weapon it disintegrates.\n");
        destruct(shadwep);
        return 1;
}

query_shadowed() { return 1; }

short(){ return shadwep->short()+" "+BOLD+" [ "+HIR+"grafted"+NORM+BOLD+" ]"+NORM; }