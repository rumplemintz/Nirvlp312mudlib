#include "/players/pavlik/junk/corsell.c"
#define HP this_player()->query_hp()
inherit "room/room";
 reset(arg) {
  if(!arg) {

  set_light(1);
 short_desc="The Bloodbank";
  long_desc="THE LOCAL BLOOD BANK\n"+
  "Welcome to the local blood bank where doctor's and nurses are busy\n"+
   "sucking the life's juices out of the poor and despereate.  The room is\n"+
 "cluttered with various needles and bags and doughnut crumbs.  Here you\n"+
 "can swap some of your own blood for cold hard cash.  You can also\n"+
 "bring corpses here and sell them off for scientific research.\n"+
 "For more information..Read the Sign!\n";


dest_dir=({
   "players/pavlik/castle/court.c","north",
});

   }
}
init() {
  ::init();
 add_action("sell", "sell");
  add_action("donate","donate");
   add_action("read","read");
}
donate(str) {
       object ob;
  ob = this_player();
 if(str == "pint" && HP < 50) {
       rejected();
      return 1;
          }
   if(str == "quart" && HP < 100) {
       rejected();
      return 1;
          }
   if(str == "gallon" && HP < 200) {
      rejected();
        return 1;
          }
     write("You offer a "+str+" of your blood for a noble cause.\n"+
    "A pretty nurse pulls you aside and bats her long eyelashes at you...\n"+
    "and pulls a 2 foot needle from behind her back.  With the gentleness\n"+
    "only underpaid nurses seem to have she jabs the needle into your arm\n"+
    "and sucks out a "+str+" of your blood.\n");
      write("She assists you to a long table where they cram you full of\n"+
   "jelly doughnuts and orange juice.  A fat man at the counter pays you\n"+
   "your money.\n");

say(capitalize(ob->query_real_name())+" donates a "+str+" of blood.\n"+
  "They put "+capitalize(ob->query_real_name())+" on a table,"+
"suck their body dry\n and give them some money.\n");
    if(str == "pint") {
       call_other(ob, "heal_self", -50);
        call_other(ob, "add_money", 500);
            return 1;
           }
   if(str == "quart") {
        call_other(ob, "heal_self", -100);
         call_other(ob, "add_money", 1000);
           return 1;
        }
    if(str == "gallon") {
        call_other(ob, "heal_self", -200);
          call_other(ob, "add_money", 3000);
           return 1;
        }
     write("A fat nurse comes over and pokes you in the ribs.\n"+
 "Fat nurse says: 'Hey! Are you gonna donate blood or what???\n"+
   "If you need help Read the sign!!!'\n"+
     "The Fat Nurse goes back to torturing..er...accepting donations\n"+
     "from the customers.\n");
            return 1;
  }
read(str) {
  if(str == "sign") {
 write("****************************************************\n"+
       "**                                                **\n"+
       "**  Welcome to The Blood Bank!                    **\n"+
       "**    Here you can swap some of your own life's   **\n"+
       "**    blood for cold hard cash.                   **\n"+
       "**  The Rates Here Are:                           **\n"+
       "**    Blood(hp/sp)     Cash Recieved              **\n"+
       "**  PINT <50/50>     500 coins                    **\n"+
       "**  QUART <100/100>  1000 coins                   **\n"+
       "** GALLON <200/200>  3000 coins                   **\n"+
       "**           To Give Blood Type: Donate (volume)  **\n"+
       "**                                                **\n"+
       "**     Corpse Selling:                            **\n"+
       "**      Bring corpses here to sell for money.     **\n"+
       "**      You can get anywhere's from 50 to 100     **\n"+
       "**      coins for a suitable body.                **\n"+
       "**      (please, dead bodies only!, make sure     **\n"+
       "**      aren't just sleeping!!!)                  **\n"+
       "**                                                **\n"+
       "****************************************************\n\n\n");
   return 1;
   }
}
rejected() {
  write("Halfway through the process the nurse suddenly realizes\n"+
   "you don't have enough blood to make this kind of donation!\n"+
   "The nurse watches in terror as all your life's fluids are \n"+
   "drained from your body!  Your dried out husk falls to the ground.\n"+
   " Then, a big burly man comes and picks you up.  With one swing\n"+
   "of his heavy steeltoed boots he kicks you out the door.\n"+
   "The man yells: Donna maka promises you cannata keep!\n");
        this_player()->add_hit_point(-HP);
        command("north", this_player());
        }