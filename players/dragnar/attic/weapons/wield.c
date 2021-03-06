wield(str) {
   if (!id(str))
      return 0;
   if (environment() != this_player()) {
      /* write("You must get it first!\n"); */
      return 0;
   }
   if (wielded) {
      write("You already wield it!\n");
      return 1;
   }
   
   if(wield_func)
      if(!call_other(wield_func,"wield",this_object())) 
      return 1;
   if (call_other(this_player(), "query_level", 0) < 10) {
      write("You are confused by the multitude of buttons and the complicated sights.\n");
      write("This weapon is obviously too complicated for you.\n");
      say(call_other(this_player(),"query_name",0)+
         " failed to wield a heavy machine gun\n");
      return 1;
   }
   write("The weight of the machine gun feels reassuring...\n");
   wielded_by = this_player();
   call_other(this_player(), "wield", this_object());
   wielded = 1;
   return 1;
} /* wield */


