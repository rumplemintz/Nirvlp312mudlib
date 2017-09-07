/*
 * Standard Load/Update cmd by V [7.8.01]
 * Also catches a load error and shows the log
 *
 * Updated by Illarion:
 * tails the proper log for other dirs
 * doesn't delete the log if it's another wizard's
 * doesn't try to load a file the wizard can't read
 * resolves .. and ~wizardname format
 *
 * if it breaks, replace it with _mk.bak
 *
 */

#include "/obj/user/load_object.h"
#include "/obj/user/resolve_path.h"
#include "/sys/temp.h"

status
cmd_mk(string arg)
{

  if (LDMUD_RUNNING)
    return (int)"/bin/wiz/_mk2.c"->cmd_mk2(arg);
    if((int)this_player()->query_level() < 21)
      return 0;

    if(!arg)
    {
      write("Mk what?\n");
      return 1;
    }

    else
    {
      object ob;

      if(arg=="here") arg=basename(environment(this_player()))+".c";
      if(!(arg = resolv_path(this_player()->get_path(), arg)))
      {
        write("Bad path error.\n");
        return 1;
      }
#ifndef __LDMUD__ /* Rumplemintz */
      if(arg[-2..-1]!="\.c")
#else
      if (arg[<2..<1] != "\.c")
#endif
        arg+=".c";

      write("Making " + arg + "...\n");

      if(ob = find_object(arg))
      {
        write("Object found.\n");
        write("Updating old copy... ");
  if(ob==environment(this_player())) {
  "/bin/wiz/_goback"->set_room((string)this_player()->query_real_name(), basename(ob));
  }
        destruct(ob);
        write("Ok\n");
      }

      else
        write("No object found.\n");

      if(file_size(arg) < 0)
      {
        write("File does not exist.  Unable to attempt load.\n");
        return 1;
      }              
      
      write("Loading new copy... ");
      
      if(!(ob = loadObject(arg)))
      {
        string me;
        string logfile;
        if(sscanf(arg,"/players/%s/%s",me,logfile)==2)
          logfile="/log/"+me;
        else
          logfile="/debug.log";

        write("Load aborted.\n");

        if(file_size(logfile) > 0)
        {
          write("Error found.\n");
          tail(logfile);
          if(me==(string)this_player()->query_real_name())
            command("rlog " + me, this_player());
          else
            write("Log not deleted...  it's not yours.\n");
        }

        else
        {
          write("No log file found for "+me+"!\n");
          tail("/lpmud.log");
        }
        return 1;
      }

      else
        write("Success!\n");

      return 1;
    }
}