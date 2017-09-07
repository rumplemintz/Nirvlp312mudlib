/*                                                                    *
 *    File:         /players/angel/area/mansion/obj/masonic_sword_01.c*
 *    Function:         OBJ                                           *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           02/7/17                                       *
 *    Notes:                                                          *
 *                                                                    *
 *                                                                    *
 *    Change History:                                                 *
 */
#include <ansi.h>

#define BASE 100
#define DAM 20
#define tp this_player()
#define tpn tp->query_name()
#define tal tp->query_alignment()

inherit "obj/weapon.c";

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_name("masonic sword");
  set_type("sword");
  set_short(HIY+"M"+HIW+"asonic"+NORM+" "+HIY+"S"+HIW+"word"+NORM);
  set_long("The masonic sword is the optimal fighting sword. It is finely\n\
detailed with the Square which symbolizes things of the earth,\n\
and it also symbolizes honor, integrity, truthfulness, and the\n\
other ways we should relate to this world and the people in it.\n\
The Compasses symbolize things of the spirit, and the importance\n\
of a good and well-developed spiritual life, and also the\n\
importance of self control - of keeping ourselves within bounds.\n\
The G stands for Geometry, the science which the ancients believed\n\
most revealed the glory of God and His works in the heavens.\n\
It also stands for God, Who must be at the center of all our\n\
thoughts and of all our efforts.\n");
  set_class(19);
  set_weight(1);
  set_value(1500);
  set_hit_func(this_object());
  set_params("other|fire",1,"fire_hit");
}

fire_hit(attacker){
  if (random(10)>6) {
    say("The Masonic Sword searches for more "+HIW+"light"+NORM+".\n\
The sword sucks up the "+HIW+BLINK+"light"+NORM+" and goes after you with "+HIW+BLINK+"God's Vengeance"+NORM+"\n");
    write("The Masonic Sword searches for more "+HIW+"light"+NORM+".\n\
The sword sucks up the "+HIW+BLINK+"light"+NORM+" and goes after you with "+HIW+BLINK+"God's Vengeance"+NORM+"\n");
    return 5;
  }
}

get() {
    if(tal < BASE) {
        write("You are not worthy enough to touch this sword!\n");
        write("Lightning from the heavens strike you!\n");
        say(tpn+" yelps as "+tp->query_pronoun()+" attempts to touch the Masonic Sword.\n");
        tp->hit_player(DAM);
    return 0;}
return 1; }