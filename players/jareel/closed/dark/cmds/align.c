#include "/players/pestilence/ansi.h"

main(str) 
{

   object victim;
   string tmpaln;
   int tmpal;
   tmpal = this_player()->query_alignment();
   if (!str) {
      write("Your alignment is --> "+ aln(tmpal) + " <--\n");
      return 1;
   }
   victim = present(str, environment(this_player()));
   if (!victim) {
      write("That is not here.\n");
      return 1;
   }
   if (!living(victim)) {
      write("You can't do that!\n");
      return 1;
   }
   tmpal = victim->query_alignment();
   write(capitalize(str) + "'s alignment is --> "+ HIY + aln(tmpal) + NORM+" <--\n");
   return 1;
}

aln(arg) {
if (arg > 10 * 64) {
        return "white lord";
    }
    if (arg > 10 * 32) {
        return "paladin";
    }
    if (arg > 10 * 16) {
        return "crusader";
    }
    if (arg > 10 * 8) {
        return "good";
    }
    if (arg > 10 * 4) {
        return "honorable";
    }
    if (arg > - 10 * 4) {
        return "neutral";
    }
    if (arg > - 10 * 8) {
        return "malicious";
    }
    if (arg > - 10 * 16) {
        return "evil";
    }
    if (arg > - 10 * 32) {
        return "infamous";
    }
    if (arg > - 10 * 64) {
        return "black knight";
    }
    return "lord of evil";
}
