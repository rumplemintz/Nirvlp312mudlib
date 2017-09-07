
inherit "room/room";

reset(arg) {
    object obj;
   if(arg) return;
    short_desc = "The Gaul" ;
    long_desc = "A path in the forest leads somewhere. You see\n" +
    "many strange tree that makes the forest not very safety.\n" +
    "Perhaps you'd better to change way.\n" ;
   dest_dir =
   ({
    "/players/hurtbrain/castello/dag/gaul/gaul39" ,"north" , 
    "/players/hurtbrain/castello/dag/gaul/gaul29" ,"south" , 
    "/players/hurtbrain/castello/dag/gaul/gaul40" ,"northwest" , 
    "/players/hurtbrain/castello/dag/gaul/gaul30" ,"southwest" 
    } ) ;
    set_light(1) ;
}