#include "/players/guilds/necro/DEFS"
#include "/obj/player/prestige.h"

#define BAR  "\t<----------------------------------------------------------->\n"
#define SPACE "       "

string cutstring(string str, int length){
    string str2;
    if(!length || length < 0)
	length = 20;
    str = str+"                                                                                  ";
    str2 = str[0..length];
    return str2;
}

int cmd(string str){
    int g_level, glevel;
    string lev, presname;
    object ob,me;
    ob = present("necro_ob", this_player());
    me = this_player();
    if(!present("necro_ob", this_player()))
	return 0;
    if(str == "-old")
	return 0;
    write("\n  "); 
    write("\t<"+HIR+"Necromantic Stat Score"+OFF+
      ">------------------------------------>\n");
    write(SPACE+BOLD+BLK+"\t     Str: "+OFF+BOLD+
      cutstring((string)me->query_attrib("str"),5)+OFF);
    write(BOLD+BLK+"Sta: "+OFF+BOLD+cutstring((string)me->query_attrib("sta"),5)+OFF);
    write(BOLD+BLK+"Pie: "+OFF+BOLD+cutstring((string)me->query_attrib("pie"),5)+OFF);
    write(BOLD+BLK+"Wil: "+OFF+BOLD+cutstring((string)me->query_attrib("wil"),5)+OFF);
    write(BOLD+BLK+"Cha: "+OFF+BOLD+cutstring((string)me->query_attrib("cha"),5)+OFF);
    write("\n");
    write(SPACE+BOLD+BLK+"\t     Mag: "+OFF+BOLD+
      cutstring((string)me->query_attrib("mag"),5)+OFF);
    write(BOLD+BLK+"Luc: "+OFF+BOLD+cutstring((string)me->query_attrib("luc"),5)+OFF);
    write(BOLD+BLK+"Int: "+OFF+BOLD+cutstring((string)me->query_attrib("int"),5)+OFF);
    write(BOLD+BLK+"Ste: "+OFF+BOLD+cutstring((string)me->query_attrib("ste"),5)+OFF);
    write(BOLD+BLK+"Dex: "+OFF+BOLD+cutstring((string)me->query_attrib("dex"),5)+OFF);
    write("\n");

	
	/* Added by Oberon */
	if( me->query_prestige_level() )
		    write("\t<"+HIR+"Prestige Skill Points: "+ me->query_prestige_skillpt()+OFF+" >-------------------------------->\n");
	else
		write(BAR+"\n");
	
	if(me->query_prestige_level()) {
		int i;
		write("\t     ");
		/*write("\tPrestige Skill Points: "+ me->query_prestige_skillpt()+"\n");*/
		for(i=0; i < sizeof(PRES_SKILL_DESC); i++) {
			switch(PRES_SKILL_DESC[i]) {
				case "Experience": presname="Exp"; break;
				case "Weapon Class": presname="WC"; break;
				case "Armor Class": presname="AC"; break;
				case "Gold": presname="Gold"; break;
				case "SP Regeneration": presname="SP Regen"; break;
				case "HP Regeneration": presname="HP Regen"; break;
				case "Detoxification": presname="Detox"; break;
				case "HP Bonus": presname="HP"; break;
				case "SP Bonus": presname="SP"; break;
				default: presname = PRES_SKILL_DESC[i]; break;
			}
			
			write(BOLD+BLK+""+pad(presname+":", 10) + ""+OFF+BOLD+""+me->query_prestige_skill( VALID_PRES_SKILL[i] )+""+OFF );
			if( i%3 == 2 && i == sizeof(PRES_SKILL_DESC)-1)
				write("\n");
			else if( i%3 == 2 )
				write( "\n\t     " );
			else
				write( "\t" );
		}
		write( BAR+"\n" );
	}

    return 1;
}
