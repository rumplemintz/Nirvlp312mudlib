#include <security.h>
#include "/obj/lib/living/settings.h"

inherit "obj/living.c";

int handnum, gold, flg, starts_thinking;
int busyct;
int atflg;
object yesply, notply;

short() { return "A man pushing a cart"; }

long(str) {
  write("There appear to be corpses in the cart.\n");
  return;
}

id(str) {
  return str =="man"||str=="cart";
}

reset(arg) {
  yesply=clone_object("/players/boltar/things/corpse");
  move_object(yesply,this_object());
  if (arg)
    return;

  cap_name = "A man";
  name = "man";
  level = 5;
  experience = 2000;
  max_hp = 170;
  hit_point = 170;
  weapon_class = 9;
  armor_class = 3;
  is_npc = 1;
  alignment = 60;
  enable_commands();
}

catch_tell(str) {
  int ran, expl;
  string who, what;
  int repro;
  object offspring;

/*
  if (attacker_ob) {
    set_heart_beat(1);
    return;
  }
*/
  if(attacker_ob) return;
  if(busyct) return;
  busyct = 1;
  if (sscanf(str, "%s man %s\n", who , what) == 2 ) {
    busyct = 0;
    return 1;
  }
  ran = random(16);
  if (ran == 1) {
    say("Man says: Bring out your dead!!\n");
    random_move();
    busyct = 0;
    return 1;
  }
  if (ran == 11)
    say("Man says: Bring out your dead!!\n");
  if (ran == 3) {
    say("**clang**\n");
    random_move();
  }
  if (ran == 4) {
    say("Man says: he says he's not dead!\n");
    random_move();
  }
  if (ran == 5)
    say("Corpse says: I'm getting better!\n");
  if (ran == 6)
    say("Corpse says: I'm not dead!\n");
  if (ran == 10 || ran == 0)
    say("Man says: I got to go on to Robinson's -- they've lost nine today.\n");
  if (ran == 7)
    say("Man says: Oh, I can't take him like that -- it's against regulations.\n");
  if (ran == 15)
    say("Corpse says: I don't want to go in the cart!\n");
  if (ran == 8)
    say("Corpse says: I feel happy... I feel happy.\n");
  if (ran == 9)
    say ("Man says: Bring out your dead!\n");
  if (ran == 2) {
    random_move();
    repro = random(100);
  }
  busyct = 0;
  return 1;
}

heart_beat() {
  age += 1;
  already_fight = 0;
  attack();
/*
  set_heart_beat(0);
*/
}

random_move() {
  int n;
  n = random(4);
  if (n == 0)
    command("west");
  else if (n == 1)
    command("east");
  else if (n == 2)
    command("south");
  else if (n == 3)
    command("north");
}
