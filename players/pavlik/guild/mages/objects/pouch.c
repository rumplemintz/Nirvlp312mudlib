inherit "/obj/treasure";

#include <ansi.h>
#include "../defs.h"
#include "/players/pavlik/guild/mages/include/spell_costs.h"

#define TP this_player()

#if 0
#endif
mapping comp_info;

reset(arg)
{
  if(arg) return;
  
  set_id("mage's component pouch");
  set_alias("component pouch");
  SetMultipleIds(({"pouch", "mage component pouch"}));
  set_short(HIM+"A mage's component pouch"+NORM);
  set_long("\
A large pocket which can hold a variety of spell components\n\
and trinkets.\n");
  set_weight(1);
  set_value(750);

  comp_info = ([ 
    "leather cord"         : ({ 1, 50, "A leather cord", "A leather cord.\n", ({ "cord", "leather" }), })
   ,"gemstone"             : ({ 1, 600, "A Gemstone", "A small semi-precious gemstone.\n", ({ "gem_stone" }), }) 
   ,SUMMON_COMPONENT_ID    : ({ 0, 0, "Null", "Not used\n", ({ "heart", "stone" }), })
   ,ACID_COMPONENT_ID      : ({ 1, 500, "Sulfur Powder (1 pinch)", "A pinch of sulfur powder.\n", ({ "sulfur", "powder", "sulfur powder", }), })
   ,SDAGGER_COMPONENT_ID   : ({ 0, 50, "A Silver Needle", "A Silver Needle.\n", ({ "needle", "silver needle", }), })
   ,ESHIELD_COMPONENT_ID   : ({ 0, 500, "A bit of Onyx Powder", "Two teaspoons of Onyx Powder.\n", ({"powder", "onyx powder", "onyx powder", }), })
   ,MIMAGE_COMPONENT_ID    : ({ 1, 5000, "A Platinum Mirror", "A tiny sheet of platinum.\nIt is shiny enough to be a mirror.\n", ({"mirror", "platinum mirror", }), })
   ,"tespian orb"          : ({ 0, 150, "A Tespian Orb", "A sphere of fagile tespian glass.\n", ({ "orb", }), })
   ,"amber rod"            : ({ 0, 500, "An Amber Rod", "A rod of golden amber.\n", ({ "rod", }), })
   ,STONESKIN_COMPONENT_ID : ({ 0, 650, "Granite Powder", "A pile of granite powder.\n", ({"powder", "granite powder", }), })
   ,"spider"               : ({ 1, 500, "Spider", "A tiny black spider.\n", ({ "black spider", }), })
   ,"orb of souls"         : ({ 1, 300, "Orb of Souls", "A chromatic, clear orb.\n", ({ "orb", }), })
   ,"light feather"        : ({ 0, 500, "Light feather", "A light feather.\n", ({ "feather", }), })
  ]);
}

init()
{
  add_action("cmd_pouch","pouch");
  add_action("cmd_unpouch","unpouch");
}

long()
{
  write("\n");
  if( guild )
    command("components", TP ); 
  write("\n");
  write("You can \"pouch\" or \"unpouch\" components.\n");
}
  

cmd_pouch(str)
{
  object obj;
  if(!str)
  {
    write("pouch what?\n");
    return 1;
  }
  if(!(obj=present(str, TP))){
    write("You don't have \""+str+"\"\n");
    return 1;
  }

  if( member( COMPONENT_IDS, obj->query_name() ) < 0 ) {
      write(str + " is not a valid component.\n");
      return 1;
  }

  do_pouch( obj );
  write("You pouch \""+obj->short()+"\"\n");
  destruct(obj);
  return 1;

}

do_pouch(object obj) {

  if( !obj )
    return;
 
  TP->add_weight(-(obj->query_weight()));
  if( guild ) {
    guild->add_component( obj->query_name() );
  }

}

clone_component( string comp_name ) {
  object obj;

  if(!guild || !guild->query_component( comp_name ) || !comp_info[ comp_name ] ) 
    return 0;

  if( comp_name == SUMMON_COMPONENT_ID ) {
    obj = clone_object( OBJ_DIR + "heartstone" );
  }
  else {
    obj = clone_object( "obj/treasure" );
    obj->set_id( comp_name );
    obj->set_weight( comp_info[ comp_name ][0] );
    obj->set_value( comp_info[ comp_name ][1] );
    obj->set_short( comp_info[ comp_name ][2] );
    obj->set_long( comp_info[ comp_name ][3] );
    obj->SetMultipleIds( comp_info[ comp_name ][4] );
  }

  return obj;  
}

cmd_unpouch(str)
{
  string comp_name;
  string *comps;
  object obj;
  int x;

  if(!str)
  {
    write("unpouch what?\n");
    return 1;
  }
  
  /** check if the component is in the info mapping **/
  if( !comp_info[ str ] ) {
    /** player did not select the id of the object **/
    comps = m_indices( guild->query_components() );
    x = sizeof(comps);    
    while( x-- ) {

      /** Make sure the comp info is in sync with the components stored in the guild obj **/
      if( !comp_info[ comps[x] ] )
        continue;

      /** Secondary search 
          Checking the multiple ids set in the comp info mapping to see if str is a match **/
      if( member( comp_info[ comps[x] ][4], str ) >= 0 ) {
        if( guild && guild->query_component( comps[x] ) ) {
          comp_name = comps[x];
          break;
        }
      }
    }
  }
  else
    comp_name = str;

  if( !comp_name || !guild || !guild->query_component( comp_name ) ){
    write("You don't have \""+str+"\" in the pouch.\n");
    return 1;
  }
  
  obj = clone_component( comp_name );
  
  if(!TP->add_weight(obj->query_weight())) {
    write("You can't carry anymore.\n");
    destruct( obj );
    return 1;
  }
  move_object(obj, TP);
  
  if( guild ) {
    guild->add_component( obj->query_name(), -1 );
  }
  write("You unpouch \""+obj->short()+"\"\n");
  return 1;
}

