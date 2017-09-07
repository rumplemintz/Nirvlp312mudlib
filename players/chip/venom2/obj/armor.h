armor_special(){
	int total;
	total = 0;
	
	/******* Shaped Armor - alternative to grafting your armors *******/
	if(arm_tot){
		if(!random(20) < arm_tot) tell_object(USER, BOLD+"["+COLOR+"armor"+NORM+BOLD+"]"+NORM+" Your armor glistens as it resists damage.\n");
		if(arm_tot > 20) total += random(20);
		else total += arm_tot;
	}
	
		total += defense_tentacles();
	
	/***** Combo Creation and Combat spell -
	gives ac for 1 round for some sp
	**************************************/
	if(block){
		tell_object(USER, COLOR+"(SHIELD)"+NORM+" You partially deflect the incoming attack!\n");
		total += block;
		block = 0;
	}
   if(total)
   if(USER->query_invis()) return total / 2;
	return total;
}




add_sh_armors(str){
	if(str == "amulet"){
		sh_armors[0] = BOLD+"NeckGuard ["+NORM+HIK+"Dark Matter"+NORM+BOLD+"]"+NORM+" (worn)";
		arm_tot += 3;
	}
        else if(str == "cloak"){
		sh_armors[1] = BOLD+"Flowing Cloak ["+NORM+HIK+"Dark Matter"+NORM+BOLD+"]"+NORM+" (worn)";
		arm_tot += 3;
	}
	else if(str == "boots"){
		sh_armors[2] = BOLD+"Boots ["+NORM+HIK+"Dark Matter"+NORM+BOLD+"]"+NORM+" (worn)";
		arm_tot += 3;
	}
	else if(str == "armor"){
		sh_armors[3] = BOLD+"Symbiotic Armor ["+NORM+HIK+"Dark Matter"+NORM+BOLD+"]"+NORM+" (worn)";
		arm_tot += 5;
	}
	else if(str == "gloves"){
		sh_armors[4] = BOLD+"Gloves ["+NORM+HIK+"Dark Matter"+NORM+BOLD+"]"+NORM+" (worn)";
		arm_tot += 3;
	}
	else if(str == "helmet"){
		sh_armors[5] = BOLD+"Smooth Helm ["+NORM+HIK+"Dark Matter"+NORM+BOLD+"]"+NORM+" (worn)";
		arm_tot += 3;
	}
	else if(str == "belt"){
		sh_armors[6] = BOLD+"Thick Belt ["+NORM+HIK+"Dark Matter"+NORM+BOLD+"]"+NORM+" (worn)";
		arm_tot += 3;
	}
        else if(str == "bracelet"){
		sh_armors[7] = BOLD+"Heavy Bracers ["+NORM+HIK+"Dark Matter"+NORM+BOLD+"]"+NORM+" (worn)";
		arm_tot += 3;
	}
	else{ return 1; }
	return 1;
}

remove_sharmor(str){
	if(!str){ write("Remit which piece of symbiotic armor?\n"); return 1; }
	if(str == "amulet" || str == "neckguard"){
		if(sh_armors[0]){
			sh_armors[0] = 0;
			write("You absorb the "+HIK+"Dark Matter"+NORM+" Neckguard.\n");
			arm_tot -= 3;
			return 1;
		}
		else{ write("You are not wearing that!\n"); return 1; }
	}
        else if(str == "cloak"){
		if(sh_armors[1]){
			sh_armors[1] = 0;
			write("You absorb the "+HIK+"Dark Matter"+NORM+" Cloak.\n");
			arm_tot -= 3;
			return 1;
		}
		else{ write("You are not wearing that!\n"); return 1; }
	}
	else if(str == "boots"){
		if(sh_armors[2]){
			sh_armors[2] = 0;
			write("You absorb the "+HIK+"Dark Matter"+NORM+" Boots.\n");
			arm_tot -= 3;
			return 1;
		}
		else{ write("You are not wearing that!\n"); return 1; }
	}
	else if(str == "armor"){
		if(sh_armors[3]){
			sh_armors[3] = 0;
			write("You absorb the "+HIK+"Dark Matter"+NORM+" Armor.\n");
			arm_tot -= 5;
			return 1;
		}
		else{ write("You are not wearing that!\n"); return 1; }
	}
	else if(str == "gloves"){
		if(sh_armors[4]){
			sh_armors[4] = 0;
			write("You absorb the "+HIK+"Dark Matter"+NORM+" Gloves.\n");
			arm_tot -= 3;
			return 1;
		}
		else{ write("You are not wearing that!\n"); return 1; }
	}
	else if(str == "helmet"){
		if(sh_armors[5]){
			sh_armors[5] = 0;
			write("You absorb the "+HIK+"Dark Matter"+NORM+" Helmet.\n");
			arm_tot -= 3;
			return 1;
		}
		else{ write("You are not wearing that!\n"); return 1; }
	}
	else if(str == "belt"){
		if(sh_armors[6]){
			sh_armors[6] = 0;
			write("You absorb the "+HIK+"Dark Matter"+NORM+" Belt.\n");
			arm_tot -= 3;
			return 1;
		}
		else{ write("You are not wearing that!\n"); return 1; }
	}
        else if(str == "bracers" || str == "bracelet"){
		if(sh_armors[7]){
			sh_armors[7] = 0;
			write("You absorb the "+HIK+"Dark Matter"+NORM+" Bracers.\n");
			arm_tot -= 3;
			return 1;
		}
		else{ write("You are not wearing that!\n"); return 1; }
	}
	else{ write("You are not wearing that!\n"); return 1; }
	return 1;
}

check_armors(string str){
object inv;
int x;
int woo;
inv = all_inventory(USER);
   for(x = 0; x < sizeof(inv); x++){
     if(inv[x]->query_worn() && inv[x]->query_type() == str){
      return 1;
	   }	
     }
 
	if(str == "amulet"){
		if(sh_armors[0]) return 1;
		return 0;
	}
        else if(str == "cloak"){
		if(sh_armors[1]) return 1;
		return 0;
	}
	else if(str == "boots"){
		if(sh_armors[2]) return 1;
		return 0;
	}
	else if(str == "armor"){
		if(sh_armors[3]) return 1;
		return 0;
	}
	else if(str == "gloves"){
		if(sh_armors[4]) return 1;
		return 0;
	}
	else if(str == "helmet"){
		if(sh_armors[5]) return 1;
		return 0;
	}
	else if(str == "belt"){
		if(sh_armors[6]) return 1;
		return 0;
	}
        else if(str == "bracelet"){
		if(sh_armors[7]) return 1;
		return 0;
	}
        else if(str == "shield"){
                return 0;
        }
	return 1;
}


query_sh_armors(){ return sh_armors; }
