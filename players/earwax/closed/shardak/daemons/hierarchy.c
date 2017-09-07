/* *********************************************************************
 * /players/earwax/closed/shardak/daemons/hierarchy.c
 *
 * Shardak Hierarchy Daemon
 * Automatically generates guild member lists and guild hierarchy list
 *
 * Coded by Earwax (sometimes known as David Halek) 7/22/03
 * 
 * Overcommenting also by Earwax, to use as a teaching tool :)
 *
 * *********************************************************************
 *
 * Note: The formatting I use in here, how the comments are, the spacing
 * and indentation, and the way the functions are declared, are not,
 * strictly speaking exact, but they are pretty much the accepted way 
 * for dealing in LPC.  The actual correct way, is how Vertebraker does
 * it in a lot of his code...
 *
 * void
 * reset(status arg) 
 * {
 *
 * And so on.  He indents 4 spaces for commands the first indent level,
 * and 2 after, generally, I just indent 2, it's readable easily, and
 * you can generally tell your indent level by looking at it, it's mainly
 * for working with real coding, where you have more than 78 or 80 
 * columns to work with, where you want to indent 5 and 3, or 5 and 5.
 * I condense it, as I imagine other coders do, for density.
 *
 * The commenting before functions, however, is something that's a good
 * habit to get in.  Before each function (for non room/mob/item files)
 * (and even within the more complex ones), you should have a comment
 * section that says the function name and what the function does.  That
 * way, anyone who looks at your code later to make changes, fix bugs,
 * update, or whatever, can more easily navigate your code and find
 * things.  At the top, you should also say the name of the file, what
 * it does, and your name, as well as have a revision history showing
 * date modified, and what was changed, as well as comment revisions
 * where you actually change things.
 *
 * *********************************************************************
 *
 * Also note: this is a daemon.  What daemons are used for are is
 * automating things, like channels, that are done repeatedly.  The code
 * this way is only loaded once, and only in one place, so it prevents
 * having the same exact code in five or more different places.  In
 * other words, I could have this code (probably some wizards put 
 * similar code) in guild objects, but then all this code would be in
 * every shardak guild object, so instead, I stick it here, and have the
 * commands reference it.  That way, all this code only has to be 
 * compiled once.  If you're doing something that's going to go into
 * multiple objects, you probably want to consider doing either an
 * inheritable for it, or, preferably usually, a daemon.  On some muds,
 * even combat is ran by daemons.
 *
 * *********************************************************************
*/

#include "../include/def.h" 
#include "../include/ansi.h"

inherit WAXFUNS;         /* ANSI color formatting functions           */
                         /* lalign(), ralign(), center() from there   */

/* Global Variables */   /* normally all globals are capitalized      */
mapping Members;         /* all members, format ([ member : rank ])   */
string *Indices,         /* indexes, mappings don't save correctly :( */
       *Values,          /* values, see above hehe                    */
       *Ranks,           /* Ranks to show in hierarchy                */
       *Testchars;       /* Test Chars to filter out                  */

/* *********************************************************************
 * reset()
 * 
 * This is the function called when this object (this code) is loaded.
 * In here, we have to initialize the variables, load the information
 * from a save file, and then convert the arrays into a mapping.
 * Using a mapping because they are way easier to work with for this
 * than using two arrays would be, but they don't save properly, so we
 * need the arrays as well.
*/

void reset(status arg) {

  int i, siz;

  if (arg)
    return;

  /* Initialize Variables */
  /* If there's no file to restore, everything else will hose */
  Members = ([ ]);
  Indices = ({ }); Values = ({ });

  /* Load the stored information from HIERARCHY_SAVE */
  restore_object(HIERARCHY_SAVE);
  Ranks = ({ "high Magus", "magus","master","magistrate","warlord","law", "berzerkers" });
  Testchars = ({ "waxman", "moso", "linusjr", "numberone", "numbertwo", "numberthree", "numberfour", "numberfive" });


  /* Goddamn ghetto-rigged mappings don't save in this lib */
  /* so have to convert arrays to mappings and back        */

  siz = sizeof(Indices);

  for (i = 0; i < siz; i++)  {
    Members += ([ Indices[i] : Values[i] ]);
  }
}

/* *********************************************************************
 * save_info()
 * 
 * This function saves the info.  It converts the mapping back into two
 * arrays, and then does save_object()
*/

void save_info() {

  Indices = m_indices(Members);
  Values = m_values(Members);
  save_object(HIERARCHY_SAVE);
}

/* *********************************************************************
 * add_member()
 * 
 * This function is called by the joinroom or from the guild object when
 * it is placed on a player.  Adds a member to the mapping of members,
 * and then saves it, so in case of a crash, no data is lost.
*/

void add_member(string name, string rank) {

  if (!name || !rank)
    return;

  if (member_array(name,Testchars) > -1)
    return;

  if (name == "earwax")
    return;

  if (member(Members,name)) {    /* Already a member, see if rank correct */

    if (Members[name] == "rank") /* Rank is the same, don't bother saving */
      return;                    

    Members[name] = rank;        /* Update rank and save */
    save_info();
    return;
  }

  Members += ([ name : rank ]);  /* Add the member to the mapping */
  save_info();
}

/* *********************************************************************
 * remove_member()
 * 
 * Called from 'abandon guild' at Shardak, this removes the member from 
 * the mapping, and then saves.
*/

void remove_member(string name) {

  /* Error checks...make sure a name was passed, and that it's a member 
   * These checks are necessary, would cause a 'senstive' mind message or
   * worse if they aren't there.                               
  */
  if (!name || !(member(Members,name)))
    return;

  /* This isn't the correct way to actually handle mappings, but this driver
   * doesn't do mappings the correct way.
  */
  Members = m_delete(Members,name);
  save_info();
}

/* *********************************************************************
 * change_rank()
 *
 * Called from gpromote command.  It's not really a necessary function,
 * it's here for the sake of efficiency.  Change their rank, save, and 
 * go.  This really should go into add_member(), but this is a little
 * faster since it assumes that the rank has been changed, so doesn't do 
 * the checks.  Works out, because gpromote does the checks for us.
*/

void change_rank(string name, string rank) {

  if (member_array(name,Testchars) > -1)
    return;

  if (name == "earwax")
    return;

  Members[name] = rank;
  save_info();
}

/* *********************************************************************
 * sort_ascending()
 *
 * sort_array() (an efun) needs a function to decide on how to sort.
 * So basically, you just put one of these together, nice and simple.
*/

status sort_ascending(string arg1,  string arg2) { return arg1 > arg2; }

/* *********************************************************************
 * dump_members()
 *
 * Format and return an output array of all members.  I did it this way
 * because if you try to use 'write' in a daemon, it simply won't work
 * every time, because there isn't necessarily a 'this_player().'
 * previous_object() could actually be used, but it's better to simply
 * return an array of the output.  That way, it can be called from 
 * anywhere, and even have the list itself dump itself to a file or a
 * log file, or whatever you may want to do.  More versatile this way,
 * although not the most efficient.
*/
string *dump_members() {

  string *names, *output;  /* I generally keep arrays and strings on */
  string info;             /* separate lines, for clarity            */
  int i, siz, pos;

  output = ({ });          /* Try to always initialize arrays        */
  names = m_indices(Members);
  names = sort_array(names, "sort_ascending");
  siz = sizeof(names);
  pos = 0;

  for (i = 0; i < siz; i++) {
    info = capitalize(names[i])+" "+NORM+RED+"("+HIK+capitalize(Members[names[i]])+NORM+NORM+NORM+RED+")"+NORM;

    switch(pos) {
      case 0 : output += ({ lalign(info,30) }); pos++; break;
      case 1 : output += ({ lalign(info,30) }); pos++; break;
      case 2 : output += ({ info + "\n" }); pos = 0; break;
    }
  }

  if (pos != 0)              /* If it's the last time through, add a */
    output += ({ "\n" });    /* carriage return, and get out */

  return output;            
}

/* *********************************************************************
 * return_rank()
 * 
 * Returns a sorted array of all members of rank 'rank'
 * Should be pretty easy to figure out how it works.
*/
string *return_rank(string rank) {

  string *temp;
  int i, siz;

  temp = ({ });
  siz = sizeof(Indices);

  for (i = 0; i < siz; i++) 
    if (Members[Indices[i]] == rank)
      temp += ({ Indices[i] });

  temp = sort_array(temp, "sort_ascending");
  return temp;
}

/* *********************************************************************
 * format_line()
 *
 * Format a line...add commas if appropriate, basically.
 * Called from dump_hierarchy()
 * Also converts the array into a string, to just slap in the output
*/

string format_line(string *peoples) {

  int i, siz;
  string temp;

  temp = ""; /* sometimes, you even initialize strings :) */
  siz = sizeof(peoples);

  if (!siz)         
    return HIK+"None"+NORM;

  if (siz == 1)
    return capitalize(peoples[0]);

  /* I haven't mentioned this yet, but you should always add a blank
   * line in between changes in indent levels, for readability.
   * Basically, indent before an if(), for(), while(), switch(), or
   * any other function that changes indent levels (uses {}).
  */
  for (i = 0; i < siz; i++) {

    if (i + 1 < siz)
      temp +=  capitalize(peoples[i]) + ", " ;
    else
      temp +=  capitalize(peoples[i]) ;
  }

  return temp;
}
  
/* *********************************************************************
 * dump_hierarchy()
 *
 * Returns an output array of the guild hierarchy.
 * Basically, in order, it calls return rank, formats what it gets
 * and returns all that.
*/

string *dump_hierarchy() {

  string *output;
  int i, siz;

  output = ({ });           /* ALWAYS initialize arrays and mappings */

  /* Do the header and so on */
  output += ({ center(HIK+"**[====>"+NORM+RED+" Shardak Hierarchy "+HIK+"<====]**"+NORM+"\n\n",50) });

  /* Now, get the information and add it to the output */
  siz = sizeof(Ranks);

  for (i = 0; i < siz; i++) {
    output += ({ HIK+"*~*  "+NORM });
    output += ({ lalign(HIR+capitalize(Ranks[i])+":",13) + NORM });
    output += ({ format_line(return_rank(Ranks[i])) });
    output += ({ HIK+"*~*"+NORM });
    output += ({ NORM+"\n" });
  }

  /* bottom border here */
  output += ({ lalign(HIK+"***"+NORM+RED+"~~~~~~~~~~~~~~~~~~~~~~~~~~~"+HIK+"***"+NORM,50) });
  

  return output;
}