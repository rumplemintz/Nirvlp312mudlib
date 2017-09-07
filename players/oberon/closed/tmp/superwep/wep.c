#include "/ansi.h"
inherit "/obj/weapon.c";

#define pCHA (int)this_player()->query_attrib("cha")
#define pINT (int)this_player()->query_attrib("int")
#define pMAG (int)this_player()->query_attrib("mag")
#define pSTA (int)this_player()->query_attrib("sta")
#define pSTR (int)this_player()->query_attrib("str")
#define pDEX (int)this_player()->query_attrib("dex")
#define pLUC (int)this_player()->query_attrib("luc")
#define pPIE (int)this_player()->query_attrib("pie")
#define pSTE (int)this_player()->query_attrib("ste")
#define pWIL (int)this_player()->query_attrib("wil")
#define pALL pCHA+pINT+pMAG+pSTA+pSTR+pDEX+pLUC+pPIE+pSTE+pWIL
#define CHA_COST 1
#define INT_COST 1
#define MAG_COST 1
#define STA_COST 1
#define STR_COST 200
#define DEX_COST 50
#define LUC_COST 0
#define PIE_COST 1
#define STE_COST 1
#define WIL_COST 1

id(str) { if(str == "wep" || str == "weapon" || str == "super_weapon") return 1; }
short() { return "A Special Weapon"; }
long() { write("A VERY Special Weapon\n"); }

reset(arg) {
	::reset(arg);
	if (arg) return;
	set_hit_func(this_object());
	set_type("sword");
	set_class(7);
	set_weight(1);
	set_value(0);
	set_save_flag(0);
	set_hit_func(this_object());
}

query_hypermode() {
	return (pALL >= 300);
}

do_special() {
	do_cha();
	do_int();
	do_mag();
	do_sta();
	do_str();
	do_dex();
	do_luc();
	do_pie();
	do_ste();
	do_wil();
}

weapon_hit(attacker) {
	do_special();
	if(query_hypermode() && !random(10)) {
		write(HIR+"HYPER MODE!!!"+NORM+"\n");
		do_special();
	}
	return 0;
}

spellprice(object user, int price) {
	if(!user || !price) { return; }
	if(user->query_spell_point() > price) { user->add_spell_point(-price); }
	else { user->add_hit_point(-price); }
}


/*** CHA - Alignment Attack? ***/
do_cha() { return 0; }

/*** INT - Lowers Enemy AC ***/
do_int() { return 0; }

/*** MAG - Unassigned ***/
do_mag() { return 0; }

/*** STA - Lowers Enemy WC ***/
do_sta() { return 0; }

/*** STR - Extra Damage ***/
do_str() {
	object user, wep, enemy;
	user = environment(this_object());
	wep = this_object();
	enemy = user->query_attack();

	/* if(!enemy || random(2)) { return 0; } */
	if(!enemy || !(random(pSTR) > random(30))) { return 0; }
	
	tell_room(environment(user), HIR+user->query_name()+" slams into "+enemy->query_name()+" with all "+user->query_possessive()+" strength!"+NORM+"\n");
	enemy->hit_player(pSTR);
	spellprice(user, STR_COST);
	return 0;
}

/*** DEX - Extra Attack ***/
do_dex() {
	int dam, times;
	string message;
	object user, wep, enemy;
	user = environment(this_object());
	wep = this_object();
	enemy = user->query_attack();
	times = pDEX / 10;

	while(enemy && times--) {
		if(random(2)) { return 0; }
		dam = random(wep->query_class());
		message = wep->query_message_hit(dam);
		tell_room(environment(user), HIY+user->query_name()+" starts to vibrate quickly!"+NORM+"\n");
		tell_object(user, "You "+message[1]+" "+enemy->query_name()+""+message[0]+".\n");
		tell_object(enemy, user->query_name()+" "+message[1]+" you"+message[0]+".\n");
		tell_room(environment(user), user->query_name()+" "+message[1]+" "+enemy->query_name()+message[0]+".\n", ({user, enemy}));
		enemy->hit_player(dam);
		spellprice(user, DEX_COST);
	}
	return 0;
}

/*** LUC - Increase WC ***/
do_luc() {
	int wclass;
	object user, wep;
	user = environment(this_object());
	wep = this_object();
	wclass = wep->query_class();
	
	if(random(pLUC) == random(30)) {
		tell_room(environment(user), BLU+user->query_name()+" gets better with "+user->query_possessive()+" weapon."+NORM+"\n");
		wclass += 1;
		wep->set_class(wclass);
		spellprice(user, LUC_COST);
	}
	
	return 0;
}

/*** PIE - Unassigned ***/
do_pie() { return 0; }

/*** STE - Unassigned ***/
do_ste() { return 0; }

/*** WIL - Unassigned ***/
do_wil() { return 0; }


