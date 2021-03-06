reset(started)
{
    if (!started)
  set_light(1);
}

init()
{
    add_action("south", "south");
    add_action("east", "east");
    add_action("west", "west");
}

short()
{
    return "A dimly lit forest";
}

long()
{
    write("You are in part of a dimly lit forest.\n" +
    "Trails lead south, east and west\n");
}

south()
{
    call_other(this_player(), "move_player", "south#room/south/sshore22");
    return 1;
}

east()
{
    call_other(this_player(), "move_player", "east#room/south/sshore23");
    return 1;
}

west()
{
    call_other(this_player(), "move_player", "west#room/south/sforst22");
    return 1;
}
