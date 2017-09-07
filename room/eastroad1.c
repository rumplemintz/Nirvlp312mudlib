#include "room.h"

init() {
     ::init();
     add_action("look", "look");
     add_action("look", "l");
     add_action("look", "examine");
}

look(str) {
  if (!str) return 0;
  if (str == "at temple"||str=="at walls"||str=="at granite walls"
     ||str=="at wall"||str=="at granite wall"){
    write("The thirty foot high walls block your view of the temple\n"+
      "and anything going on inside. They are of a quality construction\n"+
      "with anti-climbing spikes located near the top.\n");
    return 1;
  }
  if (str == "at gate" ||str=="bronze gate"||str=="menacing bronze gate"){
    write("Beyond this small well secured gate all you can see is \n"+
      "more of the granite wall. The entrance path takes several turns\n"+
      "through a walled passageway to prevent people from peering\n"+
      "inside.\n");
    return 1;
  }
   return 0;
}    

THREE_EXIT("room/eastroad2","north",
         "room/vill_shore","south",
         "room/temple/path","west",
"East road",
"The East Road runs north-south parallel to the village shore. The\n"+
"road is paved with a fine gravel making travel easy on the feet.\n"+ 
"Sitting off the road to the west after a small incline is a temple.\n"+
"The walls obscure all vision of the temple itself. You can hear the\n"+
"clashing of weapons from beyond the temple's high granite walls, and\n"+
"menacing bronze gate.\n", 1)
