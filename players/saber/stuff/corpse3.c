string name;
int corpse_level,decay;

prevent_insert() {
    write("The corpse is too big.\n");
    return 1;
}

init() {
    add_action("search","search");
}

reset() {
}

set_name(n)
{
   name = n;
}

short() {
    if(!name)
    set_name("an unknown man");
   return "Corpse of "+name;
}

long() {
   write("This is the dead body of "+name+".\n");
  write("The corpse has a horrible expression frozen into it's face.\n");
}

id(str) {
/* Added ID to prevent exchange at Bone Marketplace  -Dar  */
return str == "corpse" || str == "corpse of " + name || str == "bad_corpse" ||
	str == "remains";
}


can_put_and_get() { return 1; }

search(str)
{
    object ob;
    if (!str || !id(str))
	return 0;
    write("You search " + str + ", and find:\n");
    say(call_other(this_player(), "query_name") + " searches " + str + ".\n");
    if ( ! search_obj(this_object()))
    {
	write("\tNothing.\n");
    }
    else
    {
	write("\n");
    }
    return 1;
}

search_obj(cont)
{
    object ob;
    int total;
    string item;

    if (!call_other(cont, "can_put_and_get"))
	return 0;
    ob = first_inventory(cont);
    while(ob) {
	total += 1;
	item = call_other(ob, "short");
	write(item + ", ");
	ob = next_inventory(ob);
    }
    return total;
}

get() {
    return 1;
}

query_weight() {
    return 5;
}
set_corpse_level(arg) {
          corpse_level = 1;
           return 1;
}
heal_value() {
int heal;
   heal = 5;
return heal;
}

quest_ob()  { return 1; }
