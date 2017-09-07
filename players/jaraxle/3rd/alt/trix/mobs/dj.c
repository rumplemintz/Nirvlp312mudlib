inherit "obj/monster";
reset(arg){
   object gold,record;
   ::reset(arg);
   if(arg) return;
   set_name("dj");
   set_race("human");
   set_alias("deejay");
   set_short("The DJ");
   set_long("An eccentric dj , a creature of the night , he's in his environment , he's HUGE.\n");
   set_level(20);
   set_hp(500);
   set_al(1000);
   set_wc(30);
   set_ac(17);
   set_aggressive(0);
   set_chat_chance (14);
   load_chat("DJ says: techno techno techno techno.\n");
   load_chat("DJ says: boom boom boom.\n");
   load_chat("DJ looks at the crowd dancing and grins.\n");
   set_chance(7);
   set_spell_dam(random(5)+2);
   set_spell_mess1("DJ pushes you.");
   set_spell_mess2("DJ throws a record to you.");
   gold=clone_object("obj/money");
   gold->set_money(2900 + random(100));
   move_object(gold,this_object());
   record=clone_object("players/trix/castle/dismonst/record.c");
   move_object(record,this_object());
}