/* Version 1.0 of the Market who, taken from my old Necro who listing */

market_who() {

int a, b;
string who, loc, gld, cmbt, race;
object ob, ob2, attacker;
string pkcheck;

ob = users();

write(WHT);
write("--------------------------------------------------------------------------\n");
write(HIR);
write("     Name           Race      Level    Guild   Combat?  Location\n");
write(NORM);
write(WHT);
write("--------------------------------------------------------------------------\n");
write(NORM);

for(b=0; b<sizeof(ob); b+=1) {
  if(!ob[b]->query_invis()) {
  if(present("market_ob",ob[b])){
write(HIW+"(8=]"+NORM);
write(" "); }
  else
write("     ");
write(pad(ob[b]->query_name(),15));
  if(ob[b]->query_name() == "Guineapig"){
write(pad("hellspawn",9)); }
else {
write(NORM+pad(ob[b]->query_race(),9));
write(NORM+NORM);
}
write(" ");
write(pad(ob[b]->query_level(),3));
if(ob[b]->query_level() < 20){
write("+");
write(pad(ob[b]->query_extra_level(),5));
} else {
write("      ");  }

if(ob[b]->query_level() > 19) {
write(BOLD+"Wizard    "+NORM);
} else {
if(ob[b]->query_guild_name() == 0) {
   gld = "none"; }
if(ob[b]->query_guild_name() == "NONE"){
  gld = "none"; }
if(ob[b]->query_guild_name() == "None"){
  gld = "none"; }
if(ob[b]->query_guild_name() == "necromancer"){
   gld = "necro"; }
if(ob[b]->query_guild_name() == "Knights Templar"){
   gld = "templar"; }
if(ob[b]->query_guild_name() == "polymorph"){
   gld = "poly"; }
if(ob[b]->query_guild_name() == "vampire"){
   gld = "vampire"; }
if(ob[b]->query_guild_name() == "healer"){
   gld = "healer"; }
if(ob[b]->query_guild_name() == "Druid"){
  gld = "druid"; }
if(ob[b]->query_guild_name() == "bloodfist"){
   gld = "bloodfist"; }
if(ob[b]->query_guild_name() == "The Hive"){
   gld = "none"; }
if(ob[b]->query_guild_name() == "fallen"){
   gld = "fallen"; }
if(ob[b]->query_guild_name() == "dervish"){
   gld = "dervish"; }
if(ob[b]->query_guild_name() == "bard"){
   gld = "bard"; }
if(ob[b]->query_guild_name() == "symbiote"){
   gld = "symbiote"; }
if(ob[b]->query_guild_name() == "neo symbiote"){
   gld = "neo sym"; }
if(ob[b]->query_guild_name() == "shardak"){
   gld = "shardak"; }
if(ob[b]->query_guild_name() == "warrior"){
   gld = "warrior"; }
if(ob[b]->query_guild_name() == "cyberninja"){
   gld = "cyberninj"; }
if(ob[b]->query_guild_name() == "rangers"){
   gld = "ranger"; }
if(ob[b]->query_guild_name() == "dark rangers"){
   gld = "dark rangr"; }
if(ob[b]->query_level() > 20){
  gld = "Wizard"; }
write(pad(gld,8));
write("  ");
}

if(ob[b]->query_attack()){
write(HIR+"YES"+NORM);
write(" ");
}
   else
write("no  ");
write("   ");

if(!environment(ob[b])) loc = "LOGIN";
else
loc = environment(ob[b])->short();
write(loc);
write(NORM+NORM);
write("\n");
   }
}

write(WHT);
write("--------------------------------------------------------------------------\n");
write(HIR);
write("     Name           Race      Level    Guild   Combat?  Location\n");
write(NORM);
write(WHT);
write("--------------------------------------------------------------------------\n");
write(NORM);
return 1; }
