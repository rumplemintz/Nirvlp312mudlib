#include "../defs.h"

status main(string arg) {

  if (!arg) {
    if (file_size(EXEC) > 1) {
      destruct(EXEC);
      rm(EXEC);
      write("Exec file deleted.\n");
      return 1;
    }

    notify_fail("What is it you wish to execute?\n");
    return 0;
  }

  write_file(EXEC, "#include \"../defs.h\"" + 
    "\nint main(status arg) {" + arg + "; return 1; }");
  write("Done.\n");
  clone_object(EXEC);
  EXEC->main(0);
  destruct(EXEC);
  rm(EXEC);
  return 1;
}
