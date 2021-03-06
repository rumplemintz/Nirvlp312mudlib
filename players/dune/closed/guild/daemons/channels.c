/* originally created by wocket */
#include "../DEFS.h"

/* puppy changes start */
#define PUPPATH "/players/dune/closed/guild/pup/"
/* puppy changes end */


object listeners, members;
int num_listeners, num_members;
string *history;
string *ohistory;
string *dhistory;
static string *playerLogins;


status newLogin(string name)
{
  status isNew, found;
  int i;
  isNew = 0;
  /* add player to login list if not already there */
  if (!playerLogins)
  {
    playerLogins = ({name,});
    isNew = 1;
  }
  else
  {
    found = 0;
    for (i=0; i < sizeof(playerLogins); i++)
    {
      if (playerLogins[i] == name) found = 1;
    }
    if (!found)
    {
      playerLogins += ({name,});
      isNew = 1;
    }
  }
  return isNew;
}


reset(arg)
{
  if(arg) return;
  num_listeners = num_members = 0;
  listeners = members = 0;
  history  = ({});
  ohistory = ({});
  dhistory = ({});
}


query_listeners() { return listeners; }
query_members() { return members; }


add_member(object ob)
{
  if(!ob) return;
  members += ({ ob, });
  return 1;
}


add_listener(object ob)
{
  if(!ob) return;
  listeners += ({ ob, });
  return 1;
}


remove_member(object ob)
{
  if(!ob) return;
  members -= ({ ob });
  return 1;
}


remove_listener(object ob)
{
  if(!ob) return;
  listeners -= ({ ob });
  return 1;
}


resetchannel()
{
  int i,n;
  object players;
  players = users();
  num_members = num_listeners = 0;
  listeners = members = ({});
  for (i=0,n=sizeof(players); i<n ; i++)
  {
    if (present(GUILD_ID,players[i]))
    {
      members += ({ players[i], });
      num_members++;
    }
  }
  for (i=0,n=sizeof(members); i<n ; i++)
  {
    if (present(GUILD_ID,members[i])->muffled() != 1)
    {
      listeners += ({ members[i], });
      num_listeners++;
    }
  }

  return 1;
}


send_msg(string str)
{
  int i,n;
  object ob;
  for (i=0,n=sizeof(listeners);i<n;i++)
  {
    if (listeners[i])
    {
      tell_object(listeners[i],str);
    }
  }
  addhistory(str);
  
  /* puppy changes start */
#if 0
  write_file(PUPPATH + "cybernetlog", str);
#endif
  /* puppy changes end */

}

/* added by verte needed for mud emotes 05 */
query_officers() {
  int i,n;
  object *peeps;
  peeps = ({ });
  for(i=0,n=sizeof(listeners);i<n;i++)
  {
    if(listeners[i] && present(GUILD_ID,listeners[i])->guild_officer() == 1)
    {
      peeps += ({ listeners[i] });
    }
  }
  return peeps;
}

officer_send_msg(string str)
{
  int i,n;
  
  for(i=0,n=sizeof(listeners);i<n;i++)
  {
    if(listeners[i] && present(GUILD_ID,listeners[i])->guild_officer() == 1)
    {
      tell_object(listeners[i],str);
    }
  }
  add_ohistory(str);

  /* puppy changes start */
  write_file(PUPPATH + "cyberonetlog", str);
  /* puppy changes end */
}


/* Used where CyberDaemon talks over the normal channel, 
   which can be muffled as players see fit. */
daemontell(string str)
{
  string msg;
  msg = "";
  msg += RED+"~~~"+OFF;
  msg += BOLD+"CYBERDAEMON"+OFF;
  msg += RED+"@CyberNet>> "+OFF;
  msg += str;
  msg += "\n";
  send_msg(msg);
}


/* Used to send tells over the main guild channel. */
tell(string str)
{
  string msg;
  msg = "";
  msg += RED+"~~~"+OFF+BOLD;
  msg += capitalize(this_player()->query_real_name())+OFF;
  msg += RED+"@CyberNet>> "+OFF;
  msg += str;
  msg += "\n";
  send_msg(msg);
}


/* Used to emote over the main guild channel */
emote(string str)
{
  string msg;
  string em, arg, file;
    
  if(sscanf(str, "%s %s", em, arg) != 2) {
    em = str;
  }
    em = implode(explode(em, "."), "");
  if(file_size(file="/bin/soul/_"+em+".c") > 0) {
    return (int)file->guildcast("cyberninja", arg);
  }
  msg = "";
  msg += RED+"~~~CyberNet Image>> "+OFF;
  msg += BOLD+capitalize(this_player()->query_real_name())+OFF+RED+"_"+OFF+str;
  msg += "\n";
  send_msg(msg);
}

/* needed for mud emotes on channels, 05 verte */
string query_nem_tag() {
  return RED+"~~~CyberNet Image>>"+OFF;
}


/* Used to send tells over the officer channel */
otell(string str)
{
  string msg;
  msg = "";
  msg += BOLD+BLUE+"~~~"+OFF+BOLD;
  msg += capitalize(this_player()->query_real_name())+OFF;
  msg += BOLD+BLUE+"@OfficerNet>> "+OFF;
  msg += str;
  msg += "\n";
  officer_send_msg(msg);
}


/* Used to emote over the officer channel */
oemote(string str)
{
  string msg;
  string em, arg, file;
    
  if(sscanf(str, "%s %s", em, arg) != 2) {
    em = str;
  }
    em = implode(explode(em, "."), "");
  if(file_size(file="/bin/soul/_"+em+".c") > 0) {
    return (int)file->guildcast("cyberninja", arg);
  }
  msg = "";
  msg += BOLD+BLUE+"~~~CyberNet Image>> "+OFF;
  msg += BOLD+capitalize(this_player()->query_real_name())+OFF+BOLD+BLUE+"_"+OFF+str;
  msg += "\n";
  officer_send_msg(msg);
}

/* needed for mud emotes on channels, 05 verte */
string query_onem_tag() {
  return BOLD+BLUE+"~~~CyberNet Image>>"+OFF;
}

daemon_send_msg(string str)
{
  int i,n;
  for (i=0, n=sizeof(members); i<n; i++)
  {
    if (members[i]) tell_object(members[i], str);
  }
  add_dhistory(str);
return 1;

}


overchannel(string str)
{
  string msg;
  msg = "";
  msg += BLINK+BOLD+"<<_Msg from CyberDaemon_>>>"+OFF+OFF+" "+str+"\n";
  daemon_send_msg(msg);
  return 1;
}


addhistory(str)
{
  if(sizeof(history) == 20)
  {
    history -= ({ history[0] });
  }
  history += ({ str, });
}


add_ohistory(str)
{
  if(sizeof(ohistory) == 20)
  {
    ohistory -= ({ ohistory [0] });
  }
  ohistory += ({ str, });
}


add_dhistory(str)
{
  if(sizeof(dhistory) == 20)
  {
    dhistory -= ({ dhistory [0] });
  }
  dhistory += ({ str, });
}


viewhistory(string type)
{
  int i, a;
  string msg;
  string *hist;

  if      (type == "net")   hist = history;
  else if (type == "onet")  hist = ohistory;
  else                      hist = dhistory;

  msg = "\n" + LINE + "Channel History\n" + LINE;
  for(i=0, a=sizeof(hist); i<a; i++)
  {
    msg += hist[i];
  }
  msg += LINE;
  write(msg);
  return 1;
}
