/*
 * Shardak guild - (tm) Dragnar/John
 * Smithy is (c) Balowski/Rasmus, March 19th 1995.
 * The smith will repair and sharpen weapons
 * The smithy is supposed to be a weapons and armour shop
 * Last, the smith will have a task :)
 * change log:
 * 950417 - racks for buying equip
 * 950421 - ROOM
 * 030715 - Added color, tweaked desc, and added exits
 *          readable only by shardaks [linus]
 * 030719 - fixed long so items work again [linus]
 */

#pragma strict_types
#include "/players/balowski/lib.h"
#include "../include/def.h"
#include "../include/ansi.h"
inherit ROOM;

void
create()
{
    ::create();
    set_short(RED+"Weapons smithy"+NORM);
    set_long(HIK+"\
This room is very warm, the heat coming from the mouth of a big\n\
furnace.  A deep orange glow slowly floods the room, failing to\n\
reach the dark corners of the room.  A blackened iron anvil is\n\
bathed in the soft light from the furnace.  Upon a nearby rock\n\
wall a filthy iron plaque is mounted.\n"+NORM);
    set_items(([
"plaque" : "\
Underneath the filth it is meticulously engraved:\n\
\tWeapons repaired or sharpened for a fee.\n\
\t\tUse 'repair <weapon>' or 'sharpen <weapon>'\n\
\tQuality equipment sold for a reasonable price.\n\
\t\tUse 'list' to see what is in stock.\n",
"anvil" : "\
This is where the smith does most of his work. The working surface has\n\
been worn smooth and shiny.\n",
"furnace" : "\
The extreme heat from the furnace blazes in your face and makes your\n\
skin prickle. A few very lively flames dance playfully around on the\n\
coals, leaving white streaks of heat behind.\n",
    ]));
    set_light(1);
    set_exits(([
             "southwest" : (PATH + "grotto"),
             "south" : (PATH + "shop"),
    ]));
    set_property("fight area", 1);
    set_property("no teleport", 1);
}

void
reset(int arg)
{
    object smith;

    ::reset(arg);
    smith = present("smith", this_object());
    if (!smith) {
             smith = clone_object(PATH + "smith");
             smith->move_player("in#" + file_name(this_object()));
    }
}

void
init()
{
    ::init();
    add_action("repair", "repair");
    add_action("sharpen", "sharpen");
    add_action("list", "list");
    add_action("buy", "buy");
}


status
repair(string str)
{
    object      weapon;
    int         fee;

    if (!present("smith", this_object())) {
             notify_fail("The smith is currently out.\n");
             return 0;
    }
    if (!str) {
             notify_fail("The smith ignores you.\n");
             return 0;
    }
    weapon = present(str, this_player());
    if (!weapon) {
             write("The smith rumbles, \"You have no " + str + ".\"\n");
             return 1;
    }
    if (!weapon->weapon_class()) {
             write("The smith mutters, \"Can't help you with that.\"\n");
             return 1;
    }
    if (!weapon->query_broke()) {
             write( "The smith says, \"Can't repair what's not broken.\"\n");
             return 1;
    }
    if (weapon == (object) this_player()->query_weapon()) {
             write("The smith says, \"D'you mind unwielding it first?\"\n");
             return 1;
    }

    if (function_exists("sharpen_weapon", weapon)) {
             fee = ((int) weapon->query_Wear())/200;
             if (fee < 50) fee = 50;

             if (!weapon->fix_weapon()) {
                 write("The smith says, \"'fraid it's beyond repair.\"\n");
                 return 1;
             }
             write("\
The smith takes your broken weapon and puts it into the furnace.\n\
After a while he pulls it out again, its tip now "+HIR+"glowing brightly"+NORM+",\n\
and with a bit of hammering the smith brings the weapon back to its\n\
original state.\n");
    }
    else {
             /* the old fix_weapon() always works (and does a write, dammit) */
             write("\
The smith takes your broken weapon and puts it into the furnace.\n\
After a while he pulls it out again, its tip now "+HIR+"glowing brightly"+NORM+",\n\
and with a bit of hammering the smith brings the weapon back to its\n\
original state.\n");
             weapon->fix_weapon();
        fee = 300;
    }

    if (this_player()->query_money() < fee) {
             write("\
The smith says, \"So you can't pay? I will keep the weapon then.\"\n");
             if (transfer(weapon, RACKS))
                 destruct(weapon);
    }
    else {
             write("You pay the smith his " + fee + " gold coins fee.\n");
             this_player()->add_money(-fee);
    }
    return 1;
}

status
sharpen(string str)
{
    object      weapon;
    int         fee, class;

    if (!present("smith", this_object())) {
             notify_fail("The smith is currently out.\n");
             return 0;
    }
    if (!str) {
             notify_fail("The smith ignores you.\n");
             return 0;
    }
    weapon = present(str, this_player());
    if (!weapon) {
             write("The smith rumbles, \"You have no " + str + ".\"\n");
             return 1;
    }
    if (!weapon->weapon_class()) {
             write("The smith mutters, \"Can't help you with that.\"\n");
             return 1;
    }
    if (weapon->query_broke()) {
             write("The smith says, \"Can't sharpen what's broken, friend.\"\n");
             return 1;
    }
    if (weapon == (object) this_player()->query_weapon()) {
             write("The smith says, \"D'you mind unwielding it first?\"\n");
             return 1;
    }
    if (function_exists("sharpen_weapon", weapon)) {
        fee = 300;
             if (!weapon->sharpen_weapon()) {
                 write("The smith says, \"'fraid this weapon can't be sharpened.\n");
                 return 1;
             }
             write("\
The smith takes the weapon and walks over to a workbench in a corner\n\
of the room. He gives your weapon a good work-over on both grindstone\n\
and oilstone.\n");
    }
    else {
             class = (int) weapon->weapon_class();
        fee = 300;
             write("\
The smith takes the weapon and walks over to a workbench in a corner\n\
of the room. He gives your weapon a good work-over on both grindstone\n\
and oilstone.\n");
             weapon->re_break();
             if (weapon) weapon->fix_weapon();
             if (weapon) weapon->set_class(class);
    }
    if (!weapon) {
             write("The smith says, \"Oops. I accidentally destroyed your weapon.\"\n");
             return 1;
    }

    if (this_player()->query_money() < fee) {
             write("\
The smith says, \"So you can't pay? I will keep the weapon then.\"\n");
             if (transfer(weapon, RACKS))
                 destruct(weapon);
    }
    else {
             write("You pay the smith his " + fee + " gold coins fee.\n");
             this_player()->add_money(-fee);
    }
    return 1;
}

status
list(string str)
{
    if (!present( "smith", this_object())) {
             notify_fail( "The smith is currently out.\n");
             return 0;
    }
    if (RACKS->cmd_list())
             write( "You can buy by name, e.g. 'buy sword 2'.\n");
    else
             write( "The smith smiles and says, \"All sold out, I'm afraid.\"\n");
    return 1;
}

status
buy(string thing)
{
    int i;

    if (!present( "smith", this_object())) {
             notify_fail( "The smith is currently out.\n");
             return 0;
    }
    switch (i = (int) RACKS->cmd_buy(thing)) {
    case 0:
             write("The smith glares at you: Take a look at the list!\n");
             break;
    case -1:
             write("That is not for sale.\n");
             break;
    case -2:
             write("You do not have enough gold.\n");
             break;
    case -3:
             write("You are carrying too much to take it.\n");
             break;
    default:
             write("You pay the smith for the " + thing + ".\n");
             break;
    }
    return 1;
}

/* Room long description, shows exits only to Shards */

void
long(string arg) {
 if(!arg) {
  if((int)this_player()->query_brief() != 2) 
   write(RED+"Weapons Smithy\n"+NORM);
    ::long(arg);
  if(present("shardak_mark",this_player())) 
   write("\t"+NORM+RED+"\The exits are: south and southwest.\n"+NORM);
    return;
 }
  else ::long(arg);
}

