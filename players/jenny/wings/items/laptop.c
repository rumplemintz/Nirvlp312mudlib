/*  this object gives vague info on a player's health, to the nearest 5% if
    you know how to read the monitor, vague info on their coins, vague info
    on how high their wimpy is set, what they are fighting, and their location.
    You have to kill /players/jenny/wings/mobs/staff/holland.c to get this, it
    cannot be bought.
*/
#include "/players/jenny/define.h"
inherit "/obj/treasure.c";
int wealth,courage,health,opp,where;
string WE,HE,CG,oppname;
string lasttry;
object ob;
id(str) { return str == "laptop" || str == "computer" || str == "laptop computer"; } 
reset(int arg) {
  if(arg) return;
set_short("A laptop computer");

set_long(
"This is a small, black laptop computer.  Ken Holland uses it to store the\n"+
"scouting reports of every opposition player.  You might be able to 'access'\n"+
"information on a player.\n");

set_weight(1);
set_value(1000);
}
init() { 
    ::init(); 
add_action("theplayer","access");
}
theplayer(string name) {
    object ob;
if(!name) {notify_fail("What do you want to access?\n"); return 0; }
    ob = find_player(name);
        if (!ob) {
        write(CAP(name)+" is not in the game.\n");
        return 1; }
   if(ob->query_level() > 20) { write("Information on wizards is not available.\n"); return 1;}
   if(ob->query_invis()) {
     if(ob->query_total_level() > this_player()->query_total_level()) {
       if(random(120)>this_player()->query_attrib("int") ||
          lasttry == name) {
          write(CAP(name)+" returns garbled data.\n");
          lasttry = name;
          return 1;} /* don't show the invis -Bp */
       else write("The information is garbled but you can make it out.\n");
       }
   }
    lasttry = 0;
    opp = ob->query_attack();
    if(!opp) { oppname = "no";} else { oppname = "yes";}
    health = (ob->query_hp() * 100) / ob->query_mhp();
    wealth = ob->query_money();
    courage = ob->query_wimpy();
    where = call_other(ENV(find_player(name)),"short");
    if(wealth < 10000) { WE = "poor";}
    if(wealth > 9999 && wealth < 20000) {WE = "meager";}
    if(wealth > 19999 && wealth < 30000) {WE = "getting by";}
    if(wealth > 29999 && wealth < 60000) {WE = "comfortable";} 
    if(wealth > 59999 && wealth < 70000) {WE = "well off";}
    if(wealth > 69999) {WE = "rich";}
    if(health < 5) { HE = MAG+"["+CYN+">                   "+MAG+"]"+NORM;}
    if(health > 4 && health < 10) {HE = MAG+"["+CYN+">>                  "+MAG+"]"+NORM;}
    if(health > 9 && health < 15) {HE = MAG+"["+CYN+">>>                 "+MAG+"]"+NORM;}
    if(health > 14 && health < 20) {HE = MAG+"["+CYN+">>>>                "+MAG+"]"+NORM;}
    if(health > 19 && health < 25) {HE = MAG+"["+CYN+">>>>>               "+MAG+"]"+NORM;}
    if(health > 24 && health < 30) {HE = MAG+"["+CYN+">>>>>>              "+MAG+"]"+NORM;}
    if(health > 29 && health < 35) {HE = MAG+"["+CYN+">>>>>>>             "+MAG+"]"+NORM;}
    if(health > 34 && health < 40) {HE = MAG+"["+CYN+">>>>>>>>            "+MAG+"]"+NORM;}
    if(health > 39 && health < 45) {HE = MAG+"["+CYN+">>>>>>>>>           "+MAG+"]"+NORM;}
    if(health > 44 && health < 50) {HE = MAG+"["+CYN+">>>>>>>>>>          "+MAG+"]"+NORM;}
    if(health > 49 && health < 55) {HE = MAG+"["+CYN+">>>>>>>>>>>         "+MAG+"]"+NORM;}
    if(health > 54 && health < 60) {HE = MAG+"["+CYN+">>>>>>>>>>>>        "+MAG+"]"+NORM;}
    if(health > 59 && health < 65) {HE = MAG+"["+CYN+">>>>>>>>>>>>>       "+MAG+"]"+NORM;}
    if(health > 64 && health < 70) {HE = MAG+"["+CYN+">>>>>>>>>>>>>>      "+MAG+"]"+NORM;}
    if(health > 69 && health < 75) {HE = MAG+"["+CYN+">>>>>>>>>>>>>>>     "+MAG+"]"+NORM;}
    if(health > 74 && health < 80) {HE = MAG+"["+CYN+">>>>>>>>>>>>>>>>    "+MAG+"]"+NORM;}
    if(health > 79 && health < 85) {HE = MAG+"["+CYN+">>>>>>>>>>>>>>>>>   "+MAG+"]"+NORM;}
    if(health > 84 && health < 90) {HE = MAG+"["+CYN+">>>>>>>>>>>>>>>>>>  "+MAG+"]"+NORM;}
    if(health > 89 && health < 95) {HE = MAG+"["+CYN+">>>>>>>>>>>>>>>>>>> "+MAG+"]"+NORM;}
    if(health > 94) {HE = MAG+"["+CYN+">>>>>>>>>>>>>>>>>>>>"+MAG+"]"+NORM;}
    if(courage < 1) { CG = "fearless";}
    if(courage > 0 && courage < 10) {CG = "reckless";}
    if(courage > 9 && courage < 20) {CG = "bold";}
    if(courage > 19 && courage < 30) {CG = "average";}

    if(courage > 29 && courage < 40) {CG = "cautious";}
    if(courage > 39 && courage < 60) {CG = "timid";}
    if(courage > 59 && courage < 80) {CG = "cowardly";}
    if(courage > 79) {CG = "what a wuss!";}

write(BOLD+WHT+"\n"+
"		All Available Info On "+RED+CAP(ob->query_name())+NORM+".\n"+
"\n"+
"		Health:		"+HE+"\n"+
"		In Battle:	"+oppname+"\n"+
"		Wealth:		"+WE+"\n"+
"		Courage:	"+CG+"\n"+
"		Location:	"+where+"\n");
return 1; }
