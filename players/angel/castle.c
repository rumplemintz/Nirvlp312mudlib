#include <ansi.h>
#define NAME "Angel"
#define DEST "room/lanceroad3"
#define tp this_player()
#define tpn this_player()->query_name()

object qob;

id(str) { return str == "stargate" || str == "stargate sg1"; }

short() {
    return " "+HIB+"STARGATE /-\\"+NORM+" ";
}

long() {
    write("Inside of this military base lies the secret Stargate.\n");
    write("The gates are heavily guarded but, it appears the 'rings'\n");
    write("are unattended. Maybe you could use the 'rings' to get inside.\n");
}

init() {
    add_action("enter","rings");
}

enter(str) {
	say(capitalize(this_player()->query_name())+
    " is allowed to pass the heavily monitored gate and transported inside.\n");
    this_player()->move_player(
    "and is transported into the military base#/players/angel/area/stargate/room/sg1.c");
    say(capitalize(this_player()->query_name())+" arrives.\n");
    write_file("/players/angel/log/enter_rings",
             ctime(time())+"  "+tpn+
             "    [Level  "+tp->query_level()+"+"+tp->query_extra_level()+"]\n");
    return 1;
}

reset(arg) {
    if (arg)
        return;
    move_object(this_object(), DEST);
    /*Mason mini-guild object to here */
    call_other("/players/angel/masons/mgob.c","???");
    call_other("/players/angel/rewards/belt.c","XXX");
    call_other("/players/angel/closed/tool/p.c","XXX");
    call_other("/players/angel/closed/masonic_pin.c","XXX");

                        /*Quest Addition*/
    if(!present("masonic_quest",find_object("room/quest_room.c"))) {
    qob = clone_object("obj/quest_obj");
    call_other(qob,"set_name","masonic_quest");
    call_other(qob,"set_hint","Search out Mayor Ray through the Stargate\n"+
                                               "to solve the Masonic Quest.\n");
    move_object(qob,"room/quest_room");}
                      /*End Quest*/
}

is_castle(){return 1;}
