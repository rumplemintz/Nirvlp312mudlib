/*                                                                    *
 *    File:         /players/angel/area/mansion/obj/swatter.c         *
 *    Function:         OBJ                                           *
 *    Author(s):        Angel@Nirvana                                 *
 *    Copyright:        Copyright (c) 2017 Angel                      *
 *                              All Rights Reserved.                  *
 *    Source:           02/7/17                                       *
 *    Notes:       Decorative, mabe at some point I will code it to   *
 *                            kill the fly                            *
 *                                                                    *
 *    Change History:                                                 *
 */

#include <ansi.h>

inherit "obj/weapon.c";

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_name("Fly Swatter");
  set_alias("swatter");
  set_type("sword");
  set_short("Fly Swatter");
  set_long(" It looks like a net but sterdy and has many uses. It can\n\
kill flies by hitting them, it can get stuff under the refrigerator\n\
and it can also be used to 'swat' people.\n");
  set_class(1);
  set_weight(1);
  set_value(50);

}

init()
{
    ::init();
    add_action("swat", "swat");
}

swat(arg)
{
    object target;
    if(!arg) return 0;

    target = present(arg, environment(this_player()));
    if(!target)
    {
        write("Swat who?\n");
        return 1;
    }

    if(!living(target))
    {
        write("It was made to 'Swat' people!\n");
        return 1;
    }

    write("You smack " + target->query_name() + " with a Fly Swatter!\n");
    say(target->query_name() + " was smacked up side the head with a Fly Swatter!\n");
    return 1;
}
