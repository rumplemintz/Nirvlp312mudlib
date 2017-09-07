inherit "obj/monster";
reset(arg){
   object gold,gloves;
   ::reset(arg);
   if(arg) return;
   set_name("weirdo");
   set_race("human");
   set_alias("ringer");
   set_short("Weirdo, the bell ringer");
   set_long("Weirdo, the bell ringer.  He's a poor little humpback.\n");
   set_level(7);
   set_hp(105);
   set_al(50);
   set_wc(11);
   set_ac(6);
   set_aggressive(0);
   set_chat_chance (15);
   load_chat("Weirdo says: Oh my poor hands!!!\n");
   load_chat("Weirdo looks sadly at his hands.\n");
   load_chat("Weirdo says: This pair of gloves are useless for my poor hands.\n");
   load_chat("Weirdo sighs.\n");
   set_chance(10);
   set_spell_dam(random(1)+1);
   set_spell_mess1("Weirdo slaps you with his gloved hand.\n");
   set_spell_mess2("Weirdo kicks your butt.\n");
   gold=clone_object("obj/money");
   gold->set_money(150);
   move_object(gold,this_object());
   gloves=clone_object("players/trix/castle/primonst/gloves.c");
   move_object(gloves,this_object());
}