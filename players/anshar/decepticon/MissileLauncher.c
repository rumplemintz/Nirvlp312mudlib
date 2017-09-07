#include "/players/beck/Defs.h"
#include "/players/beck/Transformers/Decepticons/Guild/Object/Enhancement.h"
static status type;

id(str){
   return str == "missile launcher";
}

RestoreEnhancement(){
   mixed *data;
   data = Base->QData(Name);
   if(data){
      Online = data[0];
   }
   if(Online){
      enable_commands();
      move_object(TO,ENV(Base));
   }
}

Configure(str){
   if(str == "online"){
      if(Online){
         write(Name+" is already Online.\n");
         return 1;
      }
      write(Name+" is Online.\n");
      enable_commands();
      move_object(TO,ENV(Base));
      SOnline(1);
   }
   else if(str == "offline"){
      if(!Online){
         write(Name+" is already Offline.\n");
         return 1;
     }
      write(Name+" is Offline.\n");
      move_object(TO,ENV(Base));
      type = 0;
      SOnline(0);
   }
   else if(str == "explosive"){
      write(Name+" is configured for impact missiles.\n");
      CommTower = (object) Base->QCurrEnhancement("Communications Tower 1");
      call_out("explode",5);
      type = 1;
   }
      else {
         write(capitalize(str)+" is not present to track.\n");
         return 1;
      }
   }
   else if(command(str, TO)){
      write(Name+" is doing "+str+".\n");
      return 1;
   }
   else {
      write("That is not a configuration option for "+Name+"\n");
      return 1;
   }
   Base->AData(Name, ({Online}));
   return 1;
}

explode(){
   object ob;
   if(type != 1)
      return;
   if(!Online)
      return;
   blast();
   call_out("explode",5);
   return 1;
}

blast(){
   object atkr;
   int X;
   X = random(35);
   atkr = query_attack();
   if(!atkr) {
      return;
      }
   atkr->hit_player(X);
   write(
   HIR+"     *****  *       ***   **   **  *****\n"+
       "     *      *      *   *  * * * *  *    \n"+
       "     ***    *      *****  *  *  *  ***  \n"+
       "     *      *      *   *  *     *  *    \n"+
       "     *      *****  *   *  *     *  *****\n"+
       "    ENGULFS THE ROOM AS A MISSILE STRIKES!"+NORM+"\n");
   return;
   }