#include <ansi.h>

string RESULT;

RESULT = "";
RESULT += YEL + "                        .::::::::::::::::::::::::::::::`";
RESULT += "                        :" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "N";
RESULT += "                         N" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "y";
RESULT += "                         y" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "/";
RESULT += "                         /" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "`";
RESULT += "                         `" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "d";
RESULT += "                          h" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "o";
RESULT += "                          `````o" + RED + "MMMMMMMMMMMMMMMM" + YEL + "-````";
RESULT += "                             `.o" + "MMMMMMMMMMMMMMMM" + YEL + ":.`";
RESULT += "                   `-/+ooooo++/:-/" + RED + "MMM" + YEL + ":````:" + RED + "MMM" + YEL + ":::/+oooooo+/-`";
RESULT += "             -/+yms/:.     ./++  /" + RED + "MM" + YEL + "s  o-  o" + RED + "MM" + YEL + "-  ++/.     .:/smso/-";
RESULT += "        -++++:` hM:  sym/  +yod++h" + RED + "M" + YEL + "m` -" + RED + "M" + YEL + "d   m" + RED + "M" + YEL + "y++m+h/  +dys  /" + RED + "M" + YEL + "o .:+oo+-`";
RESULT += "     /++- `:+   mhs/+d+h/  +y.-o" + RED + "MMM" + YEL + "-  d" + RED + "MM" + YEL + "o  -" + RED + "MMM" + YEL + ":-.y/  +sod+:syod  `-``:+oo/`";
RESULT += "   `s. .ssooNosso-/-`  h/  +y  +" + RED + "MM" + YEL + "s  +" + REC + "MMMM" + YEL + ".  o" + RED + "MM" + YEL + "/  y/  +s  `-/:om  -mooo+` /d";
RESULT += "   y-  s+ .oyooss.     h/  +y  +" + RED + "M" + YEL + "m  .d.       .+m  y/  +s     `N-  .d/- m. /y";
RESULT += "   h.  /s+:.    /y     h/  +y  +" + RED + "M" + YEL + "-  h" + RED + "MM" + YEL + "NNNm/  `mo  y/  +s      ho    `:mhooyo";
RESULT += "   h-   `:osh-  :h    :d/  :smm+:  /" + RED + "MMMMMMM" + YEL + "m`  :+dds-  +h:     .m  .do+N.  -.";
RESULT += "   :hysyy-` y:  :y   :h`  `.-hN+ossN" + RED + "MMMMMMMM" + YEL + "hsoo+my-.`  `h-   :sm  -d `-:.";
RESULT += "   `/++hy:++o` .h-   shsso+/:-.o" + RED + "MMMMMMMMMMMMMMMM" + YEL + ":.-:/+oooho   s+`  .ho:`ysoo/";
RESULT += "   y/  :/. `:+so`              +" + RED + "MMMMMMMMMMMMMMMM" + YEL + ".             /ooo+:` ./s: -h";
RESULT += "   d. `:oss+:`            `....o" + RED + "MMMMMMMMMMMMMMMM" + YEL + ":....`            `:+ooo:` `m";
RESULT += "   Nsso-`                 d" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "o                 `-+ooN";
RESULT += "   .                     `" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "d                      .";
RESULT += "                         /" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "`";
RESULT += "                         y" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "/";
RESULT += "                         N" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "y";
RESULT += "                        :" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "N";
RESULT += "                        .::::::::::::::::::::::::::::::`";
RESULT += OFF;

int risu(string str) {
  if (!str) {
    notify_fail("Usage: risu <who>\n");
    return 0;
  }

  if (!find_player(str)) {
    notify_fail("Cannot locate " + str + " currently.\n");
    return 0;
  }

  tell_object(find_player(str), RESULT + "\n\nGo CYCLONES!\n");
  return 1;
}
