
id(str) { return str == "wepmaster"; }

m_attack() {
   int X;
   int Y;
   int V;
   int W;
   int Z;
   string how;
   string what;
   X = (this_player()->query_attrib("sta"));
   Y = (this_player()->query_attrib("str"));
       while(X>4) {
       Y = (Y/2);
       Z = (random(20));
       if(Z<X) {
       V = (random(Y+16));
       W = (W+(V));
    how = " to small fragments";
    what = "massacre";
    if (V < 30) {
      how = " with a bone crushing sound";
      what = "smashed";
    }
    if (V < 20) {
      how = " very hard";
      what = "hit";
    }
    if (V < 10) {
      how = " hard";
      what = "hit";
    }
    if (V < 5) {
      how = "";
      what = "hit";
    }
    if (V < 3) {
      how = "";
      what = "grazed";
    }
    if (V == 1) {
      how = " in the stomach";
      what = "tickled";
    }
    write("You " + what + " " + this_player()->query_attack()->query_name() + how + ".\n");
    say(this_player()->query_name() + " " + what + " " + this_player()->query_attack()->query_name() + how +
		".\n");
}
       X = (X - 5);
}
         this_player()->query_attack()->hit_player(W);
}
