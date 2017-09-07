
/*
 * PALADIN ADVANCEMENT AND TRAINING AREA (5/02/94)
 * This is where the Paladin advances levels, atrtibutes and skills
 */

#include "std_old.h"
#include "tune.h"

#define GEMOTE(x) write("Gurney "+x)
#define GSPEAK(x) write("Gurney says: "+x)
#define GWRITE(x) write("             "+x)

#define MCHAN(x) call_other("/players/sandman/paladin/powers",\
		 "master_channel",x)

#define GUILDMASTERS ({ "molasar", "sandman" })
#define COMMANDERS call_other("/players/sandman/paladin/powers",\
		   "query_commanders")

/* Minimum alignment required to advance */
#define MIN_ALIGN 0

/* define this to log joinings and departures */
#define LOG_MEMBERS

/* log advancements and attributes*/
#define LOG_ADVANCE

/* directory for log files */
#define LOGPATH "/players/sandman/paladin/log/"

/* Formats columns nicely */
justify(str, len) { return extract(str+"                      ",0,len-1); }

realm() { return "NT"; }

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

extra_reset(arg) {
   object board, paladin;
   if(arg)
     return;
   board = clone_object("players/sandman/paladin/palboard");
   move_object(board, this_object());
   paladin = clone_object("obj/monster");
   paladin->set_name("gurney");
   paladin->set_alias("paladin");
   paladin->set_short("Gurney, the Training Warden of Paladins");
   paladin->set_long("Gurney is a sturdy man in his mid forties.\n"+
	  "He is clad in practice armor and carries a large shield\n"+
	  "and sword. Gurney is in charge of training Paladins to ensure\n"+
	  "that they are at the peak of their capabilities.\n");
   paladin->set_level(40);
   paladin->set_hp(25000);
   paladin->set_wc(40);
   paladin->set_ac(20);
   paladin->set_al(1000);
   paladin->set_ep(100);
   move_object(paladin, this_object());
}

#undef EXTRA_INIT
#define EXTRA_INIT\
add_action("advance","advance");\
add_action("raise","raise");\
add_action("list_quests","list");\
add_action("cost_for_training","cost");\
add_action("train","train");\
add_action("maxtrain","maxtrain");\
add_action("practice","practice");\
add_action("maxpractice","maxpractice");\
if(this_player() && !this_player()->query_npc()) {\
  if(this_player()->query_level() < 20 &&\
     !restore_object("players/sandman/paladin/members/"+\
      this_player()->query_real_name())) {\
    write("Only Paladins and Wizards may access this room.\n");\
    move_object(this_player(), "/players/sandman/paladin/entry");\
    return 1;\
  }\
}

ONE_EXIT("players/sandman/paladin/hall1", "west",
   "The Paladin Advancement and Training Area",
   "You have entered the training and advancement room for Paladins.\n"+
   "The room is divided into three different areas. Near the northwest\n"+
   "corner is the weapons training area. Various types of weaponry lie\n"+
   "in racks along the wall for practice. In the opposite corner is the\n"+
   "combat training area. Practice dummys are hung from ceiling, clad in\n"+
   "various armors to emphasize the weak and strong points of attack.\n"+
   "The final area is the advancement area. There Paladins are tested in\n"+
   "their combat readiness and weapon proficiency to see if they are\n"+
   "worthy of the higher levels.\n"+
   "COMMANDS: advance, cost, practice, train, list (#)\n"+
   "          raise <str,sta,wil,mag,pie,ste,luc,int>\n", 1)

int next_level;
int next_exp;
int level;
int exp;
string title;         
object player_ob;

get_level(str) {
   level = str;
   next_exp   = get_next_exp(level);
   next_level = level + 1 ;   
   player_ob = this_player();
   title = get_new_title(level);
}    

string male_title_str, fem_title_str;

get_new_title(str,name,mod) {
   if(!male_title_str){
     male_title_str = allocate(20);
	
     male_title_str[19]      ="the apprentice Wizard";
     male_title_str[18]      ="the Supreme Paladin of Nirvana";
     male_title_str[17]      ="the Justiciar of Nirvana";
     male_title_str[16]      ="the Protector of the Order";
     male_title_str[15]      ="the Defender of the Realm";
     male_title_str[14]      ="the Warder of Justice";
     male_title_str[13]      ="the Guardian of the Scrolls";
     male_title_str[12]      ="the Warrior of the Third Order";
     male_title_str[11]      ="the Warrior of the Second Order";
     male_title_str[10]      ="the Warrior of the First Order";
     male_title_str[9]       ="the Initiate Warrior";
     male_title_str[8]       ="the Swordsman of the Third Order";
     male_title_str[7]       ="the Swordsman of the Second Order";
     male_title_str[6]       ="the Swordsman of the First Order";
     male_title_str[5]       ="the Initiate Swordsman";
     male_title_str[4]       ="the Squire";  
     male_title_str[3]       ="the Squire";  
     male_title_str[2]       ="the Squire";  
     male_title_str[1]       ="the Squire";  
     male_title_str[0]       ="the Squire";

     fem_title_str = allocate(20);

     fem_title_str[19]       ="the apprentice Wizard";
     fem_title_str[18]       ="the Supreme Paladin of Nirvana";
     fem_title_str[17]       ="the Justiciar of Nirvana";
     fem_title_str[16]       ="the Protector of the Order";
     fem_title_str[15]       ="the Defender of the Realm";
     fem_title_str[14]       ="the Warder of Justice";
     fem_title_str[13]       ="the Guardian of the Scrolls";
     fem_title_str[12]       ="the Warrioress of the Third Order";
     fem_title_str[11]       ="the Warrioress of the Second Order";
     fem_title_str[10]       ="the Warrioress of the First Order";
     fem_title_str[9]        ="the Initiate Warrioress";
     fem_title_str[8]        ="the Swordswoman of the Third Order";
     fem_title_str[7]        ="the Swordswoman of the Second Order";
     fem_title_str[6]        ="the Swordswoman of the First Order";
     fem_title_str[5]        ="the Initiate Swordswoman";
     fem_title_str[4]        ="the Squire"; 
     fem_title_str[3]        ="the Squire"; 
     fem_title_str[2]        ="the Squire"; 
     fem_title_str[1]        ="the Squire"; 
     fem_title_str[0]        ="the Squire"; 
   }
   if(!name)
     name = this_player()->query_real_name();
   if(member_array(name, GUILDMASTERS) != -1)
     return "the Guildmaster of Paladins";
   if(member_array(name, COMMANDERS) != -1)
     return call_other("/players/sandman/paladin/powers","query_ctitle");
   if(str >= 20)
     return "the Master Paladin of the Order of Gil-Estel";
   if(!player_ob || (player_ob->query_gender() == "creature") && (mod != 1))
     return male_title_str[str];
  else if((player_ob->query_gender() == "male") && (mod != 1))
     return male_title_str[str];
   else
     return fem_title_str[str];
}

int exp_str;

/*  returns the next_exp. */
get_next_exp(str) {
   if(!exp_str){
     exp_str = allocate(20);
	
     exp_str[19]  = 3750000;
     exp_str[18]  = 3000000; 
     exp_str[17]  = 2050659;
     exp_str[16]  = 1560042;
     exp_str[15]  = 1230042;
     exp_str[14]  =  930039;
     exp_str[13]  =  738441;
     exp_str[12]  =  443388;
     exp_str[11]  =  293387;
     exp_str[10]  =  202497;
     exp_str[9]   =  135000;
     exp_str[8]   =   89993;
     exp_str[7]   =   59990;
     exp_str[6]   =   39993;
     exp_str[5]   =   19218;
     exp_str[4]   =    8828;
     exp_str[3]   =    3498;
     exp_str[2]   =    2657;
     exp_str[1]   =    1521;
     exp_str[0]   =       0;
   }
   return exp_str[str];
}

advance() {
    string name_of_player;
    int cost;
    player_ob = this_player();
    
    if(!present("guild_medal", this_player())) {
      GSPEAK("I only promote Paladins! Be on your way!\n");
      return 1;
    }
    if(this_player()->query_alignment() < MIN_ALIGN) {
      GEMOTE("gives you a disgusted look.\n");
      GSPEAK("You are too evil to advance as a Paladin!\n");
      return 1;
    }
    name_of_player = player_ob->query_name();
    level = player_ob->query_level();
    if(level == -1)
      level = 0;
    exp = player_ob->query_exp();
    title = player_ob->query_title();
    if(level >= 20) {
      GSPEAK("I do not have the power to advance wizards!");
      return 1;
    }
    get_level(level);
    if(next_level == 20 && this_player()->query_quest_point() < NEEDED_QP) {
      GSPEAK("You have "+this_player()->query_quest_point()+" quest points"+
	    " and you need "+NEEDED_QP+" to become wizard.\n");
      return 1;
    }
    if(next_exp > exp) {
      GSPEAK("You don't have enough experience to be promoted.\n");
      return 1;
    }
    say("Gurney taps "+name_of_player+"'s shoulder with his sword.\n");
    player_ob->set_level(next_level);
    player_ob->set_title(title);
#ifdef LOG_ADVANCE    
    write_file(LOGPATH+"advance", capitalize(player_ob->query_real_name())+ 
       " advance to level "+next_level+" => "+ctime(time())+"\n");
#endif
    MCHAN(capitalize(this_player()->query_real_name())+" has advanced to "+
	  "level "+(level+1)+"!");
    if(next_level < 7) {
      GSPEAK("You are now "+name_of_player+" "+title+".\n");
      return 1;
    }
    if(next_level < 14) {
      GSPEAK("Well done, "+name_of_player+" "+title+".\n");
      return 1;
    }
    if(next_level < 20) {
      GSPEAK("You are now "+title+".\n");
      GWRITE("You are in the elite class of Paladins.\n");   
      GWRITE("Use your powers wisely, as few can oppose you now.\n");
    }
    if(next_level == 20) {
	GEMOTE("smiles at you in satisfaction.\n");
	GSPEAK("Congratulations Paladin! A new Wizard has been born.\n");
	shout("A sense of change sweeps across the Realm.\n");
	shout(capitalize(this_player()->query_real_name())+", the "+
	      title+", has attained the status of "+"Wizard!\n");
	GSPEAK("If you want a castle of your own, "+ 
	       "seek out Leo the archwizard, and ask him.\n");
	return 1;
    }
    return 1;
}

list_quests(num) {
   int qnumber;
   
   if(num == "all") {
     call_other("room/quest_room", "list_all");
     return 1;
   }
   if(num && (sscanf(num, "%d", qnumber) == 1))
     call_other("room/quest_room", "list", qnumber);
   else
     call_other("room/quest_room", "count", 0);
   return 1;
}

query_drop_castle() { return 1; }

correct_level(player) {
    level = call_other(player, "query_level", 0);
    exp = call_other(player, "query_exp", 0);
    /* Shouldn't "correct" wizards. */
    if (level >= 20)
	return;
    get_level(level);
    while(exp < next_exp) {
      level -= 1;
      get_level(level);
    }
    if(next_level == 20 && call_other("room/quest_room", "count", 0))
      get_level(18);
    call_other(player, "set_level", next_level);
    call_other(player, "set_title", title);
}

raise(str) {
    string attrib,raise,thing;
    int new,expcost,current,minexp;
    
    if(!present("guild_medal", this_player())) {
      GSPEAK("I only train Paladins.\n");
      return 1;
    }
    if(str !="str" && str !="sta" && str != "wil" && str != "mag" && 
       str !="pie" && str != "ste" && str != "luc" && str != "int") {
       GSPEAK("What attribute would you like to raise?\n");
       return 1;
    }
    if(this_player()->query_alignment() < MIN_ALIGN) {
      GEMOTE("gives you a disgusted look.\n");
      GSPEAK("You are too evil to advance as a Paladin!\n");
      return 1;
    }
    if(this_player()->query_level() > 19) {
      GSPEAK("I cannot advance the attributes of wizards.\n");
      return 1;
    }
    if(str == "str") attrib = "strength"; 
    if(str == "sta") attrib = "stamina"; 
    if(str == "wil") attrib = "will_power";
    if(str == "mag") attrib = "magic_aptitude";
    if(str == "pie") attrib = "piety";
    if(str == "ste") attrib = "stealth";
    if(str == "luc") attrib = "luck";
    if(str == "int") attrib = "intelligence";
    raise = "raise_"+attrib;
    current = this_player()->query_attrib(str);
    new = current+1;
    if(current < 12) expcost = -ATTRIB_COST;
    if(current < 16 && current > 11) expcost = -ATTRIB_COST_TWO;
    if(current < 20 && current > 15) expcost = -ATTRIB_COST_THREE;
    if(current > 19) {
      GSPEAK("I do not have the skill to increase your "+attrib+
	     " any higher.\n");
      return 1;
    }
    minexp = this_player()->query_exp() - 
		     get_next_exp(this_player()->query_level()-1);
    if(expcost < -minexp) {
      GSPEAK("You need more experience before I can increase your "+
	     attrib+".\n");
      return 1;
    }
#ifdef LOG_ADVANCE    
    write_file(LOGPATH+"attrib", this_player()->query_real_name()+
	 " raised "+attrib+" from "+current+" to "+new+"\n");
#endif    
    GEMOTE("runs you through a series of exercises designed to enhance\n"+
	   "and increase your "+attrib+".\n");
    call_other(this_player(), raise, 1);
    this_player()->add_exp(expcost);
    return 1;
}

#define MAX_PRO 20              /* maximum weapon proficiency */
#define MAX_MOD 20              /* maximum combat modifier */

/*
 * For raising combat modifiers
 */

train(str) {
   object guild;
   string what;
   int mod, lvl;
   int cost;

   guild = present("guild_medal", this_player());
   if(!guild) {
     GSPEAK("I can only train Paladins.\n");
     return 1;
   }
   if(!str || sscanf(str, "%s", what) != 1) {
     GSPEAK("I can help increase your combat efficiency.\n");
     GWRITE("Would you like me to train you in <mounted> combat, <shield>\n");
     GWRITE("and sword combat, or <dual> weapons combat?\n");
     return 1;
   }
   if(what != "dual" && what != "shield" && what != "mounted") {
     GSPEAK("I only know <mounted> combat, <shield> and sword combat,\n");
     GWRITE("and <dual> weapons combat.\n");
     return 1;
   }
   if(this_player()->query_alignment() < MIN_ALIGN) {
     GEMOTE("gives you a disgusted look.\n");
     GSPEAK("You are too evil to advance as a Paladin!\n");
     return 1;
   }
   lvl = this_player()->query_level(); 
   mod = guild->query_combat_mod(what);
   if(mod >= MAX_MOD) {
     GSPEAK("I do not have the skill to increase your "+what+
	    " combat anymore.\n");
     return 1;
   }
   if(mod >= (lvl + 4)) {
     GSPEAK("You must be of a higher level before I can train you.\n");
     return 1;
   }
   cost = get_cost("mod", mod);
   if(this_player()->query_money() < cost) {
     GSPEAK("You do not have enough money to cover the training fee of\n");
     GWRITE(cost+" gold pieces.\n");
     return 1;
   }
   this_player()->add_money(-cost);
   write("You pay the "+cost+" gp training fee.\n");
   guild->set_combat_mod(what, (mod+1));
   GEMOTE("run a series of exercises designed to enhance\n"+
	  "and increase your "+what+" combat ability.\n");
   write("Your "+what+" combat modifier is now "+(mod+1)+".\n");
#ifdef LOG_TRAINING     
   write_file(LOGPATH+"train", 
      capitalize(this_player()->query_real_name())+" advanced combat "+
      "modifier <"+what+"> to "+(mod+1)+" => "+ctime(time())+"\n");
#endif     
   guild->save_medal();
   return 1;
}

/*
 * For raising weapon proficiencies
 */

practice(str) {
   object guild;
   string what;
   int pro, lvl, cost;

   guild = present("guild_medal", this_player());
   if(!guild) {
     GSPEAK("I only train Paladins.\n");
     return 1;
   }
   if(!str || sscanf(str, "%s", what) != 1) {
     GSPEAK("I can help you practice with the recognized weapons of the\n");
     GWRITE("Paladins guild: the sword, lance, flail, mace, and axe.\n");
     return 1;
   }
   if(what != "sword" && what != "lance" && what != "flail" &&
      what != "mace" && what != "axe") {
     GSPEAK("I am unfamiliar with the "+what+" weapon. I only know the\n");
     GWRITE("following weapon types: sword, lance, flail, mace, and axe.\n");
     return 1;
   }
   if(this_player()->query_alignment() < MIN_ALIGN) {
     GEMOTE("gives you a disgusted look.\n");
     GSPEAK("You are too evil to advance as a Paladin!\n");
     return 1;
   }
   lvl = this_player()->query_level();
   pro = guild->query_weapon_pro(what);
   if(pro >= MAX_PRO) {
     GSPEAK("Your "+what+" weapon proficiency is at its maximum.\n");
     return 1;
   }
   if(pro >= (lvl + 4)) {
     GSPEAK("You must be of a higher level before you can practice more.\n");
     return 1;
   }
   cost = get_cost("pro", pro);
   if(this_player()->query_money() < cost) {
     GSPEAK("You do not have enough money to cover the training fee of\n");
     GWRITE(cost+" gold pieces.\n");
     return 1;
   }
   this_player()->add_money(-cost);
   write("You pay the.\n");
   guild->set_weapon_pro(what, (pro+1));
   GEMOTE("runs you through a series of exercises designed to enhance\n"+
	  "and increase your "+what+" weapon proficiency.\n");
   write("Your "+what+" weapon proficiency is now "+(pro+1)+".\n");
#ifdef LOG_TRAINING     
   write_file(LOGPATH+"train", 
      capitalize(this_player()->query_real_name())+" advanced weapon "+
      "proficiency <"+what+"> to "+(pro+1)+" => "+ctime(time())+"\n");
#endif     
   guild->save_medal();
   return 1;
}

cost_for_training() {
   int sword, flail, lance, mace, axe;
   int shield, dual, mounted;
   object guild;

   guild = present("guild_medal", this_player());
   if(!guild) {
     GSPEAK("I can only train Paladins!\n");
     return 1;
   }
   sword = guild->query_weapon_pro("sword");
   flail = guild->query_weapon_pro("flail");
   lance = guild->query_weapon_pro("lance");
   mace = guild->query_weapon_pro("mace");
   axe = guild->query_weapon_pro("axe");
   shield = guild->query_combat_mod("shield");
   dual = guild->query_combat_mod("dual");
   mounted = guild->query_combat_mod("mounted");
   write(justify("Proficiency",20)+justify("Cost (gp)",10));
     write(justify(" ",10));
     write(justify("Combat Method",25)+justify("Cost (gp)",10)+"\n"); 
   write(justify("===========",20)+justify("=========",10));
     write(justify(" ",10));
     write(justify("=============",25)+justify("=========",10)+"\n");  
   write(justify("Sword:",20)+justify(get_cost("pro",sword),10));
     write(justify(" ",10));
     write(justify("Shield & Sword:",25)+
			       justify(get_cost("mod",shield),10)+"\n");
   write(justify("Flail:",20)+justify(get_cost("pro",flail),10));
     write(justify(" ",10));
     write(justify("Dual Weapons:",25)+
				 justify(get_cost("mod",dual),10)+"\n");
   write(justify("Lance:",20)+justify(get_cost("pro",lance),10));
     write(justify(" ",10));
      write(justify("Mounted:",25)+justify(get_cost("mod",mounted),10)+"\n");
   write(justify("Mace:",20)+justify(get_cost("pro",mace),10)+"\n");
   write(justify("Axe:",20)+justify(get_cost("pro",axe),10)+"\n");
   return 1;
}

int cost_str;

get_cost(what, str) {
   if(!cost_str){
     cost_str = allocate(20);
	
     cost_str[19]  =    6675;
     cost_str[18]  =    6100;
     cost_str[17]  =    5550; 
     cost_str[16]  =    5025;
     cost_str[15]  =    4525;
     cost_str[14]  =    3950;
     cost_str[13]  =    3500;
     cost_str[12]  =    3075;
     cost_str[11]  =    2675;
     cost_str[10]  =    2300;
     cost_str[9]   =    1950;
     cost_str[8]   =    1625;
     cost_str[7]   =    1325;
     cost_str[6]   =    1050;
     cost_str[5]   =     825;
     cost_str[4]   =     625;
     cost_str[3]   =     450;
     cost_str[2]   =     300;
     cost_str[1]   =     175;
     cost_str[0]   =      75;
   }
   if(what == "pro" && str < MAX_PRO)  /* weapon proficiency */
     return cost_str[str]/5;  /* divide it by the number of weapon types */
   if(what == "mod" && str < MAX_PRO)
     return cost_str[str]/3;    /* divide it by the # of combat methods */
				/* do not include standard combat method */
   return "AT MAX";
}
