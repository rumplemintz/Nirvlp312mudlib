#include "../defs.h"

cmd(str){
 if(!str){
  write(ROD+"The Realm of Death disdains cowardice in their servants.\n");
  return 0;
 }
 if(str != "off"){
   write(ROD+"The Realm of Death disdains your cowardice.\n");
   return 0;
 }
   write(ROD+"The Realm of Death is pleased with your bravery.\n");
   return 0 ; 
}