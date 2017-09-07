/*                                                                    *
 *    File:         /players/angel/area/mansion/obj/hirams_key.c      *
 *    Function:         OBJ                                           *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           02/7/17                                       *
 *    Notes:        The first piece to solve the Masonic Quest        *
 *                                                                    *
 *                                                                    *
 *    Change History:                                                 *
 */

inherit "obj/treasure";

reset(arg) {
 if(arg) return;
set_short("Hiram's key");
set_alias("key");
set_long("This is a brass skelenton key with an inscription on it.\n");
set_read("Hiram's key. It looks like it unlocks something.\n");
set_weight(1);
set_value(0);
set_save_flag(1);
}
id(str) { return str == "hiram's key" || str == "key"; }