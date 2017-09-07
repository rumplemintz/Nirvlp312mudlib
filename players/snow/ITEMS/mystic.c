/*
A Dispenser of some of Snow's Mystical Devices.
Dispenses Feelers, Ether Gliders, and heals.
*/

#include "/players/snow/closed/color.h"
 
#define TP this_player()
#define TPN capitalize(TP->query_name())
#define MON TP->query_money()
#define HEALNUM 9
 
int *healprices;
int *heals;
int spent, lasttime;
status process;

id(str) { return str=="dispenser" || str == "cube" || str == "mystic_cube"; }
short() { return "An Icy Cube"; }
long() {
   write("You see before you a strange cube of blue ice. As you peer\n"+
         "inside it, a strange voice speaks inside your head:\n\n"+
         "\tDispenser of Mystic Devices, type 'list' to see what I have.\n");
  if(TP->query_level() > 20) {
    write("Spent in the last 8 hours: "+spent+"\n"); return 1; }
  return 1; }

init() {
  add_action("list_mystic","list");
  add_action("buy_mystic","buy");
}
reset(arg) {
  int i;
  if(!restore_object("players/snow/ITEMS/mystic")) {
    lasttime = time();
    healprices = ({1800,1800,1800,1800,1800,1800,3300,3300,3300});
    heals = ({20,20,20,20,20,20,20,20,20}); }
  if(arg) {
   for(i=0; i < HEALNUM; i++) {
    healprices[i] -= random(20);
    check_price(i);
  save_object("players/snow/ITEMS/mystic");
  } }
   write_file("/players/snow/log/mystic", ctime(time()));
   for(i=0; i < HEALNUM; i++) {
     write_file("/players/snow/log/mystic", " "+heals[i]+" "+healprices[i]); }
     write_file("/players/snow/log/mystic"," "+spent);
   write_file("/players/snow/log/mystic", "\n");
  if(time() - lasttime > 28800) { spent = 0; lasttime = time(); }
}

reset_heal(int num) {
  if(!num) return 5;
  if(!environment()) return 6;
  num --;
  tell_room(environment(),
    BOLD+"The CUBE pulses strangely.\n"+OFF);
  heals[num] += 20;
  healprices[num] += 300;
  return 1; }

check_price(i) {
    if(i < 6)  { if(healprices[i] < 1300) healprices[i] = 1300; }
    if(i > 5)  { if(healprices[i] < 2500) healprices[i] = 2500; }
  return 1; }
 
list_mystic(str) {

  write(
"##########################################################\n"+
"     ITEMS                       AVAILABLE    COST\n"+
"##########################################################\n"+
" 1.  Discreet Emoter (feeler)...    "+pad("UNLIM",10)+" 100\n"+
" 2.  Shamrock...                    "+pad("UNLIM",10)+" 200\n"+
"--HEALS--\n"+
" 3.  UltraMorph (tab)...            "+pad(heals[0],10)+healprices[0]+"\n"+
" 4.  SuperGoop (goop)...            "+pad(heals[1],10)+healprices[1]+"\n"+
" 5.  ProteinBlast (blast)...        "+pad(heals[2],10)+healprices[2]+"\n"+
"--LARGER DOSE HEALS--\n"+
" 6.  UltraMorph (ltab)...           "+pad(heals[3],10)+healprices[3]+"\n"+
" 7.  SuperGoop (lgoop)...           "+pad(heals[4],10)+healprices[4]+"\n"+
" 8.  ProteinBlast (lblast)...       "+pad(heals[5],10)+healprices[5]+"\n"+
"--HIGH POTENCY HEALS--\n"+
" 9.  UltraMorph (htab)...           "+pad(heals[6],10)+healprices[6]+"\n"+
" 10. SuperGoop (hgoop)...           "+pad(heals[7],10)+healprices[7]+"\n"+
" 11. ProteinBlast (hblast)...       "+pad(heals[8],10)+healprices[8]+"\n"+
"\n"+
"##########################################################\n");
return 1;
}
 
buy_mystic(str) {
  object item;
  int price, number;
  string mess, rmess;
  if(!str) { write("Buy what?\n"); return 0; }
  if(!call_other(this_player(), "add_weight", 2) ) {
    write("You are carrying too much to buy anything more.\n"); return 1; }
  switch(str) {
    case "feeler": case "1":
    price = 100;
    item=clone_object("/players/snow/ITEMS/dfeeler.c");
    mess = "You now have a Discreet Emoter! Have a good time...\n";
    rmess = TPN+" buys a Discreet Emoter!\n";
      break;
    case "shamrock": case "2":
    price = 200;
    item = clone_object("/players/snow/ITEMS/shamrock");
    mess = "You purchase a Shamrock! (sniff, sniff, sniff...)\n";
    rmess = TP->query_name()+" buys a Shamrock!\n";
      break;
    case "tab": case "3":
    item = clone_object("/players/snow/heals/umorph");
    mess = "You purchase an UltraMorph (UM)!\n";
    rmess = TPN+" buys an UltraMorph!\n";
    number = 1;
      break;
    case "goop": case "4":
    item = clone_object("/players/snow/heals/sgoop");
    mess = "You purchase a SuperGoop!\n";
    rmess = TPN+" buys a SuperGoop!\n";
    number = 2;
       break;
    case "blast": case "5":
    item = clone_object("/players/snow/heals/pblast");
    mess = "You purchase a ProteinBlast!\n";
    rmess = TPN+" buys a ProteinBlast!\n";
    number = 3;
      break;
    case "ltab": case "6":
    item = clone_object("/players/snow/heals/lumorph");
    mess = "You purchase a large dose UltraMorph!\n";
    rmess = TPN+" buys a large dose UltraMorph!\n";
    number = 4;
      break;
    case "lgoop": case "7":
    item = clone_object("/players/snow/heals/lsgoop");
    mess = "You purchase a large dose SuperGoop!\n";
    rmess = TPN+" buys a large dose SuperGoop!\n";
    number = 5;
      break;
    case "lblast": case "8":
    item = clone_object("/players/snow/heals/lpblast");
    mess = "You purchase a large dose ProteinBlast!\n";
    rmess = TPN+" buys a large dose ProteinBlast!\n";
    number = 6;
      break;
    case "htab": case "9":
    item = clone_object("/players/snow/heals/humorph");
    mess = "You purchase a high density UltraMorph!\n";
    rmess = TPN+" buys a high density UltraMorph!\n";
    number = 7;
      break;
    case "hgoop": case "10":
    item = clone_object("/players/snow/heals/hsgoop.c");
    mess = "You purchase a high density SuperGoop!\n";
    rmess = TPN+" buys a high density SuperGoop!\n";
    number = 8;
      break;
    case "hblast": case "11":
    item = clone_object("/players/snow/heals/hpblast.c");
    mess = "You purchase a high density ProteinBlast!\n";
    rmess = TPN+" buys a high density ProteinBlast!\n";
    number = 9;
      break;
    default: write("Not available ["+str+"]\n"); return 1;
  }
  if(!price) { price = healprices[number-1]; }
  if(!price) { write("ERROR #142\n"); return 1; }
  if(price > MON) {
    write("You have only "+MON+" coins!\n"); return 1; }
  if(number) {
    number --;
    heals[number] --;
    if(!heals[number]) {
      number ++; reset_heal(number); }
  }
  if(!item) { write("ERROR #242\n"); return 1; }
  move_object(item, TP); write(mess); say(rmess);
  TP->add_money(-price);
  spent += price;
  TP->recalc_carry();
  save_object("players/snow/ITEMS/mystic");
  return 1;
}

raiseprice(int which, int amount) {
  healprices[which] += amount; return 1; }

query_spent() { return spent; }

remove_object(prev) {
  save_object("players/snow/ITEMS/mystic");
}