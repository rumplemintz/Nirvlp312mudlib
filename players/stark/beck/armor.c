#include "/players/beck/Defs.h"
#include "/players/beck/Rangers/RangerDefs.h"

RangerInit(){
   if(PO->QuerySkillLevel("armor") >= 2){
      PO->AHiddenSkill("lamp","beck");
   }
   if(PO->QuerySkillLevel("armor") >= 5){
     PO->AHiddenSkill("marmor","beck",7);
     PO->AHiddenSkill("rwear","beck");     
   }
   if(PO->QuerySkillLevel("armor") >= 10){
      
   }
}

RangerPower(str,Align){
   
}

QMax(){
   return 20;
}

QRangerInfo(){ return 1; }

RangerInfo(str){
   write("Armor is your physical protection against your enemy.\n"+
         "\n"+
         "Armor skills:\n\n"+
         "Suit                        1   (Your basic suit)\n"+
BOLD+RED+"Lamp"+OFF+"                        2\n"+
         "Metallic Armor ("+BOLD+RED+"Marmor"+OFF+")     5\n"+
BOLD+RED+"Rwear"+OFF+"                       5 (Type Scarf.)\n"+
BOLD+RED+"Rwear"+OFF+"                       8 (Type Orb.)\n"+
BOLD+RED+"Rwear"+OFF+"                      10 (Type Misc.)\n"+
BOLD+RED+"Rwear"+OFF+"                      15 (Type Amulet.)\n"+
         "");
   return 1;
}

DefSkill(int level){
   return (1+(level/5));
}