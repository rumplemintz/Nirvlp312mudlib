id(str) { return str == "storm"; }
int z;
long() {
write("You see storm clouds above.\n");
}
query_value() {
  return 0;
}
query_weight() {
  return 100;
}

reset(arg) {
   if(arg) return;

call_out("storm",random(30));
}

storm() {
 z=random(5);
 if(!environment(this_object())) return 1;
if (z == 1)
{
tell_room(environment(this_object()),
 "Lightning flashes across the sky.\n");
call_out("storm",random(30));
   return 1;
}
else
{ if (z == 2)
{
 tell_room(environment(this_object()),
"Thunder booms loudly overhead.\n");
call_out("storm",random(30));
 return 1;
}
else if (z == 0)
{
tell_room(environment(this_object()),
 "The wind screams by you.\n");
call_out("storm",random(30));
 return 1;
}
else if (z == 3) {
tell_room(environment(this_object()),
"The rain lashes out at you.\n");
call_out("storm",random(30));
return 1;
}
else if (z == 4) {
tell_room(environment(this_object()),
 "A light hail beats against you.\n");
call_out("strom",random(30));
return 1;   }
}
}
