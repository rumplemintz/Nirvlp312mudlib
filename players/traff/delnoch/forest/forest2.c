/*
  I'm still working on this.  It is a LONG way from done.
  It is not well commented yet, but I'm starting to add
  comments.  While I plan to add quite a bit more to this
  file, what is here now, does work and has been tested.
   2-29-00
   Getting closer to being done.  Still need to code items for
   the monsters, and want to try and add some movement to the
   monsters.
*/
#include "/players/traff/closed/ansi.h"
#define FR "/players/traff/delnoch/forest/"
inherit "room/room";
string fr,fc;
int m,mc,r,path,trail;

reset(arg){
  if(!arg){

  set_light(1);
  long_desc=(GRN+
"The forest quickly surrounds you.  It is hard to see very far\n"+
"because of the thick growth.  You can hear sounds from the\n"+
"town of Delnoch nearby, but even now you are not quite sure\n"+
"which direction would take you back there.  Occasionaly you\n"+
"glimpse some movement out of the corner of your eye, but\n"+
"you're not quite sure whether it is caused by a breeze in\n"+
"the leaves, or some small creature moving along quietly.\n"+
"\n"+NORM);

items=({
"ground","What you can see of the ground is covered with pine needles",
"trees","Mostly conifers, they are tall and green",
"leaves","There are a lot of leafy plants here, as well as trees",
"growth","Vines, weeds, and other plants grow among the trees",
"mountains","The mountains rise steadily to the north.  You see snow capped peaks",
 });

  dest_dir=({
"/players/traff/delnoch/work/forest1.c","north",
"/players/traff/delnoch/work/forest1.c","south",
"/players/traff/delnoch/work/forest1.c","east",
"/players/traff/delnoch/work/forest1.c","west",
      });
  }   }

short() { return HIG+"Skoda Forest"+NORM;}

init()  {
 ::init();
  add_action("roam","north");
  add_action("roam","south");
  add_action("roam","east");
  add_action("roam","west");
  add_action("flee","flee");
/* Change path to trail in odd number rooms */
  add_action("path","path");
  add_action("search","search");
  add_action("count","count");
  add_action("boo","boo");
}

realm() { return "NT"; }

roam()  {
  object ob;

/* Assign rooms to the string fr[n] */
    if(!fr) {
      fr = allocate(10);
      fr[0]=FR+"forest2.c";
      fr[1]=FR+"forest3.c";
      fr[2]=FR+"forest4.c";
      fr[3]=FR+"forest5.c";
      fr[4]=FR+"forest6.c";
      fr[5]=FR+"forest7.c";
      fr[6]=FR+"forest8.c";
      fr[7]=FR+"forest9.c";
      fr[8]=FR+"forest10.c";
      fr[9]=FR+"forest11.c";
    }

/* Assign critters to the string fc[n] */
    if(!fc) {
      fc = allocate(10);
      fc[0]="fc0.c";
      fc[1]="fc1.c";
      fc[2]="fc2.c";
      fc[3]="fc3.c";
      fc[4]="fc4.c";
      fc[5]="fc5.c";
      fc[6]="fc6.c";
      fc[7]="fc7.c";
      fc[8]="fc8.c";
      fc[9]="fc9.c";
    }
  r = random(10);
/* Move the player to a random location */
  call_other(this_player(),"move_player","through the trees#"+fr[r]);
/* This checks for players.  It keeps monster movement from
   creating more monsters. I could take it out! heh */
    if(!(this_player()->is_player())) { return 1; }
  path = 0;
  m += 1;
/* The monster count, mc, is not working quite the way I want.
   I may take it out, or add a sub-routine to count mobs */
  mc += 1;
/* I put in the m<21 more as a safety than anything else.  I don't
   think it will be needed, but no doubt without it some fool would
   come in and run around til he died, just to see how many he could
   make! */
    if (m < 21) {
      r = random(10);
/* The write_file is probably temp.  It helped me see what was
   happening during testing.  There is a similar line in the
   monsters that writes when they die.  This will also help
   when the area is put into play to see how much use it is
   getting, and if adjustments need to be made. */
      write_file("/players/traff/delnoch/forest/critc",ctime()+" fc"+r+".c Cloned\n");
/* This clones a random monster.  The files are ~/delnoch/mon/
   fc0.c - fc9.c  Monsters range in level from 8-17.  Overall there
   is about a 58% chance they will be aggressive with the higher
   levels more likely aggressive than lower levels.  There is about
   a 42% chance that monsters will be wimpy, with the lower
   levels being more likely to wimpy. */
      move_object(clone_object("/players/traff/delnoch/mon/"+fc[r]),this_object());
/* This is to give some 'movement' to the critters */
      r=random(10);
      ob=present("critter");
      move_object(ob,fr[r]);
      say("An animal leaves through the trees.\n");
      return 1;}
  return 1;
         }

/* this will let low levels 'flee' back to the starting room */
flee() {
  if(this_player()->query_level()<6) {
    call_other(this_player(),"move_player","running wildly#"+FR+"forest1.c");
    path = 0;
    return 1; }
  write("You can't do that!\n");
  return 1; }

/* players that search will find a path in even numbered rooms
   and a trail in odd numbered rooms.  Movement along path or
   trail does NOT create monsters and moves the player in an
   orderly fasion by twos.  Path leads out, trail leads in. */
path() {
  if(!path) {
    write("What?\n");
    return 1; }
  path = 0 ;
  write("You move off, down the path.\n");
  call_other(this_player(),"move_player","down a path#"+FR+"forest1.c");
  return 1; }

/* the search could be made harder as is any search other than empty
   will find the path or trail */
search(str)  {

  if(!str)  {
    write("Search what?\n");
    return 1;  }
   
  path = 1;
  write("You search the "+str+" and find a path.\n");
  write("Perhaps the 'path' leads somewhere.\n");
  return 1;  }

/* This was for testing and didn't work exactly as expected */
count() {
  write("Monsters cloned = "+mc+" Current = "+m+"\n");
  return 1; }

/* This is pretty useless, but may incorporate it in a count
   sub-routine */
dead_mon() {
  m -= 1;
  return 1; }
/********************************/
boo() {
  object ob;
  r=random(10);
  ob=present("critter");
  if(!ob) {write("No critters here!\n"); return 1;}
  command("north",ob);
/*
  move_object(ob,fr[r]);
*/
  say("An animal leaves through the trees.\n");
  write("An animal leaves through the trees.\n");
  return 1; }