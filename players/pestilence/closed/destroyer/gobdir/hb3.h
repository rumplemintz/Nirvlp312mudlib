heart_beat(){
  object me, myenv;
  me = environment();
  if(!me || !me->is_player()) return;
  myenv = environment(me);
  if(!myenv) return;
  if(me->query_attack()) d_attack();
  if(me->query_level() < 21 &&  !me->query_attack() && !random(4)) s_mess();
if(query_spell_delay()) add_spell_delay(-1);
if(query_spell_delay() < 0) set_spell_delay(0);
/*
if(query_spell_delay() == 1) spell_save();
*/
  return 1;
  }

d_attack(){
 object target, me, targetn;
  int w, p, z, q, dex, wepwc, enemy;
 string mess, color, spot;
 me = environment();
 target = me->query_attack();
 targetn = target->query_name();
enemy = query_target();
 w = random(8);
 p = random(25);
 z = random(6);
 q = random(6);
  switch(q){
   case 0: spot = "head"; break;
   case 1: spot = "chest"; break;
   case 2: spot = "leg"; break;
   case 3: spot = "arm"; break;
   case 4: spot = "head"; break;
   case 5: spot = "groin"; break;
   }
  switch(p){
   case 1..2: mess = "Superior genetics adds strength to "+me->query_name()+"'s attack.\n"; break;
   case 3..4: mess = ""+me->query_name()+" hits "+capitalize(targetn)+" very hard in the "+spot+".\n"; break;
   case 5..6: mess = ""+me->query_name()+" hits "+capitalize(targetn)+" extremely hard in the "+spot+".\n"; break;
   case 7..8: mess = "Enhanced dna causes "+me->query_name()+"'s muscles to tense, adding strength to the attack.\n"; break;
   case 9..11: mess = ""+capitalize(targetn)+" crumbles before "+me->query_name()+"'s brute strength.\n"; break;
   case 12..14: mess = ""+me->query_name()+"'s muscles pulse with power.\n"; break;
   case 15..17: mess = ""+me->query_name()+" charges "+capitalize(targetn)+" knocking them backwards.\n"; break;
   case 18..22: mess = "Enhanced genetics add strength to "+me->query_name()+"'s strike on "+capitalize(targetn)+".\n"; break;
   case 23..25: return;
   }
  switch(z){
   case 0: color = YEL; break;
   case 1: color = BLU; break;
   case 2: color = CYN; break;
   case 3: color = HIB; break;
   case 4: color = HIK; break;
   case 5: color = HIR; break;
   }
if(targetn == enemy){
tell_room(environment(environment(this_object())),color+""+mess+""+NORM);
   return 1;}
}

s_mess(){
 object target, me, targetn;
  int k, l, m;

 string mess, color;
 me = environment();
 k = random(21);
 l = random(250);
 m = random(6);
  switch(k){
   case 1..2: mess = "A voice whispers to "+me->query_name()+":   "+HIR+"I NEED BLOOD"; break;
   case 3..5: mess = "A voice whispers to "+me->query_name()+":   "+HIR+"YOU MUST OBEY THE WILL OF PESTILENCE"; break;
   case 6..8: mess = "A voice whispers to "+me->query_name()+":  You must kill!"; break;
   case 9..11: mess= ""+me->query_name()+" twitches uncontrollably."; break;
   case 12..20: return;

   }
  switch(m){
   case 0: color = HIK; break;
   case 1: color = HIR; break;
   case 2: color = HIB; break;
   case 3: color = HIK; break;
   case 4: color = BLU; break;
   case 5: color = RED; break;
   }
 if(k > l){
tell_room(environment(environment(this_object())),color+""+mess+"\n"+NORM);
   return 1;}
}

spell_save() {
if(ETO) {
  if(living(ETO)) {
    USER->save();
 tell_object(USER, ""+YEL+"You may now use study again.\n"+NORM);
    call_out("spell_save2",1);
    return 1;
 }
}
}


spell_save2() {
if(ETO) {
  if(living(ETO)) {
 tell_object(USER, "You may now use study again.\n"+NORM);
    USER->save();
    command("dsave",ETO);
    return 1;
 }

}
}