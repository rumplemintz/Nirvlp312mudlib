#include <ansi.h>

#define RESULT "" +\
YEL + "                        .::::::::::::::::::::::::::::::`\n" +\
"                        :" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "N\n" +\
"                         N" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "y\n" +\
"                         y" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "/\n" +\
"                         /" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "`\n" +\
"                         `" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "d\n" +\
"                          h" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "o\n" +\
"                          `````o" + RED + "MMMMMMMMMMMMMMMM" + YEL + "-````\n" +\
"                             `.o" + RED + "MMMMMMMMMMMMMMMM" + YEL + ":.`\n" +\
"                   `-/+ooooo++/:-/" + RED + "MMM" + YEL + ":````:" + RED + "MMM" + YEL + ":::/+oooooo+/-`\n" +\
"             -/+yms/:.     ./++  /" + RED + "MM" + YEL + "s  o-  o" + RED + "MM" + YEL + "-  ++/.     .:/smso/-\n" +\
"        -++++:` hM:  sym/  +yod++h" + RED + "M" + YEL + "m` -" + RED + "M" + YEL + "d   m" + RED + "M" + YEL + "y++m+h/  +dys  /Mo .:+oo+-`\n" +\
"     /++- `:+   mhs/+d+h/  +y.-o" + RED + "MMM" + YEL + "-  d" + RED + "MM" + YEL + "o  -" + RED + "MMM" + YEL + ":-.y/  +sod+:syod  `-``:+oo/`\n" +\
"   `s. .ssooNosso-/-`  h/  +y  +" + RED + "MM" + YEL + "s  +" + RED + "MMMM" + YEL + ".  o" + RED + "MM" + YEL + "/  y/  +s  `-/:om  -mooo+` /d\n" +\
"   y-  s+ .oyooss.     h/  +y  +" + RED + "M" + YEL + "m  .d.       .+m  y/  +s     `N-  .d/- m. /y\n" +\
"   h.  /s+:.    /y     h/  +y  +" + RED + "M" + YEL + "-  h" + RED + "MM" + YEL + "NNNm/  `mo  y/  +s      ho    `:mhooyo\n" +\
"   h-   `:osh-  :h    :d/  :smm+:  /" + RED + "MMMMMMM" + YEL + "m`  :+dds-  +h:     .m  .do+N.  -.\n" +\
"   :hysyy-` y:  :y   :h`  `.-hN+ossN" + RED + "MMMMMMMM" + YEL + "hsoo+my-.`  `h-   :sm  -d `-:.\n" +\
"   `/++hy:++o` .h-   shsso+/:-.o" + RED + "MMMMMMMMMMMMMMMM" + YEL + ":.-:/+oooho   s+`  .ho:`ysoo/\n" +\
"   y/  :/. `:+so`              +" + RED + "MMMMMMMMMMMMMMMM" + YEL + ".             /ooo+:` ./s: -h\n" +\
"   d. `:oss+:`            `....o" + RED + "MMMMMMMMMMMMMMMM" + YEL + ":....`            `:+ooo:` `m\n" +\
"   Nsso-`                 d" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "o                 `-+ooN\n" +\
"   .                     `" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "d                      .\n" +\
"                         /" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "`\n" +\
"                         y" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "/\n" +\
"                         N" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "y\n" +\
"                        :" + RED + "MMMMMMMMMMMMMMMMMMMMMMMMMMMMM" + YEL + "N\n" +\
"                        .::::::::::::::::::::::::::::::`\n" +\
"\n" + OFF

int risu2(string str) {
  object *p;
  int x;

  if (!str) {
    notify_fail("Usage: risu <who>\n");
    return 0;
  }

  if (str == "ALL" && (string)this_player()->query_real_name() == "rumplemintz") {
    x = sizeof(p = users());

    while(x --)
      if (p[x] && !p[x]->query_muffled() && !in_editor(p[x]))
        tell_object(p[x], "" + RESULT + "\nGO CYCLONES!!!\n");
    write("You just sent the ISU logo to everyone!\n");
    return 1;
  }
  
  else if (find_player(str)) {
    tell_object(find_player(str), "" + RESULT + "\nGO CYCLONES!!!\n");
    write("Sent the ISU logo to " + str + ".\n");
    return 1;
  }

  else {
    notify_fail("Cannot locate " + str + " currently.\n");
    return 0;
  }
}
