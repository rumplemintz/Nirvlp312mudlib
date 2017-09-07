#include <ansi.h>

int stealthed, combo, sstrike;
int eviscerate, sap, backstab;
int pickpocket, ambush, blind, garrote;

object offwep, firstwep;

id(str) { return (str == "seal" || str == "rogue_seal" || str == "shinshi_rogue_seal" || 
          str == "GI" || str == "no_pet" || str == "no_spell" || str == "pro_object" ||
          str == "dark_sight_object" || str == "generic_wc_bonus");}


short() {return "A rogue's seal";}

long() {
	write("\n");
   write("The symbol of the Brotherhood. A small,\n");
   write("golden seal that has a pair of embossed\n");
   write("daggers which are crossed at the blade.\n");
   write("A dark green liquid is stained on the\n");
   write("top part of the seal.\n");
   write("Type 'rhelp' for your guild commands.\n");
}

get() {
   return 1;
}

drop() {
   return 1;
}

reset(arg){
	if(arg) return;
	set_heart_beat(1);
        call_out("rogue_save", 1800);
}

rogue_save()
{
       object ob;
       ob = environment(this_object());
       command("rsave", ob);
       call_out("rogue_save", 1800);
       return 1;
}

init() {
	int c;
	string *spells, cmd;
	
	if(!environment()) return;
	restore_object("players/shinshi/closed/rogue/members/"+environment(this_object())->query_real_name());
	if(environment(this_object())->query_level() < 100){
		environment(this_object())->set_guild_name("Rogue");
                environment(this_object())->set_guild_file(basename(this_object()));
	}
   
   "/players/shinshi/closed/rogue/objects/chatob.c"->resetchannel();

	
   c = sizeof(spells = files("/players/shinshi/closed/rogue/spells/"+"*.c"));
   while(c--)
   {
	   sscanf(spells[c], "%s.c", cmd);
	   add_action("cmd_hook", cmd);
	   add_action("rsave", "rsave");
	   add_action("kkill", "kkill");
   }
}

guild_login() {
	write(HIR);
	cat("/players/shinshi/closed/rogue/login.txt");
	write(NORM);
	return 1;
}

mixed cmd_hook(string str)
{
	string go;
	
	go = "/players/shinshi/closed/rogue/spells/"+query_verb()+".c";
	
	if(file_size(go) > 0)
		return (mixed) go->main(str, this_object(), this_player());
		return 0;
	}

rhelp(str)
{
	if(!str)
	{
		cat("/players/shinshi/closed/rogue/help/main.txt");
		return 1;
	}
}

rsave(){
	save_object("players/shinshi/closed/rogue/members/"+environment()->query_real_name());
	tell_object(environment(), HIK+"Saving Guild Information."+NORM+"\n");
	tell_object(environment(), HIK+"Save Complete."+NORM+"\n");
       return 1;
}

kkill(str){
	object meat;
	
	if(this_player()->query_ghost())
	{
		write("You're dead!\n");
		return 1;
	}
	
	if(!str)
	{
		tell_object(this_player(), "You must specify a target.\n");
		tell_object(this_player(), "\"kill <name>\"\n");
		return 1;
	}
	
	meat = present(str, environment(this_player()));
	
	if(!meat)
	{
		write("You don't see "+meat+" here.\n");
		return 1;
	}
	
	if(!living(meat))
	{
		write("That isn't alive to attack!\n");
	}
	
	if(meat) if(!check_rogue_attack(meat)) {
		tell_object(environment(), "The shadows disallow you to continue with your attack.\n");
		return 1;
	}
	
	this_player()->attack_object(meat);
	return 1;
}

check_rogue_attack(object meat)
{
	object room, meat_attacker;
	int meat_hp, meat_mhp;
	
	if(!meat)
	return 0;
	
	if(meat->is_player())
	return 1;
	
	room = environment(meat);
	
	if(!room)
	return 0;
	
	meat_attacker=meat->query_attack();
	
	if(!meat_attacker || !present(meat_attacker, room) || meat_attacker == this_player())
	return 1;
	
	meat_hp=meat->query_hp();
	meat_mhp=meat->query_mhp();
	
	if(meat_mhp == 0)
	return 1;
	
	if(100*meat_hp/meat_mhp <= 15)
	{
		return 0;
	}
	return 1;
}

generic_wc_bonus(){
	
	int sstrike, evis;
	
	sstrike = (int)this_object()->query_sstrike();
	evis = (int)this_object()->query_evis();
	return (evis / 100 + (sstrike / random(20) > 45 ? 5 : 0));
}

heart_beat(){
	object ob, pob, rob, sob, kob;   /* ob is player, pob is party, rob is ranger, sob is shard, kob is knight*/
	object attacker, altattacker, att, *ob2; /* PREVENT SOMEONE FROM HITTING BEHIND THE ROGUE */
	int h, s;
	
       if(!environment()) return;
	ob = environment(this_object());
	
	   if(ob->query_ghost()){
		   return;
	   }
       
       if(!ob->query_pl_k() && !ob->query_ghost()){
	       ob->set_pl_k(1);
       }
	
	if(stealthed && !ob->query_invis())
	{
		ob->set_invs_sp();
	}
	
	if(!stealthed && ob->query_invis())
	{
		ob->unset_invs_sp();
	}
	
	pob = present("party_object", ob);
	
	if(pob){
		command("party leave", ob);
		tell_object(ob, "You are not allowed to party as a Rogue.\n");
	}
	
	rob = present("honor_ranger_communicator", ob);
	
	if(rob){
		command("rleave", ob);
		tell_object(ob, "You have no need for an alliance.\n");
	}
	
	sob = present("allymark", ob);
	
	if(sob){
		command("leave alliance", ob);
		tell_object(ob, "You have no need for an alliance.\n");
	}
	
	kob = present("KnightInvite", ob);
	
	if(kob){
		command("break_alliance", ob);
		tell_object(ob, "You have no need for an alliance.\n");
	}
	
	if(!ob->query_attack() && combo > 0){
		combo = 0;
		tell_object(ob, "C-C-C-C-C-C-C-C-COMBO BREAKER!!!\n");
	}
	
	if(ob->query_attack())
	{
		ob->unset_invs_sp();
		this_object()->set_stealthed(0);
	}
	
	if(ob->query_attrib("sta") > 25)
	{
		ob->set_attrib("sta", 25);
		tell_object(ob, "Your physical endurance weakens.\n");
	}
	
	if(ob->query_attrib("str") > 25)
	{
		ob->set_attrib("str", 25);
		tell_object(ob, "The shadows take away your extra strength.\n");
	}
	
	attacker = ob->query_attack();
	
	if(!attacker)
	{
		return;
	}
	
	if(attacker && !attacker->query_alt_attack())
	{
		return;
	}
	
	if(attacker && attacker->query_alt_attack())
	{
		altattacker = attacker->query_alt_attack();
		if(!altattacker->is_player())
		{
			return;
		}
		if(altattacker->is_player() && (altattacker->query_real_name() != ob->query_real_name()))
		{
			s = sizeof(ob2 = all_inventory(environment(ob)));
			
			while(h < s)
			{
				if(att = (object)ob2[h]->query_attack())
				{
					ob->stop_fight();
					attacker->stop_fight();
				}
				h++;
			}
			tell_object(ob, "You no longer care to fight.\n");
		}
	}
}

add_combo(int x){ combo += x; }
query_combo(){ return combo; }
set_combo(int x){ combo = x; }	
add_sstrike(int x){ sstrike += x; if(sstrike > 995) sstrike = 995; }
query_sstrike(){ return sstrike; }
set_sstrike(int x){ sstrike = x; }
add_evis(int x){ eviscerate += x;  if(eviscerate > 995) eviscerate = 995; }
query_evis(){ return eviscerate; }
set_evis(int x){ eviscerate += x; }
query_stealthed(){ return stealthed; }
set_stealthed(int x){ stealthed = x; }
query_sap(){ return sap; }
add_sap(int x){ sap += x; if(sap > 995) sap = 995; }
add_backstab(int x){ backstab += x; if(backstab > 995) backstab = 995; }
query_backstab() { return backstab; }
add_garrote(int x){ garrote += x; if(garrote > 995) garrote = 995; }
query_garrote() { return garrote; }
add_blind(int x){ blind += x; if(blind > 995) blind = 995; }
query_blind() { return blind; }
add_ambush(int x){ ambush += x; if(ambush > 995) ambush = 995; }
query_ambush() { return ambush; }
set_ambush(int x){ ambush = x; }

query_offwep(){ return offwep; }
set_offwep(ob) { offwep = ob; }
query_firstwep() { return firstwep; }
set_firstwep(ob) { firstwep = ob; }
remove_offwep() { offwep = 0; }
remove_firstwep() { firstwep = 0; }

query_combat_method() { return 3; }