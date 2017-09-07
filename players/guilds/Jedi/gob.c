/******************************************************************************
 * Program: gob.c - Jedi guild object
 * Path: /players/guilds/Jedi
 * Type: Object
 * Created: May 20th, 1999 by Dragnar/Maledicta
 *
 * Purpose: Main object for the Jedi guild
 * History:
 *          05/20/1999 - Dragnar
 *            Created
 *          09/12/2015 - Dragnar
 *            Moved code to /players/guilds and fixed includes etc.
 ******************************************************************************/
inherit "/players/guilds/Jedi/hall/object.c";

#include "defs.h"
#include <ansi.h>

#define MAX_COMBO 10

static mapping cmds;      /* aval. commands to the user */
static mapping spells;    /* aval. spells to the user */
static int saber_bonus; 
static int saber_bonus2; 

/** Saber **/
static int combo_no, combo_index, combo_status;
static string saber_attack;
static string *combo;
static object ComboAtt;
static object *Sabers;

/** Skills **/
mixed *skills;              /* skills user has gained: physical, saber, etc. */
static mapping skill_ranks; /* Details of skills, crush, speed, aid, etc. */ 
mixed *skill_ranks_a;       /* only used for storing in the guild file */

string *tasks;            /* Tasks done by jedi. */
string *secondary_masters;/* Other masters that are allowed BY THE
                             MASTER to train their apprentice. */

string my_master;         /* Who players master is */
string mon_color;         /* monitor color */
string wep_color;         /* Lightsaber color */

int cp;                   /* concentration points, run Jedi powers */
int mcp;
int skill_points;         /* Avail. points for skill training */
static int absorb;        /* gives a temporary ac, uses the paladin code */
static int rage;          /* Darkside anger */
static int mind_shield;   /* protect the player from force attacks */                                           
static int converge;      /* fight with force only, no weapons */
static int speed;         /* force speed */
static object meditate;
int council;              /* Is this player a council member */
int darkside;             /* Did this player fall to the darkside? */
int mon_on;                   /* is jedi monitor on? */
static int force_delay;   /* delay before able to cast another jedi power */
int goodness_pool;        /* are we light or dark?  if <= 0 then darkside */
int wep_life;             /* Length of life left in saber */
int saber_type;           /* Type of Saber */
object offwep;

static int damage,new_hp,old_hp, exps, old_exps;
static object carry_obj;
static string carry_obj_name;



id(string str) {
  object po;
  string *ids;

  ids = ({ name, alias_name, });
  ids += multipleIds;

  po = previous_object();
  if( po ) {
    if( (po->is_armor() && po->query_weight() > 2) || 
        po->query_type() == "shield") {
      ids += ({ "notarmor" });
    }
  }

  if( converge )
    ids += ({ "no_msg_hit" });
  
  if( meditate ) {
    if( darkside )
      ids += ({ "sp_regen_object" });
    else
      ids += ({ "hp_regen_object" });
  }
  return ( member_array(str, ids ) > -1 );
}

init() {
  int i;
  string clan;
  string *ks; 

  clan = (string) USER->query_clan_name();

  if( !clan ) {
    clan = JEDI_CLAN;
    USER->set_clan_name( clan );
    write("Clan Set.\n");
  }

  if( clan != JEDI_CLAN && clan != SITH_CLAN ) {
    write("You feel something wrong with your connection to the force...\n");
    return;  
  }


  SetMultipleIds( ({ "no_spell", "guild_death_object", "generic_wc_bonus", "gob", "GI", 
                     "dark_sight_object", "jedi_object", }) ); 

  if(environment() == this_player() && this_player()->is_player() ) {
    CHAN->add_channel( CHAN_NAME, environment() );
    ::init();

    if( !Sabers )
      Sabers = allocate( MAX_SABERS );

    add_action("no_who", "ppl");
    add_action("no_who", "Mwho");
    add_action("no_who", "who2");
    add_action("no_who", "s_who");
    add_action("no_wimpy","wimpy");
	
    /* Testing functions, to be removed before Beta test */
    add_action("jedirank", "glevel");
    add_action("wep_coloring", "colorwep");
    add_action("ls_life", "setlife");
    add_action("view_vars","vvars");
    add_action("set_skill_rank", "skillrank");
    /*************************************************/

    /** Commands **/
    if (cmds = ACTIONS->query_cmds()) {
      i = sizeof(ks = keys(cmds));
      while (i--) add_action("jedi_command", ks[i]);
    }
    else write_file(ERROR,ctime(time())+" cmds not set!\n");
    if( sizeof(ks) < 10) {
      write_file(ERROR,ctime(time())+" cmds is "+sizeof(ks)+" big!\n");
    }
    /** Spells **/
    if (spells = ACTIONS->query_spells()) {
      i = sizeof(ks = keys(spells));
      while (i--) add_action("jedi_spell", ks[i]);
    }
    else write_file(ERROR,ctime(time())+" spells not set!\n");
    if( sizeof(ks) < 10) {
      write_file(ERROR,ctime(time())+" spells is "+sizeof(ks)+" big!\n");
    }

  }
}

guild_login() {
  tell_object( USER, "Guild Login\n" );
  return;
}

reset(arg){
  int i;
  if(arg) return;
  set_mon_color("auto");
  set_goodness_pool(75);
  set_heart_beat(1);
  cp = 100;
  set_mcp(100);
  for( i=0; i < sizeof(multipleIds); i++ )
    write("{"+i+"} : "+multipleIds[i]+"\n");
}

remove_object() {
   CHAN->remove_channel( CHAN_NAME, environment() );
   destruct(this_object());
   return 1;
}

guild_death() {
  DEATH->jedi_death(USER);
  CHAN->transmit_message( CHAN_NAME, HIB+"\n\t\tYou feel a disturbance cause a ripple in the force.\n\n" );
}

 
jedi_command(string str) {
    string cmd;
	
    if (cmd = cmds[query_verb()])
	return (status) cmd->main( str, environment(), this_object() );
}

jedi_spell(string str) {
    string cmd;
	
    if (cmd = spells[query_verb()])
	return (status) cmd->main( str, environment(), this_object() );
}

save_stats() {
  string file;

  if(!USER) return 0;
  file = SAVE_PATH + environment()->query_real_name();
  if (!save_object(file)) {
     tell_object(USER, "Error in saving guild stats!\n");
     return 0;
  } 
  else {
    return 1;
  }
}

restore_stats() {
  if(!USER || !USER->is_player()) return 0;
  skills = allocate(8);

  if(!restore_object(SAVE_PATH + USER->query_real_name())) {
    skills = ({ "saber",0,"telekinesis",0,"physical",0,"telepathy",0,});
    skill_ranks_a = ({ });
    save_stats();
  }
  skill_ranks = reconstruct_mapping( skill_ranks_a );
  tell_object( USER, "Restoring Jedi Stats: "+USER->query_clan_name()+"\n");
  return 1;
}

get() { return 1; }
drop() { return 1; }
query_weight() { return 0; }
query_value() { return 0; }

Dodge() {
  if(damage > 0 && old_hp){
    switch(random(5)){
    case 1:
      tell_object(USER,
      "-+- ["+query_mon_color()+"You dodge right, narrowly missing being hit!"+NORM+"]\n");
    break;
    case 2:
      tell_object(USER,
      "-+- ["+query_mon_color()+"You jump back, dodging your attacker!"+NORM+"]\n");
      break;
    case 3:
      tell_object(USER,
      "-+- ["+query_mon_color()+"You flip into the air, flying over your opponents shoulder,\n"+
      "     causing "+USER->query_attack()->query_name()+" to fumble "+USER->query_attack()->query_possessive()+" attack!"+NORM+"]\n");
      break;
    case 4:
      tell_object(USER,
      "-+- ["+query_mon_color()+"You jump into a backspin, flying out of danger!"+NORM+"]\n");
      break;
    default:
      tell_object(USER,
      "-+- ["+query_mon_color()+"You dodge to your left, causing your attacker to fumble!"+NORM+"]\n");
      break;
        }
    USER->add_hit_point(damage);
    new_hp += damage;
    old_hp = new_hp;
  }
}

Reflect() {
  int new_damage;

  new_damage = damage;
  if(new_damage > 50) new_damage = 50;
  tell_object(USER,
    HIM+"-=- You feel the force flow through you "+USER->query_attack()->query_name()+"'s attack"+
    " is reflected back at them!"+NORM+"\n");
  USER->query_attack()->heal_self(-(random(new_damage/(15 - query_skill("reflect")))));
  USER->add_hit_point(damage);
  new_hp += damage;
  old_hp = new_hp;
}

heart_beat(){
  object Saber;
  int amt;

  if( !environment() ) {
    set_heart_beat(0);
    return;
  }


  /********* Guild exps bonus for a kill *********/
  if(!old_exps) old_exps = USER->query_exp();
  exps = USER->query_exp();
  if(exps - old_exps > 19) 
    USER->add_guild_exp((exps - old_exps)/5);
  old_exps = exps;

  /********* Set up for Dodge and Reflect info *********/
  if(!old_hp) old_hp = HP;
  new_hp = (int) USER->query_hp();
  damage = (old_hp - new_hp);
  if(damage < 0) damage = 0;
  if(USER->query_attack())
    old_hp = new_hp;

  /**************** Telekinesis Carry ****************/
  if(carry_obj) {
    if(!present(carry_obj,USER)) {
      carry_obj = 0;
      carry_obj_name = 0;
    }
    else {
      if(cp < 10) DropCarry();
      else cp -= random(3)+1;
    }
  }

  /**************** Lightsaber life adjusts ***************/
  Saber = present("jedi_saber",USER);
  if(Saber && Saber->query_ignited()) { 
    /** Dual blades will use more energy **/
    Saber->adj_wep_life(-1 * Saber->query_ignited() );
    if(Saber->query_wep_life() < 1) Saber->NoEnergy();
  }
  else if(USER->query_attack() && Saber && !converge) {
    command("ignite saber", USER);
    tell_object(USER, "You turn to face your enemy.\n");
  }
  else if(USER->query_attack() && !Saber && wep_life && !converge) {
    command("unlatch saber", USER);
	tell_object(USER, "The force flows through you.\n");
  }

  /* delay counter */ 
  if(force_delay){
	force_delay --;
	if(force_delay < 0) force_delay = 0;
  }

  /* absorb counter */
  if(absorb && USER->query_attack()){
	absorb --;
	if(absorb < 0) absorb = 0;
  }

  /* rage counter */
  if(rage) {
    rage--;
    if(rage < 0) 
      rage = 0;
    if( rage == 0 ) {
      tell_object(USER, BOLD + BLK +"Your "+HIR+"Anger "+BOLD + BLK +"finally burns itself out.\n" + NORM);
    }
  }

  /* speed counter */
  if( speed ) {
    speed--;
    if( speed < 0)
      speed = 0;
    if( speed == 0 ) {
      tell_object(USER, BOLD + "You lose control of your force speed and return to normal.\n" );
    }
  }
  
  /* converge check */
  if( USER->query_weapon() && converge ) {
    tell_object( USER, "You lose control of the force convergence in your body.\n");
    converge = 0;
  }

  if(!USER->query_attack() && cp < mcp &&   !USER->query_intoxination()) {
    if(random(100) < ((USER->query_guild_rank()*2)+5)){
      cp ++;
      if(cp > mcp) cp = mcp;
    }
  }

  if(USER->query_attack() && query_skill("telekinesis") > 2 && damage
    && random(100) < random(query_skill("telekinesis"))+1){
      Reflect();
  }

  /* Jedi dodge */
  if (USER->query_attack() && query_skill("physical") > 3 && damage &&
    random(100) < (random(query_skill("physical"))+1)) {
      Dodge();
  }

  if( USER->query_attack() && speed && random(15) < (random(query_skill("physical"))+1)) 

  {
    /*
    extra_attack = 1;
    command("jedi_extra_attack", USER);
    tell_object(USER, HIR+"\n\tYou counterattack!\n"+NORM);
    tell_room(environment(USER), HIR+USER->query_name()+" counterattacks!\n"+NORM,({ USER }));
    extra_attack = 0;
    */
    tell_object(USER, query_saber_color()+"\n\tThe force flows into you and you move with blurring speed!\n\n"+NORM);
    tell_room(environment(USER), "\t"+query_saber_color()+USER->query_name()+" moves with blinding speed!\n"+NORM,({ USER }));
    USER->toggle_already_fight(1);
    USER->attack(); 
  }

  if(USER->query_attack() && mon_on){
    command("mon", USER);
  }
  
  if(!darkside) {
    if(USER->query_money() > MAXCOINS){
  	  USER->add_money(-(USER->query_money() - MAXCOINS));
    }
  }
  
  if( meditate && USER && environment( USER ) ) {
    if( meditate != environment( USER) ||
        USER->query_attack() ||
        rage )
    {
      tell_object( USER, "You lose your concentration on the force surrounding you!\n" );
      meditate = 0;
    }
  }
#if 0
  if(meditate){
    amt = random(Rank)+1;
    if(USER->query_sp() > amt && (mcp - cp) > amt) {
      USER->add_spell_point(-amt);
      tell_object(USER, "amt: "+amt+".\n");
      adj_cp(amt);
    }
    else command("awaken",USER);
  }
#endif

 if(goodness_pool <= 0 && !darkside){
   DarksideFall();
 }
 
} /* heart_beat() */

/** Do extra attack from speed, rage etc. 
int jedi_extra_attack() {

  if(!extra_attack) {
    tell_object( environment(), "\t\tNO EXTRA ATTACK FOR YOU!\n" );
    return 1;
  }

  environment()->toggle_already_fight(1);
  environment()->attack();
  return 1;
}
*/

DropCarry() {

  if(!carry_obj)  
    return;

  tell_object(USER, "You lose your concentration on the "+carry_obj_name+".\n");
  tell_room(environment(USER), USER->query_name()+" loses "+USER->query_possessive()+" concentration and drops the "+carry_obj_name+".\n", ({USER,}));
  carry_obj->drop();
  move_object(carry_obj, environment(USER));
  carry_obj = 0;
  carry_obj_name = 0;
  return;
}

no_who(){
  if(this_player()->query_level() > 19) return 0;
  write("You do not have that command available any longer. Use 'who'.\n");
  return 1;
}
			
no_wimpy() {
  if(darkside) {
    write("Your bond with the Force keeps you from running.\n");
    return 1;
  }
  return 0;
}

/* Test functions, to be removed before Beta testing */
wep_coloring(string str){
	wep_color = str;
	tell_object(USER, "Wep set to : "+wep_color+".\n");
	save_stats();
	return 1;
}

ls_life(str){
  int i;

  sscanf(str, "%d", i);
	wep_life = i;
  save_stats();
  return 1;
}

view_vars(){
  int i;
  string *myskills;

  write("Rage:        "+rage+"\n");
  write("Darkside:    "+darkside+"\n");
  write("Force Delay: "+force_delay+"\n");
  write("Light Pool:  "+goodness_pool+"\n");
  write("Mind:        "+mind_shield+"\n");
  write("Absorb:      "+absorb+"\n");
  write("Converge:    "+converge+"\n");
  write("Speed:       "+speed+"\n");
  write("Meditate:    "+(meditate ? meditate->short() : 0)+"\n");
  write("Skill Ranks:\n");
  myskills = m_indices( skill_ranks );
  for( i=0; i < sizeof(myskills); i++ ) {
    write( "\t" + myskills[i] + ": " +skill_ranks[ myskills[i] ][0]+ " : "+ 
           skill_ranks[ myskills[i] ][1]+"\n");
  }
  write("speed: " + query_skill_rank("speed","rank") + "\n");
  write("crush: " + query_skill_rank("crush","exp") + "\n");
  return 1;
}

jedirank(str) {
    int amount;
    int target;

   amount = USER->query_guild_rank();
   sscanf(str, "%d", target);
   USER->add_guild_rank(-amount);
   USER->add_guild_rank(target);
   write("Your guild rank is now: "+target+".\n");
   save_stats();
   return 1;
}

set_skill_rank( string str ) {
  int amt;
  string sname, attr;

  sscanf( str, "%s %s %d", sname, attr, amt);
  write( "Skill: "+sname+" Attribute: "+attr+" Amount: "+amt+"\n");
  add_skill_rank( sname, attr, amt );  
  return 1;
}

/*****************************************************************
 * Saber Functions
 *****************************************************************/

void ResetCombo() {
        tell_object(USER, "\tATTACKER CHANGED!!\n");
  combo = ({ "null","null","null","null","null","null","null","null","null","null", });
  combo_no = 0;
  combo_index = 0;
}

int gen_wc_bonus() {
  int ignited;
  int bonus;
  int i,j;
  object target;

  if( !Sabers[SABER1] && !Sabers[SABER2] ) {
    write("No wc bonus.\n");
    return 0;
  }
     
  target = (object) USER->query_attack();

  /* We have an ignited saber */
  if( Sabers[SABER1] && Sabers[SABER1]->query_ignited() && USER->query_spell_dam() ) {
    if( ComboAtt && ComboAtt != target )
      ResetCombo();
    if( target )
      ComboAtt = target;

    /** Penalty for Intox **/
    if( USER->query_sp() < 0 || USER->query_intoxination() )
      saber_bonus = -100;

    /** Penalty for low SP **/
    if( USER->query_sp() < 0 && USER->is_player() ) {
      tell_object(USER, "Your lack of connection to the force causes you to strike yourself with your Lightsaber.\n"); 
      USER->hit_player( random(50), "other|energy" );
      return saber_bonus;
    }


    bonus = saber_bonus;

    if( rage )
      bonus += 10; /*query_skill( SABER );*/

    saber_bonus = 0;
  }
  else {
    write("NO ATTACK DONE.\n");
    bonus = -10;
    saber_attack = 0;
    if(combo) {
      /* No attack was done, so go to the oldest attack and null it out */
      if(combo_status == 1) {
        i = combo_index;
        j = 1;
        while(j < 11 && combo[i] == "null") {
          if(i == 9) i = 0;
          else i++;
          j++;
        }

        if(j > 10) 
          combo_status = 0;
        else 
          combo[i] = "null";
      }
    }
  }


/*
    extra_attack = 1;
    command("jedi_extra_attack", USER);
    tell_object(USER, HIR+"\n\tYou counterattack!\n"+NORM);
    tell_room(environment(USER), HIR+USER->query_name()+" counterattacks!\n"+NORM,({ USER }));
    extra_attack = 0;
*/

  write("wc_bonus: "+bonus+"\n");
  saber_bonus2 = bonus;
  return bonus;
}

jedi_extra_hit( object atk ) {
  int bonus;
  bonus = saber_bonus2;
  saber_bonus2 = 0;
  write("wc_bonus2: "+bonus+"\n");
  return bonus;
}

query_message_hit( int dam ) {
  object Saber;
  
  Saber = present("jedi_saber",USER);
  if( Saber )
    return Saber->query_message_hit( dam );
  
  return 0;
}

int set_combo(string str) {
  int i;
  string ComboStr;

  /* This is not ideal, but faster than constantly resizing the array */
  combo_status = 1;
  if(!combo) {
    combo = ({ "null","null","null","null","null","null","null","null","null","null", });
    combo_index = 0;
  }
  combo[combo_index] = str;
  combo_index++;   /* point to the next index where we will insert */
  /* If we at at index 10, we need to start at the beginning again */
  if(combo_index > 9) combo_index = 0;

  for(i=0, combo_no=0; i < MAX_COMBO; i++)
  {
        if(combo[i] == str) combo_no++;
        /************ FOR TESTING ONLY ***************/
        if(i == 0) ComboStr = combo[i];
        else ComboStr += ":" + combo[i];
        /*********************************************/
  }

  tell_object(USER, HIR+"combos: "+ComboStr+"\n"+NORM);
  if(combo_no > 2) 
    return combo_no - 2;
  else return 0;
}

query_hp_regen(){
  return (meditate ? ( query_skill_rank("meditate", "rank")+ query_skill( PHYS ) ) : 0);
}

query_sp_regen(){
  int val;
  if( meditate && USER->query_sp() != USER->query_msp() && !USER->checkNM() ) {
    val = query_skill_rank("meditate", "rank") * query_skill( PHYS );
    tell_object(USER, "Adding "+ val+" meditate exp.\n");
    add_skill_rank( "meditate", "exp", val ); 
  }
  else
    val = 0;
  return val;
}

/*****************************************************************
 * Guild sets, queries, and adjusts
 *****************************************************************/
query_spells() { return (spells ? m_indices(spells) : 0); }
query_commands() { return (cmds ? m_indices(cmds) : 0); }

set_carry_obj(object ob) { carry_obj = ob; }
object query_carry_obj() { return carry_obj; }
set_carry_obj_name(string str) { carry_obj_name = str; }

set_force_delay(int x){ force_delay = x; }
query_force_delay(){ return force_delay; }
adj_force_delay(int x){ force_delay += x; }

set_mind_shield(int x){ mind_shield = x; }     
query_mind_shield(){ return mind_shield; }     
adj_mind_shield(int x){ mind_shield += x; }

set_goodness_pool(int x){ goodness_pool = x; }
query_goodness_pool(){ return goodness_pool; }
adj_goodness_pool(int x){ goodness_pool += x; }

set_absorb(int x){ absorb = x; }
query_absorb(){ return absorb; }

set_rage(int x){ rage = x; }
query_rage(){ return rage; }

set_converge(int x) { 
  if( !x )
    converge = 0;
  converge = x; 
}
query_converge() { return converge; }

set_meditate(int x) { 
  if( !x )
    meditate = 0;
  else
    meditate = environment( USER );
}
query_meditate() { return meditate; }

set_speed(int x) {
  if( !x )
    speed = 0;
  else
    speed = x; 
}
query_speed() { return speed; }

set_mcp(int x){ mcp = x; }
query_mcp(){ return mcp; }
adj_mcp(int x){ mcp += x; }

set_saber_type(int x) { saber_type = x; }
query_saber_type() { return saber_type; }

set_cp(int x){ cp = x; }
query_cp(){ return cp; }
adj_cp(int x) {
    if(x < 0 && carry_obj && !random(query_skill("telekinesis"))) DropCarry();
  cp += x;
}

set_mon_on(int x) { mon_on = x; }
query_mon_on(){ return mon_on;}

set_skill_points(int x){ skill_points = x; }
query_skill_points(){ return skill_points; }
adj_skill_points(int x){ skill_points += x; }

set_wep_life(int x){ wep_life = x; }
query_wep_life(){ return wep_life; }
adj_wep_life(int x){ wep_life += x; }

set_mon_color(string str){ mon_color = str; }
query_mon_color() {
  int x;
  string temp;

if( mon_color == "auto" ) {
    x = ((USER->query_hp() * 100) / (USER->query_mhp()));
    switch(x) {
    case 80..100:
      temp = HIG;
      break;
    case 60..79:
      temp = HIB;
      break;
    case 40..59:
      temp = HIY;
      break;
    case 0..39:
      temp = HIR;
      break;
    default:
      temp = HIM;
      break;
  }
}
  else temp = mon_color;
  return temp;
}

set_wep_color(string x) { wep_color = x; }
query_wep_color_ansi(){ return LEV->QueryColor( wep_color ); }
query_wep_color(){ return wep_color; }

query_saber_color() {
  if( Sabers[SABER1] ) {
    return Sabers[SABER1]->query_wep_color();
  }
  else return LEV->QueryColor( wep_color );
}

query_combat_method(){ return 2; }
query_paladin_shield(){ return 1; }

set_my_master(string s) { return my_master = (s) ? s : "none"; }
query_my_master(){ return my_master; }

set_secondary_masters(string s) { secondary_masters += s; }
query_secondary_masters() { return secondary_masters; }

set_council(int x){ council = x; }
query_council(){ return council; }

set_darkside(int x){ darkside = x; }
query_darkside(){ return darkside; }

/** skills **/
set_skill(string str, int lev) {
  skills += ({ str, lev, });
}
adj_skill(string str, int lev) {
  int index;

  if( member( SKILL_TYPES, str ) < 0 )
    return 0;

  if(!skills)  skills = ({ SABER, 0, KIN, 0, PHYS,0, TELE,0, });

  index = member( skills, str );
  if(index < 0) {
    set_skill(str, lev);
    return;
  }
  skills[index+1] += lev;
  return;
}
int query_skill(string str) {
  int index;
  
  index = member_array(str, skills);
  if(index < 0) return 0;
  else return skills[index+1];
}

/** skill ranks **/
int
add_skill_rank( string sname, string attr, int amt ) {
  int idx;

  if( !sname || !skill_ranks )
    return 0;

  if( !amt )
    amt = 1;

  /** add entry **/
  if( !skill_ranks[ sname ] ) {
    skill_ranks += ([ sname : DEFAULT_SKILL_RANK ]);
  }
  else {
    /** update skill rank **/
    idx = member( SKILL_RANK_ATTR, attr );
    if( idx < 0 )
      return 0;
    skill_ranks[ sname ][idx] += amt;
    if( attr == "rank" ) {
      skill_ranks[ sname ][EXP_IDX] = 0;
    }
      
  } 
  /** Update array so it will save in LP **/
  skill_ranks_a = deconstruct_mapping( skill_ranks );
  save_stats();
}

string *
query_skill_ranks() {
  return m_indices( skill_ranks );
}

mixed
query_skill_rank( string sname, string attr ) {
  int idx;

  if( !sname || !attr || !skill_ranks[ sname ]  )
    return 0;

  attr = lower_case( attr );

  idx = member( SKILL_RANK_ATTR, attr );
  
  if( idx < 0 )
    return 0;

  return skill_ranks[sname][idx]; 
}

set_offwep(ob) { offwep = ob; }
query_offwep() { return offwep; }
remove_offwep(){ offwep = 0; }

set_saber_bonus(int x) { saber_bonus = x; }
query_saber_bonus() { return saber_bonus; }

SetSaber( int i, object ob ) { 
  Sabers[i] = ob; 
}
QuerySaber( int i ) { 
  if( i >= SABER1 && i < MAX_SABERS )
    return Sabers[i]; 
  else
    return 0;
}

query_saber_attack() { return saber_attack; }
set_saber_attack( string str ) { saber_attack = str; }