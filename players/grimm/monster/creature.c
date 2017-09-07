inherit "obj/monster.talk";
object coins, move, battery;
reset(arg) {
::reset(arg);
if(arg) return;
set_level(7);
set_hp(100);
set_name("creature");
set_short("A Little Bug-eyed Creature");
set_long("This creature is definitely the homliest creature you have ever\n"+
"seen.\n");
set_whimpy(75);
set_ac(2);
battery = clone_object("players/grimm/object/battery");
move_object(battery,this_object());
coins = clone_object("obj/money");
coins->set_money(10+(random(20)));
move_object(coins,this_object());
random_move();
}
random_move() {
move = random(7);
if (move == 0)
   command("north");
else if (move == 1)
   command("south");
else if (move == 2)
   command("east");
else if (move == 3)
   command("west");
else if (move == 4)
   command("northeast");
else if (move == 5)
   command("southeast");
else if (move == 6)
   command("southwest");
else if (move == 7)
   command("northwest");
call_out("random_move",1);
}