#include "../define.h"
inherit ROOM;

reset(arg) {

  if(!present("civilian_mob", this_object())){
   MO(CO("/players/maledicta/ares/mobs/civilian"), this_object());
   if(random(100) < 50) MO(CO("/players/maledicta/ares/mobs/civilian"), this_object());
   }
  if(random(100) < 30){
   if(!present("townguard_mob", this_object())){
   MO(CO("/players/maledicta/ares/mobs/tguard"), this_object());
   if(random(100) < 10) MO(CO("/players/maledicta/ares/mobs/tguard"), this_object());
   }
  }
/*
  if(random(100) < 10){
   if(!present("special_mob", this_object())){
   MO(CO("/players/maledicta/ares/mobs/special_mob"), this_object());
   }
  }
*/
   if(arg) return;
   set_short(RED+"New Ares"+NORM);
   set_light(1);
   set_long(
YEL+"########"+NORM+"  [Celestial Avenue]\n"+
YEL+"##"+NORM+HIB+"A"+NORM+BOLD+"+---"+NORM+YEL+"#"+NORM+"\n"+
YEL+"###"+NORM+BOLD+"|"+NORM+YEL+"#"+NORM+HIB+"W"+NORM+BOLD+"|"+NORM+YEL+"#"+NORM+"  You walk along Celestial Avenue. Large\n"+
BOLD+"-"+HIR+"x"+NORM+BOLD+"-+"+NORM+YEL+"##"+NORM+BOLD+"+-"+NORM+"  houses line the street on each side as\n"+
YEL+"#"+NORM+HIB+"a"+NORM+YEL+"#"+NORM+BOLD+"|"+NORM+YEL+"#"+NORM+HIB+"B"+NORM+BOLD+"|"+NORM+YEL+"#"+NORM+"  you cross through the upper class section\n"+
YEL+"#"+NORM+HIB+"I"+NORM+YEL+"#"+NORM+BOLD+"|"+NORM+YEL+"####"+NORM+"  of New Ares. A large house stands before\n"+
YEL+"#"+NORM+BOLD+"--+---"+NORM+YEL+"#"+NORM+"  you to the south. To the west is a large\n"+
YEL+"###"+NORM+BOLD+"|"+NORM+YEL+"####"+NORM+"  gate, and to the east the street continues.\n");

   add_item(
      "road",
      "Paved with flagstones, this short road extends to the gate to the west and\n"+
      "to the main road to the east");
   add_item(
      "street",
      "Paved with flagstones, this short road extends to the gate to the west and\n"+
      "to the main road to the east");
   add_item(
      "gate",
      "A beautiful gate that leads into the Temple District");
   add_item(
      "houses",
      "Being so close to the Temple district you see only large expensive houses");
   add_item(
      "house",
      "A large house that is slightly run down compared to the others\n"+
      "around it");
   
   add_exit(ROOMS+"city11","east"); 
   add_exit(ROOMS+"city13","west"); 
   add_exit(ROOMS+"potion_store","south");
   }

init(){
 ::init();
 add_action("get_key", "key");
 }

get_key(){
 write("\n\n"+HIM+"Map Key Code:"+NORM+"\n"+
       "   A "+HIM+"-"+NORM+"  Armorer\n"+
       "   B "+HIM+"-"+NORM+"  Bar\n"+
       "   I "+HIM+"-"+NORM+"  Inn\n"+
       "   W "+HIM+"-"+NORM+"  WeaponSmith\n"+
       "   a "+HIM+"-"+NORM+"  Alchemist\n"+
       "   x "+HIM+"-"+NORM+"  You!\n\n\n");
  return 1;
  }