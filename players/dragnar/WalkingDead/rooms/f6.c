inherit "players/dragnar/WalkingDead/rooms/WalkingDeadRM";

#include <ansi.h>

reset(arg) {
	if(arg) return;
  
  short_desc = "King County "+HIG+"Forest"+NORM;
  set_light(1);
  items=({
   "ferns","The ferns are a "+GRN+"forest green"+NORM+" and are 10 inches tall",
   "forest",
"The trees grow sparse at this point as the forest approaches the "+GRY+"cliff"+NORM+".\n\
Closer to the "+GRY+"cliff"+NORM+" the trees are dwarfed and the "+GRN+"ferns"+NORM+" start\n\
to take over. The forest continues north along the cliff edge and\n\
east back toward the road. South the forest grows thick and a\n\
passage in that direction is impossible",
    "trees",
"Less dominating than further to the east, the trees here are fairly\n\
sparse. Most of the trees here are smaller leafy trees like walnut\n\
and buck-thorn. The canopy here allows "+HIY+"sunlight"+NORM+" in and somehow makes\n\
it easier to breathe. The trees growing down the cliff are smaller\n\
than the ones growing in the forest due to the rock limiting\n\
their root system",
    "moss",
"Whatever type of moss this is, it doesn't seem to follow the standard\n\
of only growing on the north sides of the trees",
    "leaves",
"Many shades of "+GRN+"green"+NORM+", the leaves gently sway in the breeze. They are\n\
beautiful, but they cause a sense of restriction.  Anything could be\n\
hiding in these trees with their leaves giving perfect cover",
    "cliff",
"The cliff is not exactly vertical, but it would be almost impossible\n\
to traverse down it safely. Ferns and other ground cover grow on the\n\
rock face wherever they can find a crack, and occasionally small\n\
trees will even take root. The cliff runs for 75 feet and a stream\n\
runs along the edge of the cliff far below",
   "canopy","The canopy is mostly made up of "+GRN+"leaves"+NORM+" high overhead",
   "water","The "+HIY+"sunlight"+NORM+" blinds you as it reflects off the water below",
   "road","The road is not visible through the forest from this point",
   "stream",
"The stream looks very tranquil from the top of the cliff. The "+HIB+"water"+NORM+"\n\
flows slowly from north to the south and there is a slight bend in\n\
the stream at the bottom of the cliff which makes the stream wider at\n\
that point. "+HIY+"Sunlight"+NORM+" is reflected from the surface of the stream and\n\
dances through the dust in the air. It seems like the stream is 25\n\
feet across, but it is hard to judge from this height",
  });
  dest_dir=({
    "/players/dragnar/WalkingDead/rooms/f7","north",
    "/players/dragnar/WalkingDead/rooms/f5","east",
  });
  long_desc=
"The forest thins out here and the slope comes to an end at a "+GRY+"cliff"+NORM+"\n\
that runs down to the west and south. The cliff has no visible path\n\
down it. The forest continues north along the edge of the cliff and\n\
back toward the road to the east. South the forest dominates and the\n\
trees grow too dense to pass easily through it.\n";
  
  reanimate_corpse();
}

init() {
	::init();
  add_action("SouthEast","se");
  add_action("SouthEast","southeast");
}

SouthEast() {
  this_player()->move_player("southeast#/players/dragnar/WalkingDead/rooms/p1");
  return 1;
}