inherit "obj/treasure";
int W;

/*A Timing Device*/

reset(arg) {
  W = 7;
  if(arg) return;

  set_id("sandial");
  set_value(0);
  set_weight(10000);
  call_out("check_time",40);
}

check_time()  {
  if(W < 1)  {
    destruct(this_object());
  return 1;
  }  else  {
    W = W -1;
  call_out("check_time",40);
  return 1;
        }
return 1;
}
