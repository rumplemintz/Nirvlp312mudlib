#include "/players/beck/Defs.h"
#include "/players/beck/Rangers/RangerDefs.h"
#include "/players/beck/Rangers/CommandCenter/Enhancement.h"
static string Channel;
int Pulse;

id(str){
   return str == "communications tower";
}

RestoreEnhancement(){
   mixed *data;
   data = Base->QData(Name);
   if(data){
      Online = data[0];
      if(sizeof(data) >= 2)
         Power = data[1];
   }
   if(Online)
      enable_commands();
}

Configure(str){
   int i;
   if(COMM){
      if(COMM->QuerySkillLevel("communication") < 10){
         write("You do not have the skill to configure the Communications Tower.\n");
         return 1;
      }
   }
   else {
      return 0;
   }

   if(str == "online"){
      write("Communications Tower is Online.\n");
      enable_commands();
      SOnline(1);
   }
   else if(str == "offline"){
      write(Name+" is Offline.\n");
      SOnline(0);
   }
   else if(str == "help"){
      write("Configuration options for "+Name+"\n");
      
      write("syntax is 'configure <option>'\n\n"+
            "online - Turn the Communications Tower on.\n"+
            "offline - Turn the Communications Tower off.\n"+
            "power <amt> - set the tower's power as a %.\n"+
            "              The higher the power, the clearer the incoming messages are,\n"+
            "              but the more power it will consume.\n"+
            
            "transfer <amt> - move Power from the Power Pool to the Communications Tower.\n"+
            "");
      return 1;
   }
   else if(str == "listen"){
      write(Name+" is no longer listening to channels.\n");
      if(Channel == "Power Rangers")
         "/players/beck/Daemons/ChannelDaemon.c"->RemoveChannel("Power Ranger",TO);
      Channel = 0;
   }
   else if(str == "listen power rangers"){
      Channel = "Power Rangers";
      write(Name+" is now set to listen to the Power Rangers.\n");
      "/players/beck/Daemons/ChannelDaemon.c"->AddChannel("Power Ranger",TO);
   }
   else if(sscanf(str,"transfer %d",i) ==1){
      if(Base->QPower("base") > i){
         if(Power + i > 1000){
            write("That amount would overload the "+Name+"\n");
            return 1;
         }
         Base->APower(-i);
         APower(i);
         write("Allocating "+i+" Power for use with "+Name+"\n");
      }
      else{
         write("There is not that much Power to allocate>\n");
         return 1;
      }
   }
   else if(sscanf(str,"power %d",Pulse) == 1){
      if(Pulse < 0)
         Pulse = 0;
      if(Pulse > 100)
         Pulse = 100;
      write(Name+" is set to "+Pulse+"% strength.\n");
   }
   else {
      write("That is not a configuration option for "+Name+"\n");
      return 1;
   }
   Base->AData(Name, ({Online,Power}));
   return 1;
}

catch_tell(str){
   string *message;
   string *temp;
   int i;
   int j;
   if(!Online)
      return;
   if(Power < (1))
      return;
   if(present(TP,environment()))
      return;
/*
   message = explode(str," ");
   temp = ({"#$%@","$%$@#","das#","593sk%"});
   j = sizeof(temp);
   if(sizeof(message) > 2){
      for(i=0;i<sizeof(message); i++){
         if(random((Pulse)) ==0){
            message[i] = temp[random(j-1)];
         }
      }
   }
   str = implode(message," ");
*/
   if(random(50) == 42)
      APower(-(1));

   say(str);
}