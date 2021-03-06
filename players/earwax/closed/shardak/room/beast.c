/*
 * Shardak guild is (tm) Dragnar/John, also Balowski/Rasmus
 * Change log:
 * 950525 - created
 * 951008 - trying to stop the bug that stops heartbeat :-( puzzling
 *          it was a bug in the mudlib..
 * 001108 - changed properties, made it much harder [verte]
 */
#pragma strict_types
#include "../include/def.h"
#include "../include/ansi.h"
inherit "/players/vertebraker/closed/std/monster";

mixed assault_room();
mixed detect_prey();

void
reset(int arg)
{
    if (arg) return;
    ::reset(arg);
    set_name("The wildebeest");
    set_alias("beest");
    set_short(RED+"Wildebeest"+BOLD+BLK+" - the dragon keeper's champion"+NORM);
    set_long(BOLD+BLK+"\
A set of glowing "+HIR+"red eyes"+BLK+" meet you in the near dark. The beast\n\
vaguely resembles a human being. Its exaggerated limbs are covered\n\
by iron-grey scales and adorned by talons worthy of a dragon.\n\
Crouched over you, its enormous body seems to fill the whole room.\n\
Saliva drips in excess from finger-long, ivory-white fangs.\n"+NORM);
    set_level(20);
    set_alt_name("beast");
    set_attrib("wil", 30);
    set_attrib("str", 40);
    set_attrib("sta", 30);
    set_race("dragon");         /* of some sort */
    set_hp(1111);
    set_al(-500);               /* black knight */
    set_ac(18+random(5));
    set_wc(46);
    set_can_kill(1);
    set_gender("creature");
    set_no_exp_value(); /* HA! */
    set_init_ob(this_object());
    set_dead_ob(this_object());
    set_heal(2, 35);            /* default is rate 2, interval 35 */
    add_attribute("magic", 50); /* magic resistance.. */
    set_message_hit(({
    "massacred"," to a bloody pulp",        /* massacre */
    "smashed"," relentlessly",               /* smash */
    "assaulted"," with a talon slash",        /* v.hard */
    "ripped"," with unadulterated savagery",  /* hard */
    "stabbed"," in the chest",                /* hit */
    "nicked", " with a talon",
    "grazed", "", }));
    set_chance(30);
    set_spell_dam(60);
    set_spell_mess1("The Wildebeest "+HIR+"tears"+NORM+" into its enemy, spraying "+HIR+"blood"+NORM+" everywhere!");
    set_spell_mess2("The Wildebeest "+HIR+"tears"+NORM+" into you, spraying "+HIR+"blood"+NORM+" everywhere!");
}
/*
 * beast killed someone :-[
 */
void
catch_tell(string text)
{
    string who;
    if (stringp(text) && sscanf(text, "You killed %s.\n", who))
        call_out("evict_ghost", 2);
}

void
evict_ghost()
{
    object ob, next;

    /*
     * do this in 2 loops to let the ghosts see the devouring
     * of their corpses. muahaha
     */

    ob = first_inventory(environment());
    while (ob) {
        next = next_inventory(ob);
        if (ob->id("corpse")) {
            say("The Wildebeest devours the corpse and "+HIR+"glows with energy.\n"+NORM);
            heal_self((int) ob->heal_value());
            destruct(ob);
        }
        ob = next;
    }

    ob = first_inventory(environment());
    while (ob) {
        next = next_inventory(ob);
        if (ob->query_ghost()) {
            tell_object(ob,
                "In your misty form you seep up through the grating.\n");
            ob->move_player("up#" + PATH + "stable");
    }
        ob = next;
    }
}

/*
 * beast died
 */
int
monster_died(object myself)
{
    say("\
The huge monster staggers and falls to its knees.\n\
With a thunderous boom, its lifeless body collapses to the ground.\n");

    /*
     * I first tried setting the solved flag here, but saw
     * how wrong things can go if anything fails at this point.
     * Therefore this function is kept as simple as possible
     */

    /*
     * I will be destructed immediately after returning
     * therefore let the room handle the cheering, etc.
     */
    environment()->beast_died(attacker_ob);
    return 0;
}

/*
 * Someone enters
 * Beast will attack at next heartbeat (100% aggressive)
 * but without changing targets
 */
int
monster_init(object myself)
{
    if (this_player())
        attacked_by(this_player());
    return 0;   /* continue init(), returning 1 can result in no hb? */

}
/* specials rewritten by verte */

void
heart_beat()
{
    if(!attacker_ob) {
      if(!alt_attacker_ob && hit_point < max_hp) {
        hit_point += (15 + random(5));
        tell_room(environment(this_object()), "\
"+cap_name+" concentrates its dark energy.....\n\
An aura of healing encircles its body.\n");
        }

      else if(alt_attacker_ob) {
        tell_room(environment(this_object()), "\
"+cap_name+" snarls in rage and leaps to attack "
+ alt_attacker_ob->query_name()+".\n", ({ alt_attacker_ob }));
        tell_object(alt_attacker_ob,
  cap_name+" snarls in rage and leaps to attack you!\n");
        attack_object(alt_attacker_ob);
       }
     if(!attacker_ob) detect_prey();
     }

    else {
      if(0 == random(8)) {
        tell_room(environment(this_object()),
cap_name+" casts a spell of "+BOLD+BLK+"darkfire"+NORM
+ " upon "+attacker_ob->query_name()+"!\n",
        ({ attacker_ob }));
        tell_object(attacker_ob,
cap_name+" casts a spell of "+BOLD+BLK+"darkfire"+NORM
+ " upon you!\n");
        if(attacker_ob->query_alignment() < 0)
          attacker_ob->hit_player(30 + random(20), "other|dark");
        else attacker_ob->hit_player(60 + random(30), "other|dark");
        }
      if(0 == random(3))
         assault_room();
      if(0 == random(3)) {
        already_fight = 0;
        attack();
        }
      }
    ::heart_beat();
    }

void
assault_room()
{
    int x;
    object *inv;
    object old_attack;
    inv = all_inventory(environment(this_object()));

    for(x = 0; x < sizeof(inv); x++) {
      if(!random(2) && living(inv[x]) && !inv[x]->id(name)) {
        if(attacker_ob) old_attack = attacker_ob;
         already_fight = 0;
        attack_object(inv[x]);
        attack();
        if(old_attack) attack_object(old_attack);
        }
      }
    }

mixed
detect_prey()
{
    int         x;
    object      *inv;

    inv = all_inventory(environment(this_object()));
    for(x = 0; x < sizeof(inv); x++)
    if(inv[x]->is_player())
    {
      tell_room(environment(this_object()), "\
The Wildebeest leaps to attack "+inv[x]->query_name()+"!\n");
       tell_object(inv[x], "\
The Wildebeest leaps to attack you!\n");
      attack_object(inv[x]);
      return 1;
    }
}
