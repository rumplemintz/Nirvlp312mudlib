main(str){
string who,what;
if(!str || sscanf(str,"%s %s",who,what) != 2) {
write("Incorrect # of args.\n");
return 1;
}
if(!find_living(who)){
write("not found.\n");
return 1;
}

write(call_other(find_living(who), "query_"+what));
write("\n");
return 1;
}