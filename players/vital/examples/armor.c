/******************************************************************************
 *  File:           armor.c
 *  Author(s):      Vital@Nirvana
 *  Copyright:      Copyright (c) 1997 Vital@Nirvana
 *                  All Rights Reserved.
 *  Source:			Started 1/4/01.
 *  Notes:			
 *  Change History: 
 *****************************************************************************/

inherit "obj/armor";

reset(arg)
{
   if(arg) return;
   ::reset(arg);
   set_name("armor");
   set_alias("an armor");
   set_short("An Armor");
   set_long("This is an utterly simple armor.\n");
   set_ac(5);
   set_type("armor");  /* armor,helmet,boots,ring,amulet,shield,misc  */
   set_weight(1);
   set_value(0);
}
