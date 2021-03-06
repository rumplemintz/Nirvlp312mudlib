
#include "/players/jaraxle/define.h"
#define moose this_object()->query_attack()
#define moosen capitalize(moose->query_name())
#define dam_count query_dam_taken_this_round()
inherit "/players/vertebraker/closed/std/monster.c";
reset(arg)  
{
   object gold;
   ::reset(arg);
   if(arg) return;
   set_name(HIW+"Phantom"+NORM);
   set_alias("spirit");
   set_alt_name("demon");
   set_race("phantom");
   set_aggro(1, 10, 90);
   set_short(HIW+"Phantom"+NORM);
set_long("  The Phantom is a lost and lonely creature from another plane\n"+
         "of existance.  These Phantoms were said to have ripped through\n"+
         "their realm into Nirvana to absorb the life and energy of the\n"+
         "land.  Continuously floating, forever hunting.\n");
   set_level(25);
   set_hp(1000+random(150));
   set_al(-1000);
   set_wc_bonus(85);
   set_ac(24+random(5));
   set_wc(45+random(6));
   set_dead_ob(this_object());
   set_chat_chance(4);
   load_chat("The "+HIW+"Phantom"+NORM+" wails.\n");
   load_chat("The "+HIW+"Phantom"+NORM+" wails.\n");
   
}

monster_died() {
   object b, c;
   c = present("corpse", environment());
   if(c){ destruct(c); }
   tell_room(environment(this_object()),
      "The "+HIW+"Phantom"+NORM+" disappears into a feeble spirit.\n");
move_object(clone_object("/players/jaraxle/3rd/alt/items/spirit.c"),TO);
   return 0; }     


spec1(){
   
   string ATT_NAME,msg;
   int total_damage, i;
   string hit_type;
   if(attacker_ob)  ATT_NAME = attacker_ob->query_name();
   say("\nThe "+HIW+"Phantom"+NORM+" lashes wildly at "+ATT_NAME+". . .\n");
   for(i = 0; i < 6; i++) { 
      switch(random(7)){
         case 0: hit_type = ""+BLK+BOLD+"lashes"+NORM+"";
         total_damage +=14;
         break;
         
         case 1: hit_type = ""+BLK+BOLD+"slashes"+NORM+"";
         total_damage +12;
         break;
         
         case 2: hit_type = ""+BLK+BOLD+"slices"+NORM+"";
         total_damage +=9;
         break;
         
         case 3: hit_type = ""+BLK+BOLD+"thrashes"+NORM+"";
         total_damage +=8;
         break;
         
         case 4: hit_type = ""+BLK+BOLD+"whips"+NORM+"";
         total_damage +=5;
         break;
         
         case 5: hit_type = ""+BLK+BOLD+"welts"+NORM+"";
         total_damage +=3;
         break;
         
         case 6: hit_type = ""+BLK+BOLD+"misses"+NORM+"";
         total_damage +=0;
         break;
       }
      
      say("\tThe sharp claws of the "+HIW+"Phantom"+NORM+" "+hit_type+" "+ATT_NAME+"\n");
   }
   
   attacker_ob->hit_player(total_damage);
   /*
   say(HIY+"\t Damage: "+HIR+total_damage+NORM+"\n");
   */
   
}

spec2(){
   string ATT_NAME,msg;
   int total_damage, i;
   string body_part;
   object para_obj;
   if(attacker_ob)  ATT_NAME = attacker_ob->query_name();
   para_obj = "/players/jaraxle/3rd/alt/mobs/para.c";
   say("\t"+BWHT+BLK+"The Phantom passes through your body!\n"+NORM);
   for(i = 0; i < 1 + random(6); i++)
   {
      switch(random(6)){
         case 0: body_part = "leg";
         total_damage +=2;
         break;
         case 1: body_part = "fingers";
         total_damage +=5;
         break;
         case 2: body_part = "chest";
         total_damage +=8;
         break;
         case 3: body_part = "arm";
         total_damage +=10;
         break;
         case 4: body_part = "spine";
         total_damage +=12;
         break;
         case 5: body_part = "neck";
         total_damage +=3;
         break;
       }
      
      say("You feel a "+HIC+"cold"+NORM+" chill down your "+body_part+"!\n");
      
      /*
      say(HIY+"\t Damage: "+HIR+total_damage+NORM+"\n");
      */
      
   }
if(!present("freeze_me", attacker_ob)){ 
move_object(clone_object(para_obj), attacker_ob);
}
   attacker_ob->add_spell_point(-total_damage);
}



spec3(){
   object *inv;
   int lil_doggy, i;
   inv = all_inventory(environment());
   lil_doggy = sizeof(inv);
   tell_room(environment(moose),
      "The "+HIW+"Phantom"+NORM+" erupts a banshee wail!\n");
   
   tell_room(environment(moose),
      HIW+"\tThe shockwave rocks the room!\n\n");
   for(i = 0; i < lil_doggy; i++)
   {
      if(inv[i]->query_name() != "phantom")
         {
         if(living(inv[i]))
            {
            tell_object(inv[i], "\t"+BWHT+BLU+"Your ears begin to "+RED+"bleed"+NORM+"\n\n");
            inv[i]->hit_player(20 + random(21));
         }
       }
   }
}  


heart_beat(){
   int i;
   ::heart_beat();
   if(attacker_ob){
      i = random(15);
      switch(i){
         
         case 0..3: spec1();
         break;
         
        case 4: spec2();
         break;
         
         case 5..8: spec3();
         break;
         
         
         case 9..14: return 0;
         break;
      }
   }
}
