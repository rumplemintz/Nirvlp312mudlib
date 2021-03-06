/* Evocation - Attack spells of the Bardic Guild  */

/* Words of Pain - a low level attack spell */
words_of_pain(str)  {
string gender;
object ob;
int aaa;
if(!str && this_player()->query_attack())  {
  str = TP->query_attack()->query_real_name();
        }
  if(!str)  {
  write("You must invoke the words of pain against an opponent.\n");
  return 1;
        }
  ob = present(str,ENV);
  gender = ob->query_objective();
  if(attack_spell(-50,2,10,ob) == -1) return 0;
  aaa = random(20);
  if(aaa > ob->query_hp())  aaa = ob->query_hp() -1;
  ob->hit_player(aaa);
  write("Extending one hand towards "+CAP+", you weave the Words Of Pain into\n"+
   "song lyrics and channel the energy into "+gender+".\n");
  say(tp+" weaves an invocation into lyrics and channels energy through "+GENDER+" "+INST+".\n");
  say(tp+" extends a hand towards "+CAP+".\n");
  say(tp+" weaves an invocation into lyrics and channels the energy towards "+CAP+".\n");
  TP->attack_object(ob);
  tell_room(environment(TP), CAP+" staggers.\n");
  call_other(TP, "add_spell_point", -10);
  return 1;
        }

/* Requiem of the Falling Stars - A high level attack spell
  which requires a material component.  */
requiem_of_stars()  {
object ob, ob2;
int i, cost_count;
string NAM;
  ob2 = present("gem",INV);
  if(!ob2)  { ob2 = present("stone",INV);  }
  if(!ob2)  { ob2 = present("rock",INV);   }
   if(!ob2)  {
    write("You must have a gemstone to play the requiem of the stars.\n");
    return 1;
        }
  NAM = call_other(ob2,"short");
 if(spell(-170,7,50,TO) == -1) return 0;
  if(TP->query_ghost())  { notify_fail("You must be alive to do that.\n");
        }
  tell_room(ENV, tp+" holds up a "+NAM+".\n");
  write("You play a requiem to the stars upon your "+INST+".\n");
  say(tp+" plays a requiem upon "+GENDER+" "+INST+".\n");
  tell_room(ENV, "\nA burst of STARFIRE explodes around you.\n");
  cost_count = 0;
  ob = first_inventory(environment(this_player()));
    while(ob)  {
  if(ob->is_player()) {
  tell_room(ENV, ob->query_name()+" is shielded from the STARFIRE.\n\n");
  tell_object(ob, "You feel very lucky.\n\n");
        }
  else if(ob->is_pet())  {
  tell_room(ENV, "The "+ob->query_name()+" is shielded from the STARFIRE.\n");
        }
  else if(ob->query_npc())  {
  tell_room(ENV, ob->query_name()+" is FRIED by a burst of STARFIRE.\n");
  if(!ob->query_attack())  {
  if(living(ob)) ob->attack_object(TP);
  TP->attack_object(ob);
        }
  ob->hit_player(random(40));
  cost_count = cost_count + 1;
        }
  ob = next_inventory(ob);
        }
  cost_count = cost_count * 15;
  if(cost_count == "0")  {
    write("There are not creatures here to fry.\n");
        return 1;
        }
  if(cost_count < 50) { cost_count = 50; }
  call_other(TP,"add_spell_point",-cost_count);
  tell_room(ENV, NAM+" fades from view.\n");
  destruct(ob2);
        return 1;
        }

/* A spell which makes 4 chromatic orbs for a Bard  */
chromatic_sphere()  {
 if(present("sphere",TP))  {
    write("You have already shaped a globe of chromatic spheres.\n");
    return 1;
        }
 if(spell(-164,5,100,TO) ==-1)  return 0;
 write("You play a psalm upon your "+TO->query_instrument()+".\n"+
    "The music slowly shapes the forces of primal chaos into a globe.\n"+
    "The psalm ends as the globe of chromatic spheres gently floats into your hand.\n");
  say(tp+" plays a psalm upon "+GENDER+" "+INST+".\n"+
    "The music slowly shapes the forces of primal chaos into a globe.\n"+
    "The psalm ends as the globe of chromatic spheres lands in "+tp+"'s hand.\n");
 move_object(clone_object("/players/guilds/bards/sphere.c"),TP);
 call_other(TP,"add_spell_point",-100);
   return 1;
        }

/* A medium level attack spell with a multitude of effects */
elemental_tune(str)  {
object ob;
string target;
int aaa, bbb;
  if(!str && this_player()->query_attack())  {
   str = TP->query_attack()->query_real_name();
        }
  if(!str)  {
    write("You must direct the tune to an opponent.\n");
    return 1;
        }
  ob = present(str,environment(TP));
  if(!ob)  {
  write("You must direct the tune towards an opponent.\n");
    return 1;
        }
  target = ob->query_name();
  target = capitalize(target);
  if(attack_spell(-129,4,25,ob) == -1) return 0;
  write("\n");
  bbb = random(8) + 1;

  if(bbb == 1)  {
    write("You sing the tune of Elemental Earth.\n");
    say(tp+" sings the tune of Elemental Earth.\n");
    tell_room(ENV,
      target+" is buried under a rain of sharp gray stones.\n");
        }
  else if(bbb == 2)  {
    write("You whistle up a storm.\n");
    say(tp+" whistles up a storm.\n");
    tell_room(ENV,
      "\n*Clouds gather overhead.\n"+
      "\n   *Thunder is heard in the distance.\n"+
      "\n      *It begins to rain on "+target+".\n"+
      "\n         *"+target+" is struck by a BLAZING bolt of lightning.\n\n");
        }
  else if(bbb == 3)  {
    write("You throw a small iron sphere at "+target+" as you hum an off key tune.\n");
    say(tp+" throws a small iron sphere at "+target+" as "+TP->query_pronoun()+" hums an off key tune.\n");
    tell_room(ENV,
    "The ball EXPLODES, piercing "+target+" with sharp slivers of shrapnel.\n");
        }
  else if(bbb == 4)  {
    write("You play a light tune upon your "+INST+".\n"+
      "Extending your hand, you point at "+target+".\n");
    say(tp+" plays a light turn upon "+GENDER+" "+INST+".\n"+
      tp+" points at "+target+".\n");
    tell_room(ENV,
      target+" is picked up by a sudden gust of wind and smashed against the ground.\n");
        }
  else if (bbb == 5)  {
    write("You produce a blazing melody upon your "+INST+".\n");
    say(tp+" produces a blazing melody upon "+GENDER+" "+INST+".\n");
    tell_room(ENV,
      "A column of searing crimson fire descends from the heavens upon "+target+".\n"+
      target+" is engulfed in an inferno of flame.\n");
        }
  else if (bbb == 6)  {
    write("You play the tune of Elemental Ice upon your "+INST+".\n"+
      "Glancing up, you point at "+target+".\n");
    say(tp+" plays the tune of Elemental Ice upon "+GENDER+" "+INST+".\n"+
      "You feel a slight chill as "+tp+" points at "+target+".\n");
    tell_room(ENV,
      target+" is nearly decapitated by large slivers of falling ice.\n");
        }
  else if (bbb == 7)  {
    write("You play a tune on your "+INST+".\n"+
      "Singing the words 'Rikca Solamnos Larlus' you point at "+target+".\n");
    say(tp+" plays a tune upon "+GENDER+" "+INST+".\n"+
      tp+" sings the words 'Rikca Solamnos Larlus' and points at "+target+".\n");
    tell_room(ENV,
      target+" is blinded by a burst of scintillating white light.\n");
        }
  else if (bbb == 8)  {
    write("You whistle a pastoral tune as you glare at "+target+".\n");
    say(tp+" whistles a pastoral tune and glares at "+target+".\n");
    tell_room(environment(TP),
      target+" is impaled by hundreds of large wooden splinters.\n");
        }
   aaa = random(50);
  if(aaa > ob->query_hp())  aaa = ob->query_hp() - 1;
  ob->hit_player(aaa);
  TP->attack_object(ob);
  call_other(TP,"add_spell_point", -25);
  return 1;
        }
