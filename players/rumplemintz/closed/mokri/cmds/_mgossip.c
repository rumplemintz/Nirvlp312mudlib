inherit "obj/user/channel";

main(string str)
{
string mess;

mess = "/players/mokri/stuff/letters/block"->block_string(str);
mess = "\n" + mess;

command("gossip " + mess,this_player());
return 1;
}