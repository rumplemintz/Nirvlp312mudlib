/*                                       
 *  File:   /players/mosobp/areas/BATTLE/NPC/krillen.c
 *  Function:  mob                      
 *  Author(s):  Mosobp@Nirvana           
 *  Copyright: copyright (c) 2008 Mosobp 
 *             all rights reserved          
 *                                       
 *                                       
 *  Source:  6/17/08                    
 *  Notes:                               
 *                                       
 *                                       
 *  Change History:                      
 */

#include "/sys/lib.h"

#include <ansi.h>

inherit "/obj/monster";

reset(arg)
{
  object gold;
  ::reset(arg);
  if(arg) return;
  set_name("King Vegeta");
  SetMultipleIds(({"king","vegeta"}));
  set_short(HIK+"King Vegeta"+NORM);
  set_race("saiyan");
  set_long(
  "King Vegeta, The King of all Saiyans. He is the father of Prince Vegeta."+
  "He was also the commanding hero of the Saiyan Army during the Tuffle war.\n");
  set_level(25);
  set_hp(1800+random(550));
  set_al(0);
  gold=clone_object("obj/money");
  gold->set_money(random(2000)+10000);
  set_wc(50);
  set_ac(18);
  set_heal(45,8);
  set_multi_cast(1);
  add_spell("kivolley",
    "A volley of "+HIM+"E N E R G Y  B L A S T S"+NORM+" scream toward you hitting you!\n",
    "#MN# releases a rapid "+HIM+"Barrage"+NORM+"of energy blasts!.\n",
    30,"100-120","other|energy");
  add_spell("executionbeam",
    "A Bright "+HIM+"Execution Beam "+NORM+"of light fly's toward you hitting your chest!\n",
    "#MN# fires an "+HIM+"Execution Beam"+NORM+"towards his opponent!\n",
    20,"130-170","other|energy");
  add_spell("orga_blaster",
	"#MN# rushes you,knocks you off balance, and a "+HIM+"LARGE WAVE"+NORM+" knocks you into another room!\n",
	"#MN# rushes #TP# knocking them aside "+HIY+"KNEES"+NORM+"then he "+HIM+"BLASTS"+NORM+" them into another room\n",
	10,"150","other|energy");
}

roundhouse_kick( object target, object room, int damage ) {
  /** Code borrowed from Zeus' Ani **/
  int ran1, i;
  string str;
  object wall;
  string *the_dirs;
  
  if( room && target && damage - target->query_attrib( "str" ) > 110  ) {
    wall = present( "clan_wall_blocker_obj" );
    
    the_dirs = (room->query_dest_dir());
    ran1 = random(sizeof(the_dirs)-1);
    i = ran1 / 2 * 2;
    str = the_dirs[i+1];
    str += "#";
    str += the_dirs[i];
    tell_room( room, "\n\n\n\n"+target->query_name()+" tries to recover but the force of the blow knocks them out of the room!\n" );
    
    if( wall ) {
      destruct( wall );
      tell_room( room, target->query_name()+" flies right through the wall shattering it to pieces!\n" );
      target->hit_player( 50 + random(50) - target->query_attrib( "luc") );
    }
    
    target->move_player(str);
    command( "look", target );
  }
}