inherit "obj/monster";
   object gold;

reset(arg){
   ::reset(arg);
   if(arg) return;
   set_name("member");
   set_race("cult");
   set_alias("master");
	set_short("Cult Master of the darkside cult");
	set_long("The man has a yellow scarf around his neck and a white silk patch\n"+
"over his right eye.  As you look into his eyes you can see the evil\n"+
"that controls is soul.  Something about his missing eye makes you shiver.\n");
   set_level(20);
   set_hp(700);
   set_al(-1000);
   set_wc(30);
   set_ac(17);
   set_chance(20);
   set_spell_dam(45);
	set_spell_mess1("Cult member summons a demon.\n");
	set_spell_mess2("A demon appears and strikes you down.\n");
	set_a_chat_chance(5);
   set_chat_chance(2);
	load_chat("Cult member says: We have to get to the portal and destroy it.\n");
	load_chat("Cult member says: The ancients must be destroyed!\n");
	load_a_chat("Cult member says: Only the chosen one could defeat our quest.\n");
    gold = clone_object("obj/money");
   gold->set_money(random(4444)+900);
   move_object(gold,this_object());
}
