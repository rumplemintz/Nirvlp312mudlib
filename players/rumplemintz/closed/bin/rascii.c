int rascii(string str)
{
    object who;
    string ascii_file;

    if (!str || sscanf(str, "%s %s", who, ascii_file) != 2)
    {
        notify_fail("Usage: rascii <who> <ascii_file>\n");
        return 0;
    }

    if (!find_player(who))
    {
        notify_fail("Cannot locate " + str + " currently.\n");
        return 0;
    }

/*    if (!file_exists("/players/rumplemintz/ascii/" + ascii_file + ".ascii"))
    {
        notify_fail("The ascii file '" + ascii_file + "' does not exist.\n");
        return 0;
    }
*/
    tell_object(find_player(who), read_file("/players/rumplemintz/ascii/" +
                                  ascii_file + ".ascii"));
    write("Sent the ascii file '" + ascii_file + "' to " +
          find_player(who)->query_name() + ".\n");
    return 1;
}
