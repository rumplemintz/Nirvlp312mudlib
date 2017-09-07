move_stuff(cont) {
  object hob,ob;
  ob = first_inventory(cont);
  while(ob) {
    hob=next_inventory(ob);
    if(ob->is_money()) {
      cont->add_gold(ob->query_goldamt());
      ob->set_money(0);
    }
    else
      move_object(ob,environment(cont));
    ob=hob;
  }
  return 1;
}
