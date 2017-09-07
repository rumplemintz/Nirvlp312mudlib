#include <ansi.h>
inherit "/obj/monster";
#define IT capitalize(obj->query_name())

reset(arg) {
  ::reset(arg);
  if(arg) return;
  set_name("Manticore");
  set_alias("manticore");
  set_short("A Manticore");
  set_long(
  "This rare beast has the body of a strong lion, the tail of a poisoness\n"+
  "scorpian, and a face that is nearly human.  Two steel-grey eyes gaze\n"+
  "at you from the Manticore's gruesome visage.  It's huge gaping maw is\n"+
  "lined with 3 rows of sharp, deadly teeth.  The Manticore's tail is\n"+
  "tipped with several 3' spikes.\n");
  set_race("manticore");
  set_level(20+random(5));
  set_hp(425+random(275));
  set_ac(10+random(15));
  set_al(-(500+random(500)));
  set_aggressive(0);
  set_dead_ob(this_object());
  call_out("fake_beat", 5);
}

id(str) {
  return str == "manticore" || str == "ilstkarn_monster";
}

init() {
  ::init();
  if(this_player()->is_player() && !this_object()->query_attack()) {
     call_out("threaten", 5, this_player());
  }
}

threaten(obj) {
  tell_object(obj,
  "Slivak hisses loudly, hot flames lash out from between its teeth.\n"+
  "Slivak snickers: Hello "+IT+".  Are you prepared for "+HIR+"eternal sleep!?\n"+NORM);
  tell_object(obj,
  "Slivak throws its head back and cackles with glee!\n");
  return;
}

/*
 * As usual, I don't like players being able to stop a fight.
 */
stop_fight() {
  if(this_player()->query_level() > 20) {
    ::stop_fight();
    return 1;
  }
  return;
}

/*
 * None of this heal_self crap
 */
heal_self(i) {
  if(i <= 0) {
    return;
  }
  else {
    ::heal_self(i);
  }
  return;
}

/*
 * No modifying stats either!
 */
set_ac(x) {
  if(this_player() != this_object()) { return; }
  ::set_ac(x);
  return 1;
}

set_wc(x) {
  if(this_player() != this_object()) { return; }
  ::set_wc(x);
}

set_heal_rate(x,y) {
  if(this_player() != this_object()) { return; }
  ::set_heal_rate(x,y);
}

/*
 * Do some interesting combat stuff.
 */
fake_beat() {
  object obj, arm;
  int i;

  obj = this_object()->query_attack();
  
  if(!obj || !present(obj, environment(this_object()))) {
    call_out("fake_beat", 10);
    return 1;
  }

  i = random(12);
  arm = present("ilstkarn_magic_armor", obj);

  /*
   * Summon a helper
   */
  if(i == 1) {
    int help_count;
    object roominv;
    int x;

    help_count = 0;
    roominv = all_inventory(environment(this_object()));

    for(x=0; x<sizeof(roominv); x++) {
       if(roominv[x]->id("fire demon"))
          help_count++;
    }

    /*
     * Let's make sure it doesn't get too crowded here...
     */
    if(help_count < 3) {
       object obh;
       tell_room(environment(this_object()),
       "Slivak raises his arms and speaks: "+HIR+"Ghundak Tsurak!\n"+NORM+
       "A being shimmers into view.\n");
       tell_room(environment(this_object()),
       "Slivak points and the creature attacks!\n");
       obh = clone_object("players/pavlik/monsters/ilstkarn/slivak_helper");
       move_object(obh, environment(this_object()));
       obh->do_help(obj);
    }
    else {
       tell_room(environment(this_object()),
       "Slivak says: "+HIR+"Ghundak Tsurak!"+NORM+"\n"+
       "The ground shakes beneath your feet!\n");
    }
  }

  /*
   * Cast a spell: Damage is 50
   */
  if(i == 3) {
    tell_room(environment(obj),
    "Slivak shouts: "+HIR+"Vestak! Vouzri!\n"+NORM+
    "A "+HIR+"huge fireball"+NORM+" shoots from its fingertips and SLAMS "+IT+"!\n");
    tell_object(obj,
    "The "+HIR+"ball of fire"+NORM+" torches you!\n");
    if(arm && arm->query_worn()) arm->do_fire_damage(50);
    else obj->hit_player(50);
  }

  /*
   * Cast a spell: Damage is 30 + random(70)
   * Spell kills an NPC outright.
   */
  if(i == 4) {
    tell_room(environment(this_object()),
    "Slivak cups its hands in front of its face and a "+HIR+"blazing sphere"+
    "of fire\n"+NORM+
    "appears in its cupped palms!\n"+
    "Slivak blows the "+HIR+"Fireball"+NORM+" at "+IT+" ...\n");
    tell_room(environment(this_object()),
    "The fireball strikes "+IT+" and "+HIR+" E X P L O D E S ! ! !\n"+NORM);

    if(!obj->is_player()) {
       tell_room(environment(this_object()),
       HIM+IT+" is instantly incinerated in the blast!\n"+NORM);
       move_object(obj, "players/pavlik/waste_room");
       destruct(obj);
    }
    else {
       tell_object(obj,
       "You are "+HIM+"-severly burned-"+NORM+" by the blast!\n");
       if(arm && arm->query_worn()) arm->do_fire_damage(30+random(70));
       else obj->hit_player(30+random(70));
    }
  }

  /*
   * Cast a spell: Damage is 20 + random(40)
   */
  if(i == 7) {
    tell_room(environment(this_object()),
    "Slivak points his finger at "+IT+" and a "+HIY+"Column of Flame\n"+NORM+
    "erupts from the ground!\n"+
    "The smell of "+HIR+"burning flesh"+NORM+" taints the air.\n");
    if(arm && arm->query_worn()) arm->do_fire_damage(20+random(40));
    else obj->hit_player(20+random(40));
  }

  /*
   * Make some threats
   */
  if(i == 8 && obj->is_player()) {
    int ran;
    string gname;

    gname = capitalize(obj->query_guild_name());
    if(!gname) gname = "Adventurer";
    if(gname == "Rangers") gname = "Ranger";

    ran = random(4);
    if(ran == 0) tell_room(environment(this_object()),
    "Slivak says: Come on, "+IT+".  Is that the best you can do?\n");
    else if(ran == 1) tell_room(environment(this_object()),
    "Slivak hisses: "+IT+", you are the weakest "+gname+" I have ever seen!\n"+
    "Slivak chortles demonically.\n");
    else if(ran == 2) tell_room(environment(this_object()),
    "Slivak says: I will hang your head on my wall, "+IT+"!\n");
    else if(ran == 3) tell_room(environment(this_object()),
    "Slivak hisses: I will EAT "+IT+"'s heart for my dinner!\n");
  }

  /*
   * Destroy the attackers weapon
   */
  if(i == 11 && obj->query_weapon()) {
    object weap, mag;
    weap = obj->query_weapon();

    tell_room(environment(this_object()),
    "Slivak "+HIM+"grabs "+NORM+IT+"'s weapon in midcombat and shouts: "+HIC+"Shczlah!\n"+NORM);

    /*
     * If magic resistance then only drop the weapon.
     * Otherwise, the weapon gets destroyed
     */
    mag = present("_magic_armor", obj);
    if(mag && mag->query_worn()) {
      tell_object(obj,
      "Your weapon becomes "+HIY+"super-heated"+NORM+" and you are forced to drop it\n"+
      "before you get severly burned!\n");
      tell_room(environment(obj),
      IT+" cries out and drops "+obj->query_possessive()+" weapon!\n");
      command("drop "+weap->query_name(), obj);
    }
    else {
      tell_room(environment(obj),
      IT+"'s weapon begins to glow with "+HIR+"intense heat!\n"+NORM);
      tell_object(obj,
      "Your weapon becomes "+HIY+"super-heated"+NORM+" and "+HIC+"melts!\n"+NORM+
      HIC+"The "+weap->query_name()+HIC+" is destroyed!\n"+NORM);
      weap->drop(1);
      destruct(weap);
    }
  }

  call_out("fake_beat", 5);
  return;
}

monster_died() {
  if(this_player()->query_real_name())
    write_file("/players/pavlik//LOG",
    capitalize(this_player()->query_real_name())+" killed the Slivak. ["+ctime()+"]\n");
  return 0;
}
