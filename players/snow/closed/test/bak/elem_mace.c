/* This sword is gained by completing the Elemental Test at extreme risk of death
 * if this weapon seems powerful for that, please try out the test. - Snow
 * changed everything to Damage Types [5.25.01] Vertebraker
*/
inherit "/obj/weapon.c";
#include "/players/snow/closed/color.h"
#define SWORD RED+"~ "+OFF+BLUE+"Ele"+OFF+GREEN+"men"+OFF+BOLD+"tal M"+OFF+GREEN+"ac"+OFF+BLUE+"e"+OFF+RED+" ~"+OFF

int smack;

reset(arg) {
  ::reset(arg);
  set_name("elemental mace");
  set_alias("mace");
  set_short(SWORD);
  set_long("\n\tYou have found the Elemental Mace.\n"+
    "It is a heavy blunt weapon that seems to hold a great and strange power.\n"+
    "Wield it wisely as it is rather rare.\n");
  set_class(21);
  set_type("mace");
  set_weight(2);
  set_value(10000);
  set_hit_func(this_object());
  }

query_save_flag() { return 0; }

weapon_hit(object ob) {
  int r;
  int dam;
  r = random(16);
  if(!environment() || !this_player() || this_player() != environment()) return;

  if(!random(20) && !ob->is_player() && ob->query_ac() > 5) {
    tell_room(environment(ob),
    "*** "+ob->query_name()+"'s defenses are weakened! ***\n");
    ob->set_ac(ob->query_ac() - 1);
    return 3; }
  if(!r) {
    earth(ob);
    dam = (int)ob->hit_player(random(5) + 3, "other|earth");
    if(ob)
    if((int)ob->query_spell_point() > 0)
      ob->add_spell_point(-dam);
    return 3;
  }
  if(r == 1) {
    water(ob);
    dam = (int)ob->hit_player(random(8) + 1, "other|water");
    if(ob)
    if((int)ob->query_spell_point() > 0) ob->add_spell_point(-dam);
    return 3;
  }
  if(r == 2) {
    flame(ob);
    dam = (int)ob->hit_player(5 + random(5), "other|fire");
    if(ob)
    if((int)ob->query_spell_point() > 0) ob->add_spell_point(-dam);
    return 3;
  }
  call_out("extra_hit", 3, ob);
  return; }

earth(object ob) {
  if(!ob) return;
  tell_room(environment(ob),
  BROWN+"\n\t* * THE EARTH SHAKES!\n\n\t"+ob->query_name()+" FALLS TO THE GROUND!\n"+OFF);
  tell_object(ob, BROWN+" * * * * THE EARTH RISES TO CRUSH YOU! * * * * \n"+OFF);
  return 1; }

water(object ob) {
  if(!ob) return;
  tell_room(environment(ob),
  BLUE+"\n\tTHE SKY GROWS DARK!\n\n\t ,', ,', HAIL CRASHES DOWN FROM THE SKY! ,', ,',\n"+
  "\n\t"+ob->query_name()+" IS PUMMELED BY THE ICE!\n"+OFF);
  tell_object(ob, BLUE+",', ,', THE HAIL SMASHES YOU DOWN! ,', ,',\n"+OFF);
  return 1; }

flame(object ob) {
  if(!ob) return;
  tell_room(environment(ob),
  RED+"\n\tCRACKS OPEN IN THE EARTH!\n\n\tLAVA SPRAYS FORTH!\n\n\t"+
  ob->query_name()+" SCREAMS IN BURNED AGONY!\n"+OFF);
  tell_object(ob, RED+"\nHOT PAIN RIPS THROUGH YOU!\n");
  return 1; }

extra_hit(object ob) {
  if(!ob) return;
  if(!environment()) return;
    if(environment(environment()) != environment(ob)) return;
  if(environment()->query_attack() != ob) return;
  if(ob->query_hp() < 80) return;
  tell_room(environment(ob),
    BOLD+environment(this_object())->query_name()+" blurs in a burst of speed!\n"+OFF);
  tell_room(environment(ob),
    environment(this_object())->query_name()+" impales "+ob->query_name()+" with a "+
    "vicious thrust!\n");
  ob->hit_player(random(21));
  return 1; }

wield(str) {
  if(this_object()->id(str)) {
  if(!present("elemental aura", this_player())) {
    write("The "+SWORD+" burns you with its power!\n");
    return 1; }
  }
/* fixed by Verte 5.28.01 */
  return ::wield(str); }

offwield_function() {
  if(!present("elemental aura", this_player())) {
    write("The "+SWORD+" burns you with its power!\n");
    return 2; }
  return 0; }
