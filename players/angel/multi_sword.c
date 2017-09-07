/*                                                                    *
 *    File:         /players/angel/area/mulit_sword.c                 *
 *    Function:         OBJ                                           *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           07/04/17                                      *
 *    Notes:                                                          *
 *                                                                    *
 *                                                                    *
 *    Change History:                                                 *
 */

#include "/sys/lib.h"

#include <ansi.h>

inherit "obj/weapon.c";

#define BASE 50
#define DAM 5
#define tp this_player()
#define tpn tp->query_name()
#define tal tp->query_alignment()

int T;
int x;
int X;
int Y;
int Z;
string TYPE;
string NAME;
string WHAT;
reset(arg) {
  ::reset(arg);
  if (arg) return;
  T = (random(7));
  Y = (random(20));
  Z = (random(24));
  X = (Y+15);

  if(T == 0) TYPE = "sword";
  if(T == 1) TYPE = "shortsword";
  if(T == 2) TYPE = "longsword";
  if(T == 3) TYPE = "broadsword";
  if(T == 4) TYPE = "two-handed sword";
  if(T == 5) TYPE = "khopesh sword";
  if(T == 6) TYPE = "uchigatana sword";
  
  if(X == 16) NAME = "Blackout";
  if(X == 17) NAME = "Skyfall";
  if(X == 18) NAME = "Armageddon";
  if(X == 19) NAME = "Storm";
  if(X == 20) NAME = "Barbarian";
  if(X == 21) NAME = "Nightcrackle";
  if(X == 22) NAME = "Godslayer";
  if(X == 23) NAME = "Ghostwalker";
  if(X == 24) NAME = "Eclipse";
  if(X == 25) NAME = "Purifier";
  if(X == 26) NAME = "Restorer";
  if(X == 27) NAME = "Lifedrinker";
  if(X == 28) NAME = "Honor's Call";
  if(X == 29) NAME = "Agatha";
  if(X == 30) NAME = "Phoenix";
  if(X == 31) NAME = "Annihilation";
  if(X == 32) NAME = "Lazarus";
  if(X == 33) NAME = "Spineripper";
  if(X == 34) NAME = "The Void";
  if(X == 35) NAME = "Hope's End";

  if(Z == 0) WHAT = "Ender of Broken Bones";
  if(Z == 1) WHAT = "Iron Crusader";
  if(Z == 2) WHAT = "Blood of the Storm";
  if(Z == 3) WHAT = "Last Stand of Summoning";
  if(Z == 4) WHAT = "Blessing of the Plague";
  if(Z == 5) WHAT = "Deflector of Oblivion";
  if(Z == 6) WHAT = "Diamond Protector";
  if(Z == 7) WHAT = "Blood of Blessings";
  if(Z == 8) WHAT = "Mithril Skewer";
  if(Z == 9) WHAT = "Mageblade of Holy Might";
  if(Z == 10) WHAT = "Soul of Justice";
  if(Z == 11) WHAT = "Sculptor of Phoenix";
  if(Z == 12) WHAT = "Token of Shadow Strikes";
  if(Z == 12) WHAT = "The Honed Doomblade";
  if(Z == 14) WHAT = "Last Stand of Titans";
  if(Z == 15) WHAT = "Protector of the Stars";
  if(Z == 16) WHAT = "Promise of the Forest";
  if(Z == 17) WHAT = "Mithril Slicer";
  if(Z == 18) WHAT = "Skeletal Warblade";
  if(Z == 19) WHAT = "The Lone Victor";
  if(Z == 20) WHAT = "Ravager of Illumination";
  if(Z == 21) WHAT = "Quickblade of Hope";
  if(Z == 22) WHAT = "Sword of Dragonsouls";
  if(Z == 23) WHAT = "Slayer of Due Diligence";

  set_name("sword");
  set_type(""+TYPE+"");
  set_short(""+HIR+""+NAME+", "+HIW+""+WHAT+""+NORM+"");
  set_long("  This "+TYPE+" was forged by the Legondary blacksmith Tybalt\n\
using Earth, Moon and Fire stones. It is the optimal fighting sword.\n\
It has been finely honed to fit "+tpn+"'s hand!\n");
  set_class(19);
  set_weight(2);/*Drawback heavy sword*/
  set_value(0);/*This sword is priceless and is not easy to obtain*/
  set_hit_func(this_object());
  set_params("other|fire",1,"fire_hit");
}

fire_hit(attacker){
  if (random(8)>4) {
    say(""+HIW+"~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~"+NORM+"\n\
"+HIR+"The Sword draws "+HIW+""+tpn+"'s"+HIR+" blood and blazes with"+NORM+" "+HIW+BLINK+"white"+NORM+""+HIR+" fire."+NORM+"\n\
"+HIW+"~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~"+NORM+"\n");
    write(""+HIW+"~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~"+NORM+"\n\
"+HIR+"The Sword draws "+HIW+""+tpn+"'s"+HIR+" blood and blazes with"+NORM+" "+HIW+BLINK+"white"+NORM+""+HIR+" fire."+NORM+"\n\
"+HIG+"The "+HIB+"Earth, "+HIW+"Moon "+HIC+"and "+HIR+"Fire "+HIG+"stones go after your enemy with"+NORM+" "+HIW+BLINK+"Vengeance."+NORM+"\n\
"+HIW+"~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~"+NORM+"\n");
this_player()->add_spell_point(-1);/*Drawback loss of Spell points*/
    return 3;
  }
}

get() {
    if(tal < BASE) {
        write("You are not worthy enough to touch this sword!\n");
        write("Lightning from the heavens strike you!\n");
        say(tpn+" yelps as "+tp->query_pronoun()+" attempts to touch the Sword.\n");
        tp->hit_player(DAM);/*Drawback requires good alignemnt to hold sword*/
    return 0;}
return 1; }