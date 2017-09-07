#define tp this_player()->query_name()
#define TP this_player()
inherit "room/room";
int t;
reset(int arg){
 if(!arg){
  set_light(1);
short_desc="Library of Ryllian";
long_desc=
 "You stand in the Library of Ryllian.  The walls are lined from marble floor\n"+
 "to marble ceiling with countless shelves of neatly alphabetized books and\n"+
 "scrolls.  There are scattered chairs and couches and tables set out for use\n"+
 "by library patrons.\n"+
 "Command: look at books\n";

items=({
 "scrolls","The walls are filled with shelves upon shelves of scrolls",
 "walls","The walls have been constructed from a fine polished white marble",
 "wall","The walls have been constructed from a fine polished white marble",
 "floor","The floor has been constructed from a fine polished white marble",
 "lantern","There are many magical flameless lanterns upon the walls",
 "chairs","There are many chairs here.  Perhaps you could <sit chair>",
 "chair","There are many chairs here.  Perhaps you could <sit chair>",
 "tables","There are many tables here for public use",
 "thable","There are many tables here for public use",
 "patrons","There are a few people here looking at various books",
 "books","Here are a list of books that you can read <read #>\n"+
    "Books 1-12",
 });

  dest_dir=({
 "/players/saber/ryllian/library.c","west",
           });
  }   }
init(){
 ::init();
  add_action("search","search");
   add_action("sit","sit");
  add_action("read","read");
}

search() {
 write("You find nothing\n");
say (tp +" searches the area\n");
 return 1;  }

sit(str)  {
  if(!str)  {
    write("Sit where?\n");
    return 1;
        }
  if(str == "chair")  {
    write("You sit down in a very comfortable chair.\n");
    say(tp+" sits down in one of the library chairs.\n");
    return 1;
        }
  if(str == "floor")  {
    write("You sit down on the floor.\n");
    say(tp+" sits down upon the floor.\n");
    return 1;
        }
  if(str == "table")  {
    write("You sit down upon the table.\n"+
      "The librarian arches an eyebrow at you.\n");
    say(tp+" sits down upon one of the tables.\n");
    return 1;
        }
  write("Sit down where?\n");
  say(tp+" looks around for a place to sit.\n");
  return 1;
        }

read(str)  {
  if(!str)  {
    write("To read: < read >  < book # >\n");
    return 1;
        }
  if(str == "1")  {
    say(tp+" reads a book.\n");
    write(
 "The Bards Guild was originally formed in the city of Ryllian under the\n"+
 "leadership of the now legendary Carthan <Harper> de Oro.  While proper\n"+
 "historians may point out that the precursor to the Bards Guild, namely\n"+
 "the University of Ryllian, existed before the guild, all will agree\n"+
 "that the true history of the Bards did not actually begin until \n"+
  "both groups were recognized as separate entities.  Under the brilliant, if\n"+
 "not somewhat erratic, leadership of Harper, the Bards became a separate\n"+
 "entity in the city of Ryllian.  Not content to passively collect\n"+
 "knowledge, the Guild began encouraging their members to travel out into\n"+
 "the world in search of it.  The knowledge thus collected was returned\n"+
 "to the Bards guild and recorded for preservation in the verses of songs\n"+
 "and poetry.\n");
    return 1;
        }
  if(str == "2")  {
    say(tp+" reads a book.\n");
    write(
 "  What has roots that nobody sees,\n"+
 "  Is taller than trees,\n"+
 "    Up, up it goes,\n"+
 "    And yet never grows?\n"+
 "      - A mountain\n\n"+
 "  Thirty white horses on a red hill,\n"+
 "    First they stomp,\n"+
 "    Than they chomp,\n"+
 "  Then they stand still.\n"+
 "      - Teeth\n\n");
    return 1;
        }

 if(str == "3")  {
    say(tp+" reads a book.\n");
    write(
 "   In every era, on every kingdom and region throughout the known\n"+
 "dimensions of magic and sorcery, traveling musicians wander across the\n"+
 "lands.  These musicians move from city to city, land to land, practicing\n"+
 "their profession and plying their trade as artists of sound and\n"+
 "information to masses hungry for both.  The best of these traveling\n"+
 "musicians belong to the guild of the Bards, a brotherhood of individuals\n"+
 "united under the common interests of both knowledge and music.\n\n");
    return 1;
        }

  if(str == "4")  {
    say(tp+" reads a book.\n");
    write(
 "Day                    Color       Musical Note\n\n"+
 "Day of the Dragon      Blue             G\n"+
 "Day of the Sun         Orange           D\n"+
 "Day of the Unicorn     Violet           B\n"+
 "Day of the Moon        Indigo           A\n"+
 "Day of the Gods        Green            F\n"+
 "Day of the Earth       Yellow           E\n"+
 "Day of the Phoenix     Red              C\n\n");
    return 1;
        }

if(str == "5")  {
    say(tp+" reads a book.\n");
    write(
 "	One subject in which Bards Guild members may claim specialization\n"+
 "is the art collecting and presenting knowledge.  All Bards are required\n"+
 "to become proficient in the art both of instrumental and vocal music.\n"+
 "Most can fluently speak many languages, and all study history.  Because\n"+
 "of this research, Bards can often identify objects and creatures unknown\n"+
 "to other.\n"+
 "	Bards have been known to put their music to many uses.  Tales are\n"+
 "quietly told of certain singers who have managed to beguile hostile\n"+
 "creatures with the sound of their voice, or of warriors whose recitation\n"+
 "of poetry in battle urges them on to greater heroics.  And while the\n"+
 "Guild may deny it, certain accomplished Bards have been seen accompanied\n"+
  "by wild animals supposedly conjured by the humming of a simple ditty!\n");
    return 1;
        }

if(str == "6")  {
    say(tp+" reads a book.\n");
    write(
 "  Voiceless it cries,\n  Wingless flutters,\n"+
 "  Toothless bites,\n  Mouthless mutters.\n      - Wind\n\n"+
 "  It cannot be seen, cannot be felt,\n"+
 "  Cannot be heard, cannot be smelt,\n"+
 "  It lies behind stars and under hills,\n"+
 "    And empty holes it fills.\n"+
 "  It comes first and follow after,\n"+
 "    Ends life, kills laughter.\n        - Dark.\n\n");
    return 1;
        }

if(str == "11")  {
    say(tp+" reads a book.\n");
    write(
 "Gods           Gender       Sphere\n\n"+
 "Larn           Male         Life and Protection\n"+
 "Arate          Female       Death and Disease\n"+
 "Hadinea        Female       Love & Music & Music\n"+
 "Sylvia         Female       War and Competition\n"+
 "Wyrd           Male         Time & Fate & Phophecy\n"+
 "Soli           Male         Sun & Light  (day)\n"+
 "Crysea         Female       Moon & Stars (night)\n\n");
  return 1;
       }

if(str == "8")  {
  say(tp+" reads a book.\n");
  write(
 "List of elements:\n\n"+
 "   Air\n   Fire\n   Earth\n   Water\n   Metal\n\n");
    return 1;
        }

if(str == "9")  {
    say(tp+" reads a book.\n");
    write(
 "  A box without hinges, key or lid,\n"+
 "  Yet golden treasure inside is hid.\n      - an Egg\n\n"+
 "  Alive without breath,\n  As cold as death\n"+
 "  Never thirsty, ever drinking,\n  All in mail never clinking.\n"+
 "      - a Fish\n\n");
    return 1;
        }

if(str == "10")  {
    say(tp+" reads a book.\n");
    write(
 "  This things all things devours:\n  Birds, beasts, trees, flowers;\n"+
 "  Gnaws iron, bites steel;\n  Grinds hard stone to meal;\n"+
 "  Slays king, ruins town;\n  And beats high mountain down.\n"+
 "      - Time\n\n");
    return 1;
        }

if(str == "7")  {
int NUMBER;
 NUMBER = (TP->query_attrib("mag")) + (TP->query_attrib("wil")) + (TP->query_attrib("int")) + (TP->query_attrib("pie"));
  say(tp+" reads a book.\n");
    write(
 "This is a book written for "+tp+".\n\n"+
 "I, Wyrd, god of Time and Fate and Phophecy have cast the dice\n"+
 "and determined that your personal bardic number is:\n\n"+
 "             "+NUMBER+"\n\n"+
 "Yes, I know, you wonder what to do with this number.\n"+
 "You must tell it to the youngest of the Bards, one who is within\n"+
 "the first circle of seven and whose name is within the sphere\n"+
 "of my sister Crysea.\n\n");
    return 1;
        }

if(str == "12")  {
  say(tp+" reads a book.\n");
  write(
 "I am music.  Servant and master am I; servant of the dead,\n"+

 "and master of the living.  Through me spirits immortal speak\n"+
 "the messages that make the world weep, and laugh and wonder and worship.\n"+
 "                                             - Anon\n\n");
  return 1;
        }

 write("There is no book by that number.\n");
  return 1;
        }