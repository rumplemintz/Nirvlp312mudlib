inherit "basic/create";

int hr, min, sec;            /* To hold the minutes and hours */
int i;                       /* placehoder */
int clock_start, test_flag, dong_flag;    /* Flags to set/test */

string *roomlist = ({
    "alley.c", "bank.c", "eastroad1.c", "eastroad2.c", "eastroad3.c",
    "eastroad4.c", "eastroad5.c", "inn.c", "jetty.c", "jetty2.c",
    "narr_alley.c", "northroad1.c", "northroad2.c", "northroad3.c",
    "pub2.c", "pub3.c", "shop.c", "southroad1.c", "southroad2.c",
    "southroad3.c", "store.c", "sunalley1.c", "sunalley3.c", "vill_green.c",
    "vill_road1.c", "vill_road2.c", "vill_road3.c", "vill_shore.c", "vill_shore2.c",
    "vill_track.c", "well.c", "yard.c"
});

void dong();
void find_time();
void shout_two(string str);
void look_for_symb(object obj);

int id(string str) { return str == "tower" || str == "clock" || str == "clock tower"; }
string short() { return "A large and very tall clock tower stands here";}
int get() { return 0;}
int query_value() { return 3;}
int query_weight() { return 3000;}


string long() {
    write("A large brick clock tower,\n" +
          "The clock is reporting the time to be: " + hr + ":" + (min < 10 ? "0" + min : min) + " Central time.\n");
          say(this_player()->query_name() + " takes a look at the clock and finds out the time.\n");
}

void find_time() {
    string time;

    time = ctime();
    hr = atoi(ctime()[11..12]);
    min = atoi(ctime()[14..15]);
    sec = atoi(ctime()[17..18]);

    if (hr > 12) hr = hr-12;

    if (test_flag) {
        min = 0;
        sec = 0;
        test_flag = 0;
    }

    if (!min && sec < 2 && !dong_flag) {
        shout_two("\nYou hear the clock tower chime.\n\n");
        i = 1;
        dong_flag = 1;
        dong();
    }
    
    call_out("find_time", 1);
}

void dong() {
    shout_two("dong!\n\n");
    if (i < hr) {
        i += 1;
        call_out("dong", 4);
    }

    if (i >= hr)  dong_flag = 0;
}

void init() {
    if ((int)this_player()->query_level() >= 21)
        add_action("settest", "test");
    
    if (!clock_start) {
           call_out("find_time", 1);
    }
}

int settest() {
    test_flag = 1;
    if (member(roomlist, object_name(environment(this_player())))) {
        write("Your environment is in the array.\n");
        return 1;
    }
    else
    {
        write("Your environment was not found in the array.\n");
        return 1;
    }
    return 1;
}

void shout_two(string str) {
    object *list;
    object envob;
    string envfil;
    int x;

/*
    log_file("CLOCKTEST", str);
*/
    list = users();

    while (x < sizeof(list))
    {
        string pname;
        object pobject;

        if (list[i]) {
            if ((int)list[i]->query_level()) {
                pname = (string)list[i]->query_real_name();
                
                if (list[i]->query_ghost()) pname = "ghost of " + pname;

                pobject = find_player(pname);
                envob = environment(list[i]);

                if (envob) {
                    envfil = object_name(envob);
		    write("envfil = " + envfil + "\n");
                    write("Member ? " + (member(roomlist, envfil) ? "Y" : "N") + "\n");

                    if ((int)list[i]->query_level() < 20) {

                        if (member(roomlist, envfil)) {
                            tell_object(list[i], str);
                            look_for_symb(list[i]);
                        }
                    }
                }
            }
        }
        i += 1;
    }
}

void look_for_symb(object obj) {
    if ((string)obj->query_guild_name() == "symbiote" || "neo symbiote") {
        tell_object(obj, "Your symbiote cries out in pain as the clock tower's" +
                        " bells chime!\n");
        obj->heal_self(-(30 + random(21)));

        if ((int)obj->query_hp() < 0) obj->hit_player(1000);
    }
}
