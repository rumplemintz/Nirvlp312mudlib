#include "/players/boltar/things/esc.h"
string colorstr,backstr;
string style;
init(){
    add_action("color","color");
   add_action("cdescribe","cdescribe");
    add_action("setstyle","setstyle");
   add_action("colormmout","colormmout");
   add_action("colormmin","colormmin");
   add_action("colormin","colormin");
   add_action("colormout","colormout");
   add_action("colormhome","colormhome");
   add_action("setback","setback");
    add_action("coloral","coloral");
     add_action("setcolor","setcolor");
    add_action("colorpre","colorpre");
   }
id(str) {
  return str=="colorob";
}
color(str) {
    str=esc+"[0m"+style+colorstr+str+esc+"[0m";
     call_other(this_player(), "set_title", str);
     return 1;
}
coloral(str) {
    str=esc+"[0m"+style+colorstr+str+esc+"[0m";
     call_other(this_player(), "set_al_title", str);
     return 1;
}
colorpre(str) {
    str=esc+"[0m"+style+colorstr+str+esc+"[0m";
     call_other(this_player(), "set_pretitle", str);
     return 1;
}
colormmout(str) {
    str=esc+"[0m"+style+colorstr+str+esc+"[0m";
     command("setmmout "+str,this_player());
     return 1;
}
cdescribe(str) {
     str=esc+"[0m"+style+colorstr+str+esc+"[0m";
     this_player()->describe(str);
     return 1;
  }
setcolor(str){
    if (!backstr)
     backstr = "40m";
     if (str == "pur")
           colorstr=esc+"[35m"+esc+"["+backstr;
     if (str == "red")
         colorstr = esc+"[31m"+esc+"["+backstr;
     if (str == "gre")
         colorstr = esc+"[32m"+esc+"["+backstr;
     if (str == "yel")
         colorstr = esc+"[33m"+esc+"["+backstr;
     if (str == "blu")
         colorstr = esc+"[34m"+esc+"["+backstr;
     if (str == "cya")
         colorstr = esc+"[36m"+esc+"["+backstr;
     if (str == "whi")
         colorstr = esc+"[37m"+esc+"["+backstr;
return 1;
}
setstyle(str){
      if (str == "none")
         style = esc+"[0m";
     if (str == "bold")
           style = esc+"[1m";
     if (str == "bb")
            style = esc+"[1m"+esc+"[5m";
     if (str == "blink")
           style = esc+"[5m";
     if (str == "under")
           style = esc+"[4m";
return 1;
}
short(){ return "A colorfull colorob";}
colormmin(str) {
    str=esc+"[0m"+style+colorstr+str+esc+"[0m";
     command("setmmin "+str,this_player());
     return 1;
}
colormin(str) {
    str=esc+"[0m"+style+colorstr+str+esc+"[0m";
     command("setmin "+str,this_player());
     return 1;
}
colormout(str) {
    str=esc+"[0m"+style+colorstr+str+esc+"[0m";
     command("setmout "+str,this_player());
     return 1;
}
colormhome(str) {
    str=esc+"[0m"+style+colorstr+str+esc+"[0m";
     command("setmhome "+str,this_player());
     return 1;
}
setback(str){
     if (str == "pur")
           backstr = "45m";
     if (str == "red")
             backstr = "41m";
     if (str == "gre")
          backstr = "42m";
     if (str == "yel")
          backstr = "43m";
     if (str == "blu")
            backstr = "44m";
     if (str == "cya")
          backstr = "46m";
     if (str == "whi")
       backstr = "47m";
  if (!str)
      backstr = "40m";
return 1;
}
get(){
   return 1;
  }
