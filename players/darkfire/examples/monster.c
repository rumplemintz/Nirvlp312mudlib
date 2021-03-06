/*
 * A general purpose monster. Clone this object,
 * and call local functions to configure it.
 */
#include "living.h"
#include "clean.c"
#include "chat_include.c"
#include "catch_talk_include.c"
#define EMOTER(a,b,c) (string)call_other("/obj/user/parse_emote","parse_emote",a,b,c)
#define ANSI(x) (string)call_other("/obj/monitor","replace_ansi",x)
#define NONPHYS 30000/20000


/*
 * The heart beat is always started in living.h when we are attacked.
 */

string short_desc, long_desc, alias, alt_name, race, hbflag,info;
int move_at_reset, aggressive, can_kill;
object kill_ob;
string *message_hit;
int my_tot_wc, my_tot_ac;
object desc_ob;


int heal_start;
int heal_rate;
int heal_intv;
/** Moving autoheal from call_out to heart_beat **/
int autoheal_count;
int chat_chance;
/* Duplicates from included file that ld don't like -Bp 
int chat_nr;
int a_chat_nr;
*/

int a_chat_chance;

string the_text;
int have_text;

/* pavlik: begin wander addition */
int wander;			/* whether we wander or not */
int wander_interval;		/* how often we move */
int wander_count;		/* count heartbeats until next wander */
string wander_realm;		/* base file path we are allowed to wander */
/* pavlik: end wander addition */

object dead_ob;
object init_ob;

int random_pick;

int spell_chance, spell_dam_mon;
string spell_mess1, spell_mess2;
object me;
static int give_count;

string spell_type;

static int res, pac, pwc;

static string armor_special, weapon_special;

mixed *armor_params;
mixed *weapon_params;

mixed *spells;
static status readied;
status multi_cast;
int saved_hr, saved_hi;
int saved_wc, saved_ac;

/* suggested/inspired by forbin.  added by illarion 5 dec 2004 */
string corpse_short,corpse_long,corpse_name;
string death_emote;

/* [2006.06.30] Forbin -implemeted multiple ids */
string *multipleIds;

int wimpy_health;
int wimpy_chance;
string wimpy_exit;
string wimpy_msg;

int luck;


set_desc_ob(ob) { desc_ob = ob; }

valid_attack(ob)
{
    /* Don't attack other monsters unless specifically allowed to. */
    return (!call_other(ob, "query_npc", 0) || can_kill);
}

reset(arg)
{
  if(arg)
  {
	/* pavlik: begin wander addition */
	if(set_heart_beat(0))
		/* heart_beat was on and we just turned it off */
		/* turn heart_beat back on */
		set_heart_beat(1);
	else
	{
		/* heart beat was already off, leave it off and wander */
		if(wander) wander();
	}
	/* pavlik: end wander addition */

	if(move_at_reset)
		random_move();
	return;
  }
  is_npc = 1;
  /* Only let this monster kill other monsters if specifically allowed. */
  can_kill = 0;
  enable_commands();
  if(!pac && !pwc) {
  }
  me = this_object();
  message_hit=({
	"massacre"," to small fragments",
	"smashed"," with a bone crushing sound",
	"hit"," very hard",
	"hit"," hard",
	"hit","",
	"grazed","",
	"tickled"," in the stomach"
  });
  if (luck2) luck = luck2;
}

random_move()
{
  int n;
  n = random(7);   /* Changed from 4 to 7 to allow ne,nw,se,sw - Rumplemintz */
/*
  if (n == 0)
	command("west");
  else if (n == 1)
	command("east");
  else if (n == 2)
	command("south");
  else if (n == 3)
	command("north");
*/
  switch(n) {     /* Changed from if/else to switch - Rumplemintz */
    case 1: command("west"); break;
    case 2: command("east"); break;
    case 3: command("south"); break;
    case 4: command("north"); break;
    case 5: command("northeast"); break;
    case 6: command("northwest"); break;
    case 7: command("southeast"); break;
    default: command("southwest"); break;
  }
}

short() {
    object ob;
    string temp_short;

    if(desc_ob) short_desc = (string)desc_ob->monster_short();
    if (attacker_ob)
      temp_short = short_desc + " (Fighting "+(attacker_ob == this_player() ? "YOU!" : (string)attacker_ob->query_name())+")";
    else temp_short = short_desc;
    if(this_player() && (ob=present("sight_short_modifier", this_player())))
    {
      return (string)ob->modify_short(temp_short);
    }
    return temp_short;
}

/*
long() {
    if (desc_ob) {
        call_other(desc_ob,"monster_long",0);
  return;
    }
    write (long_desc);
}
*/

long() {
    if (desc_ob) {
        call_other(desc_ob,"monster_long",0);
  return;
    }
if (gender)
    write(short_desc + " ("+gender+")\n");
    write (query_long());
    if(hit_point < max_hp/10) {
      write(cap_name+" is in very bad shape.\n");
      return;
    }
    if(hit_point < max_hp/5) {
      write(cap_name+" is in bad shape.\n");
      return;
    }
    if(hit_point < max_hp/2) {
      write(cap_name+" is somewhat hurt.\n");
      return;
    }
    if(hit_point < max_hp - 20) {
      write(cap_name+" is slightly hurt.\n");
      return;
    }
    write(cap_name+" is in good shape.\n");
}
id(str) {
    /* 07/12/06 Earwax: this is hosing somehow, adding these checks */
    if (!str) return 0; 
    if (objectp(desc_ob) && desc_ob != this_object())
      return desc_ob->monster_id(str);
    /* [2005.06.30] Forbin -modified to support multiple ids */
#if 0 /* Adding a default id for all monsters that use this -- Rumplemintz */
    if(!multipleIds) multipleIds = ({ });
#else
    if (!multipleIds) multipleIds = ({"npc"});
#endif

    return str == alt_name || str == name || str == alias || 
           str == race || member_array(str, multipleIds) > -1;
}

heart_beat()
{
    int c;

    if(!this_object()) return;

    dam_taken_this_round=0;
    age += 1;

#if 0
    if(!heal_start && hit_point < max_hp)
    {
	call_out("autoheal_monster", heal_intv);
	heal_start = 1;
    }
#endif
#if 1
    if( heal_rate && hit_point < max_hp )
    {
        autoheal_count++;
        if( autoheal_count >= heal_intv ) {
            autoheal_monster();
            autoheal_count = 0;
        }
    }
#endif

    /* pavlik: begin wander addition */
    if(wander)
    {
	wander_count++;
	if(wander_count >= wander_interval)
	{
		wander();
		wander_count = 0;
	}
    }
    else
    {
	wander_count = 0;
    }
    /* pavlik: end wander addition */

    already_fight = 0;

    /* If there is none here test_if_any_here will turn of heat_beat */
    if(!test_if_any_here())
    {
	if(have_text && talk_done)
	{
		have_text = 0;
		test_match(the_text);
	}
	/* pavlik: begin wander addition */
	/* the below addition allows us to wander one more time before */
	/* shutting off the heart_beat */
	else if(wander == 1)
	{
		if(wander_count <= 0)
		{
			set_heart_beat(0);
			return;
		}
	}
	/* pavlk: end */
	else
	{
          /* Only turn off HB if no healing required */
          if( !heal_rate || hit_point >= max_hp ) {
	    set_heart_beat(0);
	    return;
          }
	}
    }

    if (kill_ob && present(kill_ob, environment(this_object()))) {
  if (random(2) == 1)
      return;   /* Delay attack some */
  attack_object(kill_ob);
  kill_ob = 0;
  return;
    }

  if(attacker_ob && (wimpy_health >= query_hp()*100/query_mhp()) && 
    present(attacker_ob, environment()) &&
      wimpy_chance >= random(100))
  {
    this_object()->wimpy_out();
    return;
  }

  if (attacker_ob && present(attacker_ob, environment(this_object())) &&
      spell_chance > random(100)) 
  {
    /** Gnar 09/01/2015 added checks the spell messages are set **/
    if( spell_mess1 )
      say(spell_mess1 + "\n", attacker_ob);
    if( spell_mess2 )
      tell_object(attacker_ob, spell_mess2 + "\n");
    attacker_ob->hit_player(random(spell_dam_mon), spell_type);
  }
   attack();
/*
   if(alt_attacker_ob)
  if(!alt_attacker_ob->query_name()) alt_attacker_ob = attacker_ob;
  if(alt_attacker_ob && alt_attacker_ob != attacker_ob){
     if(present(alt_attacker_ob))
   hit_pet(weapon_class,spell_dam_mon);
   }
*/
    if (attacker_ob && whimpy && hit_point < max_hp/5)
       if(random(100)<41)  /*make monsters less annoying*/
  this_object()->wimpy_out();
    if(chat_nr > 0 || a_chat_nr > 0) {
  c = random(100);
  if(attacker_ob && a_chat_nr > 0) {
      if(c < a_chat_chance){
    c = random(a_chat_nr);
                a_chat(c);
      }
  } else {
      if(c < chat_chance && chat_nr > 0){
    c = random(chat_nr);
                chat(c);
      }
  }
    }
    if(random_pick) {
  c = random(100);
  if(c < random_pick)
      pick_any_obj();
    }
    if(have_text && talk_done) {
  have_text = 0;
        test_match(the_text);
    }
}

can_put_and_get(str)
{
    if (!str)
  return 0;
    return 1;
}

int busy_catch_tell;

catch_tell(str) {
    string who;

    if (busy_catch_tell)    /* Should not happen, but does! */
  return;
    busy_catch_tell = 1;
    if(talk_done) {
  if(have_text) {
      who = the_text;
      the_text = str;
      have_text = 1;
            test_match(the_text);
  } else {
      the_text = str;
      have_text = 1;
  }
    }
    busy_catch_tell = 0;
}

/*
 * Call the following functions to setup the monster.
 * Call them in the order they appear.
 */

set_name(n) {
    name = n;
    set_living_name(n);
    cap_name = capitalize(n);
    if(!short_desc)
      short_desc = cap_name;
    if(!long_desc)
      long_desc = "You see nothing special.\n";
/*    move_object(clone_object("obj/soul"), this_object()); */
/* why is this here?? */
    if(!message_hit) 
    message_hit=({"massacre"," to small fragments","smashed"," with a bone crushing sound","hit"," very hard","hit"," hard","hit","","grazed","","tickled"," in the stomach"});
}

/* Optional */
set_alias(a) { alias = a; }
query_alias() { return alias; }
/* Optional */
set_race(r) { race = r; }
/* optional */
set_hp(hp) { max_hp = hp; hit_point = hp; }
/* optional */
set_ep(ep) { experience = ep; }
/* optional */
set_al(al) {
    /* Limit alignment to keep wizards from making their monsters worth
       much too much */
    if (al > 1000)
  al = 1000;
    if (al < -1000)
  al = -1000;
    alignment = al;
}
/* optional */
set_short(sh) { 
  short_desc = sh;
  if(!long_desc)
    long_desc = short_desc + "\n";
}
/* optional */
set_long(lo) { long_desc = lo; }
/* optional */

set_wc(wc) {
  if(!saved_wc) {
    saved_wc = wc;
    my_tot_wc = wc;
  }
  else {
    if(wc > my_tot_wc) my_tot_wc = wc;
  }
  pwc=wc;
  weapon_class=wc;
  set_weapon_params("physical", pwc, weapon_special);
}

set_weapon_special(special2){ weapon_special = special2; set_weapon_params("physical",pwc, weapon_special); }
/* optional */
set_ac(ac)
{
  if(!saved_ac) {
    saved_ac = ac;
    my_tot_ac = ac;
  }
  else {
    if(ac > my_tot_ac) my_tot_ac = ac;
  }
  pac=ac;
  armor_class=ac;
  set_armor_params("physical", pac, res, armor_special);
}
set_res(res1)
{
  res=res1;
  set_armor_params("physical",pac,res,armor_special);
}

set_armor_special(special1) { armor_special = special1; set_armor_params("physical",pac,res,armor_special);  }

/* pre-dtypes
set_wc(wc) { weapon_class = wc; }
set_ac(ac) { armor_class = ac; }
*/
/* optional */
set_move_at_reset() { move_at_reset = 1; }
/* optional
 * 0: Peaceful.
 * 1: Attack on sight.
 */
set_aggressive(a) {
    aggressive = a;
}
/* optional
 * 0: Can't attack other monsters.
 * 1: Can attack other monsters.
 */
set_can_kill(a) {
    can_kill = a;
}
/*
 * Now some functions for setting up spells !
 */
/*
 * The percent chance of casting a spell.
 */
set_chance(c) {
    spell_chance = c;
}
/* Message to the victim. */
set_spell_mess1(m) {
    spell_mess1 = m;
}
set_spell_mess2(m) {
    spell_mess2 = m;
}
set_spell_dam(d) {
    spell_dam_mon = d;
}

/* Set the frog curse. */
set_frog() {
    frog = 1;
}

/* Set the whimpy mode */
set_whimpy() {
    whimpy = 1;
}

/*
 * Force the monster to do a command. The force_us() function isn't
 * always good, because it checks the level of the caller, and this function
 * can be called by a room.
 */
init_command(cmd) {
    command(cmd);
}

/* Load chat */

set_chat_chance(c) {
    chat_chance = c;
}

/* Load attack chat */

set_a_chat_chance(c) {
    a_chat_chance = c;
}

set_dead_ob(ob)
{
    dead_ob = ob;
}

second_life()
{
  if(dead_ob)
    call_other(dead_ob,"monster_died",this_object());
}

set_random_pick(r)
{
    random_pick = r;
}

pick_any_obj() {
    object ob;
    int weight;

   if(!environment()) return;  /* verte */
    ob = first_inventory(environment(this_object()));
    while(ob) {
  if (call_other(ob, "get", 0) && call_other(ob, "short")) {
      weight = call_other(ob, "query_weight", 0);
      if (!add_weight(weight)) {
    say(cap_name + " tries to take " + call_other(ob, "short", 0) +
        " but fails.\n");
    return;
      }
      move_object(ob, this_object());
      say(cap_name + " takes " + call_other(ob, "short", 0) + ".\n");
      if (call_other(ob, "weapon_class", 0))
    call_other(ob, "wield", call_other(ob,"query_name"));
      else if (call_other(ob, "armor_class", 0))
    call_other(ob, "wear", call_other(ob,"query_name"));
      return;
  }
  ob = next_inventory(ob);
    }
}

dumpa(str)
{
    string foo;
    if (sscanf(str, "players/%s", foo)) return 0;
    if(!str)
  str = "MONSTER_DUMP";
    save_object(str);
}

set_init_ob(ob)
{
    init_ob = ob;
}


init() {
  int ste,atc;

    if(this_player() == me)
  return;
    if(dead_ob)
  if(call_other(dead_ob,"monster_init",this_object()))
      return;
    if (attacker_ob) {
  set_heart_beat(1); /* Turn on heart beat */
    }
    if(this_player() && !call_other(this_player(),"query_npc")) {
  set_heart_beat(1);
  if (aggressive == 1)
    {
     atc = random(50);
     ste = call_other(this_player(), "query_attrib", "ste");
     if (ste < atc)
      kill_ob = this_player();
   }
    }
  ready_eq();
}

set_info(str) { info = str; }
set_hbflag(str) {hbflag = str; }
query_hbflag() {return hbflag;}
query_info() {return info; }
autoheal_monster() {
  /* Prevent Heal Code added by Illarion -2014.02.16 */
  if(!present("prevent_monster_heal")) 
  {
     if (hit_point < max_hp) {
        hit_point += heal_rate;
     }
        if (hit_point > max_hp)
               hit_point = max_hp;
  }
#if 0
  if(hit_point < max_hp)
   call_out("autoheal_monster", heal_intv);
   if(hit_point == max_hp) heal_start = 0;
#endif
}
set_heal(hr, hi){
    if(hr < 0) return;
    if(hi < 0) return;
  if(!saved_hr) saved_hr=hr;
  if(!saved_hi) saved_hi=hi;
    heal_rate = hr;
     heal_intv = hi;
    }
set_alt_name(n) { alt_name = n; }
set_gender(str) { gender = str;}
query_aggressive() { return aggressive;}
query_race() {return race;}
set_message_hit(arr) {
   message_hit=arr;
}
query_message_hit(tmp) {
  string *mess;
    mess = ({message_hit[1],message_hit[0]});
  if (tmp < 30) {
    mess = ({message_hit[3],message_hit[2]});
  }
  if (tmp < 20) {
    mess = ({message_hit[5],message_hit[4]});
  }
  if (tmp < 10) {
    mess = ({message_hit[7],message_hit[6]});
  }
  if (tmp < 5) {
    mess = ({message_hit[9],message_hit[8]});
  }
  if (tmp < 3) {
    mess = ({message_hit[11],message_hit[10]});
  }
  if (tmp == 1) {
    mess = ({message_hit[13],message_hit[12]});
  }
  return mess;
}
given_me_junk(objg) {
  if(give_count < 2) return;
  give_count += 1;
  move_object(objg,environment(this_object()));
  write(cap_name+" drops "+objg->query_short()+"\n");
  return 1;
}

set_armor_params(style,class,res2,special2){
   string cat, subcat;
   int i,s;
   if(!armor_params) armor_params = ({ });
   if(sscanf(style, "%s|%s",cat,subcat) !=2){ 
      if(style != "physical" && style != "magical") style = "physical";
   }
   else if(cat != "other") style = "physical";
   if(member_array(style,armor_params) != -1){
      for(i=0;i<sizeof(armor_params);i++){
         if(style == armor_params[i]){
            armor_params[i+1] = class;
            armor_params[i+2] = res2;
            armor_params[i+3] = special2;
          if(this_object())
            this_object()->RegisterArmor(this_object(), armor_params );
            return;
         }
      }
   } 
   armor_params += ({style,class,res2,special2});
  if(this_object())
   this_object()->RegisterArmor(this_object(), armor_params );
}

set_weapon_params(style,class,special2){
   string cat, subcat;
   int i,s;
   if(!weapon_params) weapon_params = ({ });
   if(sscanf(style, "%s|%s",cat,subcat) !=2){ 
      if(style != "physical" && style != "magical") style = "physical";
   }
   else if(cat != "other") style = "physical";
   if(member_array(style,weapon_params) != -1){
      for(i=0;i<sizeof(weapon_params);i++){
         if(style == weapon_params[i]){
            weapon_params[i+1] = class;
            weapon_params[i+2] = special2;
          if(this_object())
            this_object()->RegisterWeapon(this_object(), weapon_params );
            return;
         }
      }
   }
   weapon_params += ({style,class,special2});
   this_object()->RegisterWeapon(this_object(), weapon_params );
}

/* Returns damage potential (wc) for all registered weapons, with
   additional weight for non-physical damage:
   25% bonus for magical
   50% bonus for other non-physical
*/
query_damage_potential() {
  int tot_dam_pot;
  int s,s2,i;
  object *weps;
  mixed *params;
  int class;
  string style;
  if(!Weapons)
   return (saved_wc?saved_wc:query_wc());
  weps=keys(Weapons);
  s2=sizeof(weps);
  while(s2--)
    if(weps[s2] && (params=Weapons[weps[s2]]) && !weps[s2]->no_exp_effect()) {
      s=sizeof(params);
      weapon_class=0;
      for(i=0;i<s;i+=3) {
        style=params[i];
        class=params[i+1];
        if(style=="physical"||weps[s2]->is_weapon())
          continue;
        else if(style == "magical")
          tot_dam_pot += (5*class/4);  /* 25% bonus for magical damage type */
        else
          tot_dam_pot += (3*class/2);  /* 50% bonus for other styles */
      }
    }
  return tot_dam_pot;
}

/* Returns defensive potential (ac) for all registered armor,
   50% less potential for magical
   75% less potential for other non-physical
*/
query_defense_potential() {
  int tot_def_pot;
  int s,s2,i;
  mixed *params;
  object *armors;
  int class;
  string style;
  if(!Armors)
    return (saved_ac?saved_ac:query_ac());
  armors=keys(Armors);
  s2=sizeof(armors);
  while(s2--)
    if(armors[s2] && (params=Armors[armors[s2]]) && !armors[s2]->no_exp_effect()) {
      s=sizeof(params);
      for(i=0;i<s;i+=4) {
        style=params[i];
        class=params[i+1];
        if(armors[s2]->is_armor())
          continue;
        if(style=="physical")
          tot_def_pot += class;
        else if(style == "magical")
          tot_def_pot += (class/2);
        else
          tot_def_pot += (class/4);
      }
    }
  return tot_def_pot;
}


query_heal_rate(){ return heal_rate; }
query_heal_intv(){ return heal_intv; }
query_spell_chance(){ return spell_chance; }
query_spell_dam(){ return spell_dam_mon; }

set_ghost(x) { ghost = x; } /* verte 9.20.01 */
query_long() { return long_desc; } /* verte 3.17.02 */

query_message_hit_array() { return message_hit; }

set_spell_type(x) { spell_type=x; }

mixed *query_spell_info(string name) {
  int x,s;
  if(!spells)
    return 0;
  s=sizeof(spells);
  for(x=0;x<s;x++)
    if(spells[x][0]==name)
      return spells[x];
  return 0;
}

mixed *query_spells() {
  int s;
  string *spnames;
  if(!spells)
    return 0;
  s=sizeof(spells);
  spnames=allocate(s);
  while(s--)
    spnames[s]=spells[s][0];
  return spnames;
}

/* Redid this part because calling m_decode in /obj/monitor
   directly would eat the #s from the string */
string process_ansi(string str) {
  string *words,as;
  int s;
  if(!str)
    return 0;
  words=explode(str,"$");
  s=sizeof(words);
  while(s--)
    if(as=ANSI(words[s])) {
      words[s]=as;
    }
  return implode(words,"");
}

varargs status add_spell(string name, string mess_target, string mess_room,
                        int chance, mixed damage, mixed type, status hit_all_attackers,
                        string ex_fun, object ex_ob) {
  mixed *nspell;
  if(!name)
    return 0;
  if(chance <= 0 || chance > 100)
    return 0;
  if(!spells)
    spells=({});
  if(query_spell_info(name))
    return 0;
  nspell=allocate(9);
  nspell[0]=name;
  nspell[1]=process_ansi(mess_target);
  nspell[2]=process_ansi(mess_room);
  nspell[3]=chance;
  if(intp(damage))
    nspell[4]=({"1-"+damage});
  else if(stringp(damage))
    nspell[4]=({damage});
  else if(pointerp(damage)) {
    int s;
    s=sizeof(damage);
    while(s--) {
      if(intp(damage[s]))
        damage[s]="1-"+damage[s];
      else if(!stringp(damage[s]))
        damage[s]="1-0";
    }
    nspell[4]=damage;
  } else
    return 0;
  if(!type)
    nspell[5]=({"physical"});
  else if(stringp(type))
    nspell[5]=({type});
  else if(pointerp(type))
    nspell[5]=type;
  else
    return 0;
  if(sizeof(nspell[4])!=sizeof(nspell[5]))
    return 0;
  nspell[6]=hit_all_attackers;
  if(ex_fun) {
    nspell[7]=ex_fun;
    if(ex_ob && objectp(ex_ob))
      nspell[8]=ex_ob;
    else
      nspell[8]=this_object();

  } else {
    nspell[7]=0;
    nspell[8]=0;
  }
  spells+=({nspell});
  return 1;
}

status remove_spell(string name) {
  mixed *rspell;
  if(!spells)
    return 0;
  rspell=query_spell_info(name);
  if(rspell) {
    spells-=({rspell});
    return 1;
  }
  return 0;
}

#ifndef __LDMUD__ /* Rumplemintz */
status set_multi_cast(status x) {
#else
void set_multi_cast(int x) {
#endif
  if(x) 
    multi_cast=1;
  else
    multi_cast=0;
}

int *rand_dam(string *idam) {
  int *ndam;
  int s,x,y,t;
  int min,max,num_dice,side_dice;
  s=sizeof(idam);
  ndam=allocate(s);
  for(x=0;x<s;x++) {
    if(sscanf(idam[x],"%d-%d",min,max)==2)
      if(max>min)
        ndam[x]=min+random(max-min+1);
      else 
        ndam[x]=0;
    else if(sscanf(idam[x],"%dd%d+%d",num_dice,side_dice,t)==3 ||
            sscanf(idam[x],"%dd%d",num_dice,side_dice)==2) {
      for(y=0;y<num_dice;y++)
        t+=random(side_dice+1);
      ndam[x]=t;
    } else
      ndam[x]=0;
  }

  return ndam;
}

status check_attacking_me(object ob) {
  return (object)ob->query_attack()==this_object();
}

status check_player_target(object ob) {
  return (int)ob->is_player();
}

status check_non_player_target(object ob) {
  return !check_player_target(ob);
}

void execute_spell(mixed *cur_spell,object room) {
  int dam,num_targets;
  int s;
  status area;
  object *targets;
  if(cur_spell[6]==0) {
    targets=({attacker_ob});
  } else if(cur_spell[6]==2) {
    if(alt_attacker_ob!=attacker_ob) 
      targets=({alt_attacker_ob});
    else
      return;
  } else {
#ifndef __LDMUD__ /* Rumplemintz */
    targets=filter_array(all_inventory(room),"check_attacking_me",this_object());
#else
    targets = filter(all_inventory(room), "check_attacking_me", this_object());
#endif
  }
  s=sizeof(targets);
  if(s==0)
    return;
  if(cur_spell[6]==1 || cur_spell[6]==3 || cur_spell[6]==4)
    area=1;
  if(cur_spell[6]==3 || cur_spell[6]==6)
#ifndef __LDMUD__ /* Rumplemintz */
    targets=filter_array(targets,"check_player_target",this_object());
  else if(cur_spell[6]==4 || cur_spell[6]==7)
    targets=filter_array(targets,"check_non_player_target",this_object());
#else
    targets = filter (targets, "check_player_target", this_object());
  else if (cur_spell[6] == 4 || cur_spell[6] == 7)
    targets = filter (targets, "check_non_player_target", this_object());
#endif
  s=sizeof(targets);
  if(s==0)
    return;
  if(cur_spell[6]==6 || cur_spell[6]==7)
    targets=({targets[random(s)]});
  if(!area) {
    /* if the target is dead already... bail out -mizan 01 jun 2011 */
    /* if(!targets[0] || !present(targets[0],room)) */
    if(!targets[0] || !present(targets[0],room) || targets[0]->query_ghost())
      return;
    if(cur_spell[1])
      tell_object(targets[0],EMOTER(cur_spell[1],this_object(),targets[0]));
    if(cur_spell[2])
      tell_room(room,EMOTER(cur_spell[2],this_object(),targets[0]),({this_object(),targets[0]}));
    dam=(int)targets[0]->do_damage(rand_dam(cur_spell[4]),cur_spell[5]);
    if(cur_spell[7])
      call_other(cur_spell[8],cur_spell[7],targets[0],room,dam);
  } else {
    int x;
/*
    if(cur_spell[2])
      tell_room(room,EMOTER(cur_spell[2],this_object(),0),({this_object()}));
*/
    for(x=0;x<s;x++) {
      dam=(int)targets[x]->do_damage(rand_dam(cur_spell[4]),cur_spell[5]);
      if(cur_spell[1] && targets[x])
        tell_object(targets[x],EMOTER(cur_spell[1],this_object(),targets[x]));
    if(cur_spell[2])
      tell_room(room,EMOTER(cur_spell[2],this_object(),targets[x]),({this_object(),targets[x]}));
      if(cur_spell[7])
        call_other(cur_spell[8],cur_spell[7],targets[x],room,dam);
    }
  }
}

attack() {
  if(spells && attacker_ob) {
   object room;
   room=environment();
   if(room && present(attacker_ob,room)) {
     int spchance,s,x;
     s=sizeof(spells);
     if(multi_cast) {
       for(x=0;x<s;x++) {
         if(attacker_ob) {
           spchance=random(100)+1;
           if(spchance<spells[x][3])
             execute_spell(spells[x],room);
         }
       }
     } else {
       int chance_total;
       spchance=random(100)+1; 
       chance_total=0;
       for(x=0;x<s;x++) {
         if(spchance > chance_total && spchance <= spells[x][3]+chance_total) {
           execute_spell(spells[x],room);
           break;
         } else if(room) {
           chance_total+=spells[x][3];
         }
       }
     }     
   } 
  }
  if(this_object())
  ::attack();
}

int avg_dam(string dstr) {
  int min,max,num_dice,side_dice,t;
  if(sscanf(dstr,"%d-%d",min,max)==2) {
    if(max>min) {
      return (min+((max-min)/2));
    } else 
      return 0;
  } else if(sscanf(dstr,"%dd%d+%d",num_dice,side_dice,t)==3 ||
          sscanf(dstr,"%dd%d",num_dice,side_dice)==2) {
    min=t;
    max=min+num_dice*side_dice;
    min+=num_dice;
    return min+((max-min)/2);
  } else
    return 0;
}

int query_spell_exp() {
  int x,y,s,ss;
  int extra_exp_tot;
  int extra_exp_round;
  int chance_total;
  int spells_used;
  int bonus;
  s=sizeof(spells);
  if(!spells || !sizeof(spells))
    return 0;
  chance_total=0;
  extra_exp_tot=0;
  for(x=0;x<s;x++) {
    extra_exp_round=0;
    ss=sizeof(spells[x][4]);
    /* Calculate total damage with a bonus for non-physical */
    for(y=0;y<ss;y++) {
      if(spells[x][5][y]=="physical")
        extra_exp_round+=avg_dam(spells[x][4][y]);
      else
        extra_exp_round+=avg_dam(spells[x][4][y])*NONPHYS;
    }
    switch(spells[x][6]) {
      default: bonus=100; break;
      case 1: bonus=120; break; /*extra exp for area attacks */
      case 3: case 4: bonus=110; break; /*for limited area attacks */
      case 2: bonus=80; /*Less than standard for alt_attacker */
    }
    extra_exp_round+=(extra_exp_round*bonus/100-extra_exp_round);
    
    /* Average damage is spell avg damage*chance in multicast mode */
    if(multi_cast)
      extra_exp_tot+= (extra_exp_round * spells[x][3] / 100);
    else {
      chance_total+=spells[x][3];
      extra_exp_tot+=extra_exp_round;
    }
    if(chance_total>=100)
    {
      x++;  /* since we're breaking out of the loop early manually iterate */
      break;
    }
  }
  if(multi_cast)
    return extra_exp_tot;
  else /* In non multi-cast motive the chance is cumulative not averaged */
    return extra_exp_tot * chance_total / 100 / x;
}

query_total_level() { return level; }

set_corpse_short(str) {
  corpse_short=str;
}
query_corpse_short() {
  return corpse_short;
}
set_corpse_long(str) {
  corpse_long=str;
}
query_corpse_long() {
  return corpse_long;
}
set_corpse_name(str) {
  corpse_name=str;
}
query_corpse_name() {
  return corpse_name;
}
set_death_emote(str) {
  death_emote=str;
}
query_death_emote() {
  return death_emote;
}
perform_death_emote() {
  string emote;
  object room;
  if(death_emote && (room=environment()) && this_player()
     && (emote=EMOTER(death_emote,this_object(),this_player())))
    tell_room(room,format(emote));
}

/* [2006.06.30] Forbin -added SetMultipleIds & QueryMultipleIds to support
                        multiple ids */
void SetMultipleIds(string *x)
{
  multipleIds = x;
  /* Adding default "npc" id here as well - Rumplemintz */
  multipleIds += ({ "npc" });
}

string * QueryMultipleIds()
{
 return multipleIds;
}

query_saved_wc(){ return saved_wc; }
query_saved_ac() { return saved_ac; }
query_saved_hr() { return saved_hr; }
query_saved_hi() { return saved_hi; }


/*
 * Pavlik - 10/21/2005
 */
mixed query_armor_params(string dtype)
{
  int i;
  if(!dtype)
  {
    return armor_params;
  }
  for(i=0;i<sizeof(armor_params);i+=4)
  {
    if(armor_params[i] == dtype)
    {
      return ( armor_params[i], armor_params[i+1], armor_params[i+2], armor_params[i+3] );
    }
  }
  return 0;   /* what do we return if no match was found? */
}

int query_armor_class(string dtype)
{
  int i;
  if(!dtype)
  {
    return 0; /* return 0, or maybe just return physical? */
  }
  for(i=0;i<sizeof(armor_params);i+=4)
  {
    if(armor_params[i] == dtype)
    {
      return armor_params[i+1];
    }
  }
  return 0;   /* no matching dtype: return 0, or maybe just return physical? */
}

int query_armor_res(string dtype)
{
  int i;
  if(!dtype)
  {
    return 0; /* return 0, or maybe just return physical? */
  }
  for(i=0;i<sizeof(armor_params);i+=4)
  {
    if(armor_params[i] == dtype)
    {
      return armor_params[i+2];
    }
  }
  return 0;   /* no matching dtype: return 0, or maybe just return physical? */
}

/* pavlik: begin wander addition */
void set_wander(int i)
{
  /* one heartbeat every (3) seconds */
  wander = i/3;
  if(wander < 1) wander = 1;
}
int query_wander(){ return wander; }

void set_wander_interval(int i){ wander_interval = i; }
int query_wander_interval(){ return wander_interval; }

void set_wander_realm(string s){ wander_realm = s; }
string query_wander_realm(){ return wander_realm; }

wander()
{
  string *dest_dir, *exits;
  string tmp, tmp2;
  int i, x;

  if(!this_object() || !environment()) return 1;

  /* wander_realm is required! */
  if(!wander_realm) return 1;

  dest_dir = environment()->query_dest_dir();
  if(!dest_dir || !(x = sizeof(dest_dir))) return 1;

  exits = ({});

  for(i=1; i<x; i+=2)
  {
	/*
	 * if the dest_dir path is not absolute then make it so
	 *   (ie: change "players/.../" to "/players/.../")
	 * this could cause a problem if some wizards use relative paths, but
	 * they aren't supposed to be doing that.
	 */
	if(dest_dir[i-1][0..0] != "/")
		dest_dir[i-1] = "/" + dest_dir[i-1];

	/* our check depends on whether wander_realm is absolute or relative */
	/* absolute */
	if(wander_realm[0..0] == "/")
	{
		if(sscanf(dest_dir[i-1], wander_realm+"%s", tmp) == 1)
{
  if (!exits || !sizeof(exits)) exits = ({ dest_dir[i] });
    else exits += ({ dest_dir[i] });
/*
shout("i: "+i+"\t\/\t"+dest_dir[i]+"\t sizeofexits: "+sizeof(exits)+"\n");
*/
}
	}
	/* relative */
	else
	{
		if(sscanf(dest_dir[i-1], "%s"+wander_realm+"%s", tmp, tmp2) == 2)
			exits += dest_dir[i];
	}
  }

  /* just stop here if no possible exits were found */
  if(!exits || !sizeof(exits)) return 1;

  i = random(sizeof(exits)-1);

  if(exits[i])
	command(exits[i], this_object());

  return 1;
}
/* pavlik: end wander addition */

void load_default_attribs(int x)
{
  /* nothing for now */
}

void load_stats(int w, int a, int h)
{
  set_wc(w);
  set_ac(a);
  set_hp(h);
}

void
set_level(int tmp)
{
  int z, tmpAc, n;
  
  level = tmp;
  if(!experience)
  {
    experience = (int)"/room/adv_guild"->query_cost(tmp-1);
  }
  if(!heal_intv)
  {
    heal_intv = ((level < 12) ? 120 : 35);
    heal_rate = 2;
  }
  if(!saved_hi)
  {
    saved_hi=heal_intv;
  }
  if(!saved_hr)
  {
    saved_hr=heal_rate;
  }
  if(!message_hit)
  {
    message_hit=({"massacre"," to small fragments","smashed"," with a bone crushing sound","hit"," very hard","hit"," hard","hit","","grazed","","tickled"," in the stomach"});
  }
  
  switch(tmp)
  {
    case 1..14:
      switch(tmp)
      {
        case 1..2:
          tmpAc=3;
          break;
        case 3..4:
          tmpAc=4;
          break;
        case 5..6:
          tmpAc=5;
          break;
        case 7:
          tmpAc=6;
          break;
        case 8..9:
          tmpAc=7;
          break;
        case 10:
          tmpAc=8;
          break;
        case 11..12:
          tmpAc=9;
          break;
        case 13..14:
          tmpAc=tmp-3;
          break;
      }
      load_stats((4 + tmp), (tmpAc), (tmp * 15));
    break;

    case 15..20:
      z = (20 - (tmp));
      load_stats((30 - (z * 2)), (17 - z), (500 - (50 * z)));
      break;

    case 21:
      load_stats(34, 19, 600);
      break;

    case 22..25:
      z = (25 - (tmp));
      load_stats((44 - (z * 2)), (23 - z), (1000 - (100 * z)));
      break;

    case 26:
      load_stats(46, 24, 1200);
      break;

    case 27:
      load_stats(48, 25, 1500);
      break;

    case 28:
      load_stats(52, 26, 1800);
      break;
    
    case 29:
      load_stats(55, 28, 2000);
      break;
    
    case 30:
      load_stats(60, 30, 2500);
      break;
  }
  
  load_default_attribs(tmp);
    
  if(!hit_point)
  {
    set_hp(50 + (level - 1) * 8);
  }
}

void
wimpy_out()
{
  int x, s;
  string *dd, *de;
  object e;
    
  s=sizeof(dd = (string *)(e=environment())->query_dest_dir());
  
  de=({});
  
  for(x=1;x<s;x+=2)
  {
    de+=({dd[x]});
  }

  tell_room(environment(), (wimpy_msg ? wimpy_msg : 
       cap_name+" runs away...\n"));

  e->init();
  command((wimpy_exit ? wimpy_exit : de[random(sizeof(de))]),
      this_object());
}

void remove_object(object caller) { 
  destruct(this_object());
}
query_save_flag() { return 1; }

void ready_eq()
{
  object *inv;
  int old_wc, old_ac;
  int x, y;
  object ob;

 if(readied) return;
  readied=1;
  inv = all_inventory(this_object());
  y = sizeof(inv);

  old_wc = (int)query_wc();
  old_ac = (int)query_ac();

  for(x = 0; x < y; x ++)
  {
    ob = inv[x];

    if(ob->is_weapon())
    {
      command("wield "+(string)ob->query_name());
    }
    if(ob->is_armor())
    {
      command("wear "+(string)ob->query_name());
    }
  }

  set_wc(old_wc);
  set_ac(old_ac);
}
