/*
 * A pain-in-the-ass monster for high-levs. It is the monster most commonly cloned in
 * ChAoS and has no treasure (also aggressive). Another annoying facet of the realm.
 */

inherit "/obj/monster";
 
reset(arg) {
   ::reset(arg);
   if (!arg) {
 
     set_name("giant crawdad");
     set_short("A giant crawdad");
     set_race("chaoscreature");
     set_alias("crawdad");
     set_long(
"This is a huge reddish-grey monster with two powerful \n" +
"claws it uses to rend its prey.\n");
     set_level(10 + random(6));
     set_ac(10 + random (8));
     set_wc(16 + random(4));
     set_hp(200 + random(80));
     set_al(0);
     set_aggressive(1);
set_chance(15);
set_spell_mess1("The crawdad crushes a victim in its claws.\n");
set_spell_mess2("The crawdad crushes you in its claws.\n");
set_spell_dam(10);
   }
}
 
