static status wielded;
static int no_go_time;
static int no_go_over;
static object wielded_by;
static int broke;
static int eff_wc;
static int misses,hits;
static int save_flag,class_of_weapon;
static object hit_func;
static string type;
static string *message_hit;
weapon_class() {
   return class_of_weapon;
}
hit(attacker)
{
   if (hit_func)
      return call_other(hit_func,"weapon_hit",attacker);
   return 0;
}
set_class(c) { class_of_weapon = c; }
weapon_breaks(){
   if(broke) return 1;
   return 1;
}
count_misses() {
   misses += 1;
   return 1;
}
count_hit_made(w) {
   hits += 1;
   eff_wc=((hits-1)*eff_wc + w)/hits;
   return 1;
}
query_wear() {
   return 0;
}
add_wear(arg) {
   misses = 0;
   hits = 0;
}
fix_weapon() {
   if (!broke) {
      return 0;
   }
   broke = 0;
   return 1;
}
re_break() { 
   broke = 1;
   return 1;
}

query_broke(){return broke;}

query_pro_weapon(){ return 1;}


query_message_hit(tmp) {
  string *mess;

 if (tmp > 55) {
  mess = ({message_hit[1],message_hit[0]}); 
  }
  else if (tmp > 45){
  mess = ({message_hit[3],message_hit[2]});
  }
  else if (tmp > 35){
  mess = ({message_hit[5],message_hit[4]});
  }
  else if (tmp > 30) {
  mess = ({message_hit[7],message_hit[6]});
  }
  else if (tmp > 25) {
  mess = ({message_hit[9],message_hit[8]});
  }
  else if (tmp > 20) {
  mess = ({message_hit[11],message_hit[10]});
  }
  else if (tmp > 10) {
  mess = ({message_hit[13],message_hit[12]});
  }
  else if (tmp > 5) {
  mess = ({message_hit[15],message_hit[14]});
  }
  else if (tmp > 3) {
  mess = ({message_hit[17],message_hit[16]});
  }
  else if (tmp > 1) {
  mess = ({message_hit[19],message_hit[18]});
  }
  else if (tmp == 1){
  mess = ({message_hit[21],message_hit[20]});
  }
  
  return mess;
}

/****************************************************************
***********  Proficiency Hit for Paladin object code ************
*****************************************************************/
gen_wc_bonus()
{
  int total, str_bonus;
  total = 0;
  if(no_go_time < time()) no_go_over = 0;
  if(no_go_over >= 2) return;
  no_go_time = time();
  no_go_over += 1;
  
  if(!USER) return 0; /* just a test!  added by verte 6.23.01 */
  
  str_bonus = USER->query_attrib("str");
	
  /********  This only happens if no Wep is wielded **********/
  if(USER->query_weapon() == this_object())
  {
    total += clawstwo();
    total += clawstwo();
  }
  /**********************************************************/
	
  total += str_bonus / 5;  /* 5 max */
	
  total += GOB->query_t_attack();
	
  if(!USER->query_attack()) return 0;  /* added by verte 6.23.01 */

  if(USER->query_attack()->webbed() || 
     present("venom_web_object", USER->query_attack()) && 
     GOB->query_combat())
  {
    total += random(GOB->query_combat() * 2) + GOB->query_combat();
  }

  if(USER->QL > 19 || USER->QRN == "toy") 
    TOM HIG+"NEO SYMB TOTAL IS: "+total+NORM+".\n");
  return total;
}