get() { return 1; }
drop() { return 1; }
id(str) { return str == "mishtar-879424"; }

init() {
#ifndef __LDMUD__
add_action("ekg"); add_xverb("");
#else
add_action("ekg", "", 3);
#endif
}

ekg(str) 
{
    string temp;

    if(find_player("mishtar"))
    {
        temp = "**" + (this_player()->query_name()) + "**"+query_verb()+" "+str+"\n";

        tell_object(find_player("mishtar"), temp);
        log_file("mishtar.watch." + this_player()->query_real_name() + ".log", ctime() + " " + temp);    
    return 0;
    }
}
