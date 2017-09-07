#pragma strong_types

inherit "obj/treasure";

string *Styles;
string *Hits;


void reset(int arg) {
  if (arg) return;
  ::reset();
  set_name("tester");
  set_short("Tester");
  set_long("This is a test object to test various stuff.\n" +
           "Use the 'test' command to see what it does currently\n");
  set_weight(0);
  set_value(0);
  Styles = ({ "Style One",
              "Style Two",
              "Style Three",
              "Style Four"
           });
  Hits = ({ "Hit One",
            "Hit Two",
            "Hit Three",
            "Hit Four"
         });
}

void init() {
  ::init();
  add_action("test_func", "test");
}

int test_func() {
  write(Styles[random(sizeof(Styles))] + "\n");
  write(Hits[random(sizeof(Hits))] + "\n");
  return 1;
}