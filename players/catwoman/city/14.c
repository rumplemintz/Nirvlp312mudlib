
object newspaper, top_list;
object band;
/* realm() {return "NT";}*/

reset(arg) {
   /* if (!present("go player"))
        move_object(clone_object("obj/go_player"), this_object());*/
    if (!top_list || !present(top_list)) {
        top_list = clone_object("obj/level_list");
        move_object(top_list, this_object());
    }
    
/*
    if (!present("bandit")) {
   band = clone_object("obj/bandit");
   move_object(band, this_object());
   }


 
*/
    set_light( 1);
}

short() {
    return "The local Metropolis pub";
}

init() {
 
    add_action("north","north");
  /*  add_action("south");
    add_verb("south"); */
    add_action("order","order");
    add_action("order","buy");
}

north() {
    object ob;

    call_other(this_player(), "move_player",  "north" + "#" +"players/catwoman/city/13");
    return 1;
}
 /*
south() {
    object ob;
    call_other(this_player(), "move_player", "north" + "#" +"players/catwoman/tl");
    return 1;
}
*/
long() {
    write("You are in the local Metropolis pub.\n");
    write("A large sign here says:\n");
    write("WE RESERVE THE RIGHT TO CHANGE PRICES WITHOUT NOTICE\n\n");
    write("You can order drinks here.\n\n");
    write("     First class beer    :  9  coins\n");
    write("     Cup of Starbucks    :  19 coins\n");
    write("     Battery Acid        : 120 coins\n");
    write("     Dragon Blood        : 210 coins\n\n");
    write("The only obvious exit is north.\n");
}
 

order(str)
{
    string name, short_desc, mess;
    int value, cost, strength, heal;

    if (!str) {
       write("Order what ?\n");
       return 1;
    }
    if (str == "beer") {
        mess = "That feels good";
        heal = 1;
        value = 9;
        strength = 3;
    }
 
    else if (str == "acid" || str == "Battery acid") {
        mess = "it burns as it goes through your body";
        heal = 10;
        value = 120;
        strength = 7;
    } else if (str == "dragons blood" || str == "blood") {
        mess = "A cloud of smoke steams out of you ears";
        heal = 20;
        value = 210;
        strength = 14;
    } else if (str == "coffee" || str == "starbucks") {
        mess = "WOW !! It must have been a double shot!";
        heal = 0;
        value = 20;
        strength = -2;
    } else {
 
       write("The bartender says: What do you want?\n");
       return 1;
    }
    if (call_other(this_player(), "query_money", 0) < value) {
        write("That costs " + value + " gold coins, which you don't have.\n");
        return 1;
    }
    cost = value;
    if (strength > (call_other(this_player(), "query_level") + 2)) {
        if (strength > (call_other(this_player(), "query_level") + 5)) {
            /* This drink is *much* too strong for the player */
            say(call_other(this_player(), "query_name", 0) + " orders a " +
                str + ", and immediately throws it up.\n");
            write("You order a " + str + ", try to drink it, and throw up.\n");
        } else {
            say(call_other(this_player(), "query_name", 0) + " orders a " +
 
                str + ", and spews it all over you!\n");
            write("You order a " + str + ", try to drink it, and sputter it all over the room!\n");
        }
        call_other(this_player(), "add_money", - cost);
        return 1;
    }
    if (!call_other(this_player(), "drink_alcohol", strength)) {
        write("The bartender says: I think you've had enough.\n");
        say(call_other(this_player(), "query_name", 0) + " asks for a " +
                str + " but the bartender refuses.\n");

        return 1;
    }
    write("You pay " + cost + " coins for a " + str + ".\n");
    say(call_other(this_player(), "query_name", 0) + " orders a " + str + ".\n");
    call_other(this_player(), "add_money", - cost);
 
    call_other(this_player(), "heal_self", heal);
    write(mess + ".\n");
    return 1;
}


