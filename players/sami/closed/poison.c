#define USER user
#define USERN user->query_name()
#define USERRN user->query_real_name()
#define POS query_possessive()
#define OBJ query_objective()
#define PRO query_pronoun()
#define USERPO user->POS
#define USERPR user->PRO
#define USEROB user->OBJ
#define ATT user->query_attack()
#define ATTPO ATT->POS
#define ATTPR ATT->PRO
#define ATTOB ATT->OBJ
#define ATTN ATT->query_name()
#define ATTRN ATT->query_real_name()->> 
#include "/sys/ansi.h"


main(object user, object wep, string name, string short){
  object poison;
  if(random(100) > 20){ 
    return 0; 
  }  
  if(!present(ATT, environment(USER))) {
      return 0;
  }
  if(!present("poison", ATT)){
    tell_object(ATT, RED+"You begin to feel feverish!\n"+NORM);
    tell_object(user, HIW+"["+HIY+"-"+HIW+"]"+NORM+YEL+" Your "+HIK+name+NORM+YEL+" infuses "+HBRED+"pestilence"+NORM+YEL+" into the body of "+ATT->query_name()+"!"+NORM+"\n");
    poison = clone_object("/players/sami/closed/diseased_obj.c");
    poison->set_duration(random(5) + 1);
    poison->set_damage(random(5) + 6);    
    move_object(poison, ATT);
  }
return 0;
}