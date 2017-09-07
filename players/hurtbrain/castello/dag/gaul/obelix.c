inherit "obj/monster";
reset(arg){
   object gold,ob1;
   ::reset(arg);
   if(arg) return;
   set_name("obelix");
   set_race("human");
   set_short("Obelix");
   set_long("He is an enormous man. He is carrying a very heavy mace.\n");
   set_level(20);
   set_hp(500);
   set_al(100);
   set_wc(30);
   set_ac(17);
   set_chat_chance (30);
   load_chat("Obelix says: 'Perhaps I can find some wild boars for lunch.'\n");
   load_chat("Obelix shouts: 'There are no roman soldiers here?' *sigh*\n");
   load_chat("Obelix says: 'Asterix? Idefix? Where are you?'\n");
   set_chance(10);
   set_spell_dam(15+random(15));
   set_spell_mess1("Obelix throws his mace.\n");
   set_spell_mess2("Obelix throws his mace on you.\n");
   gold=clone_object("obj/money");
   gold->set_money(2000 + random(200));
   move_object(gold,this_object());
   ob1=clone_object("players/hurtbrain/castello/dag/gaul/mace");
   move_object(ob1,this_object());
   ob1=clone_object("players/hurtbrain/castello/dag/gaul/boots");
   move_object(ob1,this_object());
}