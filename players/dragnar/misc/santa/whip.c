inherit "obj/weapon";

#include <ansi.h>

reset(arg) {
  ::reset(arg);
  if(arg) return;

  set_name("whip");
  set_class(17);
  set_weight(2);
  set_type("whip");
 
  set_value( 1800 );
  SetMultipleIds( ({ "glock pistol", "walkerobj" }) );
  
  set_short( HIBLK+"Reindeer Whip"+NORM );
  set_long( "This whip is the only way Santa can keep his reindeer in order. You\n\
know how much of a jerk Blitzen can be? Imagine him without Santa's\n\
whip. Also, is that elf blood on it?\n");
  set_params("physical", 5);
  
}

wield(string str)
{
  if(id(str) && present(this_object(), this_player()) &&
    this_player()->query_weapon() == this_object()){
    ::wield(str);
    return 1;
  }
  ::wield(str);
  if(id(str))
  {
    if(!present(this_object(), this_player())) return 0;
    if(this_player()->is_npc()) return 0;
    if( this_player()->query_real_name() != "santa" ) {
      set_class(10);
      write("You almost hit yourself in the eye with the whip!\n");
    }
    else {
      write("You crack the whip with a practiced flick of your strong wrist.\n");
      say(capitalize(this_player()->query_name())+" cracks the whip with loud S N A P!\n");
    }

    return 1;
  }
}

query_wear() {
  return 1;
}

weapon_breaks() {
  return 1;
}

