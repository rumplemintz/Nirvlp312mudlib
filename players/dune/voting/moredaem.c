/* 
 * General 'more' command with Nirvana guild add-ons.
 *   --Dune (retrieved code from /obj/_more.c)
 */
#include "DEFS.h"

#define SEARCH_LINES   10000


private int lines, eof, temp_file;
private int top_line, page_size;
private string fname, swap_file;
private string rem_expr;
private mixed *mark;


/* prototypes */
int help();
int more_file( string file );
int pager( string file );
int find_menu(string str);
string shorted_file(string str);


status view_doc(string str, string directory)
{
  string file, topic, all;

  if(sscanf(str, "%s %s", topic, all)) {
    file = directory +"/"+ topic;
    file = shorted_file(file);
    if(all == "all") {
      if (file_size(file) >= 0) {
        cat(file);
        return 1; 
      }
      else {
        write("There is no help on that fax topic.\n");
        return 1; 
      }
    }
    if(all != "all") return 0;
  }
  if(sscanf(str, "%s", topic)) {
    file = directory +"/"+ topic;
    file = shorted_file(file);
    if (file_size(file) >= 0) {
       if(find_menu(file)) {
         cat(file);
         return 1; 
       }
       more_file(file);
       return 1; 
    }
    return 0; 
  }
  return 0;
}


int find_menu(string str)
{
  string menustr;
  if(sscanf(str, "%smenu.txt", menustr) == 1) return 1;
  if(sscanf(str, "%sshort.txt", menustr) == 1) return 1;
  return 0;
}


string shorted_file(string str)
{
  string files;
  files = str + "short.txt";
  if(file_size(files) >= 0) str = files;
  else str = str + ".txt";
  return str;
}


private int get_oid()
{
  string junk;
  int oid;

  sscanf( file_name( this_player() ), "%s#%d", junk, oid );
  return oid;
}


private void swap_in()
{
  swap_file = SAVEROOT+"/tmp/m" + get_oid();
  temp_file = 0; mark = 0; rem_expr = 0; eof = 0;
  if( ! restore_object( swap_file ) )
    write( "** Swap file corrupted. **\n" );
}


private void swap_out()
{
  save_object(swap_file);
  temp_file = 0;
}


static void write_menu_bar()
{
  int max;
  string cut;
  /* commented out by wocket 11/99
  cut = "@@@@@@@@@@@@@@@@@@@@";
  */
  cut = "~~~~~~~~~~~~~~";
  max = top_line + page_size - 1;
  if( max > lines ) max = lines;
  write(cut+" ");
  write(top_line+"-"+max+" ("+lines+") ");
  write((max * 100 / lines)+"% (help ?, q to quit) ");
  write(cut+" ");
}

 
static void display_page()
{
  int n, ps;

  ps = page_size;
  if( top_line + ps > lines ) ps = lines - top_line + 1;
  n = cat( fname, top_line, ps );
  if( top_line + n > lines ) eof = 1;
}
 

static void cont_more()
{
  write_menu_bar();
  input_to( "get_more_com" );
  swap_out();
}


private int get_mark( string str )
{
  int n;

  if( ! sscanf( str, "%d", n ) ) {
    write( "Format should be \"m#\" where # is mark number.\n" );
    n = 0;
  }
  else if( n > 5 || n < 1 ) {
    write( "Marks must be in range 1-5.\n" );
    n = 0;
  }
  return n;
}


private int search_string( string str ) 
{
  int tmp_line;
  string tmp1;
  string tmp2;

  tmp_line = top_line + page_size / 2;
  tmp1 = read_file( fname, tmp_line, SEARCH_LINES );
	
  while( tmp1 && sscanf( tmp1, "%s" + str, tmp2 ) != 1 ) {
    tmp_line += SEARCH_LINES;
    tmp1 = read_file( fname, tmp_line, SEARCH_LINES );
  }

  if( tmp2 ) {
    while( sscanf( tmp2, "%s\n%s",tmp1, tmp2 ) )
      tmp_line++;
    tmp_line -= 2;    
    return tmp_line;  
  }
  return top_line;
}


static void get_more_com( string str )
{
  int n, cmd;
  int rem_line;
  string path;

  swap_in();
  if( ! str || str == "" ) str = " ";
  if( sscanf( str, "%d%s", n, str ) != 2 ) n = 1;
  if( ! str || str == "" ) str = "G";
  cmd = str[0]; str = extract( str, 1 );
  switch( cmd )
    {
    case 'G':			/* goto line */
      top_line = n;
      break;

    case ' ':			/* next page */
      if( ! eof )
	{
	  top_line += n * page_size;
	  break;
	}

    case 'q':			/* quit */
      if( temp_file && sscanf( fname, SAVEROOT+"/tmp/%s", path ) == 1 )
	rm( fname );
      rm( "/"+swap_file+".o" );
      temp_file = 0;
      return;

    case '?':			/* help */
      cat( "/"+SAVEROOT+"/moredaem.h" );
      return cont_more();

    case 'b':			/* previous page */
      top_line -= n * page_size;
      break;

    case 'e':			/* switch files */
      if( temp_file )
	{
	  write( "Cannot switch out of a temporary file.\n" );
	  return cont_more();
	}
      while( str[0] == ' ' ) str = extract( str, 1 );
      path = (string) this_player() -> get_path();
      str = (string) this_player() -> add_paths( path, str );
      if( ! more_file( str ) )
	{
	  write( "File not found.\n" );
	  return cont_more();
	}
      return;

    case 'p':			/* switch page length */
      if( sscanf( str, "%d ", n ) ) page_size = n;
      if( page_size < 1 ) page_size = 1;
      if( page_size > 40 ) page_size = 40;
      write( "Page length is now " + page_size + ".\n" );
      return cont_more();

    case 'm':			/* mark line */
      if( ! fname )
	{
	  write( "Cannot place mark here.\n" );
	  return cont_more();
	}
      n = get_mark( str );
      if( n ) mark[n-1] = ({ fname, top_line, lines });
      return cont_more();

    case 'g':			/* goto mark */
      n = get_mark( str );
      if( ! mark[n-1] )
	{
	  write( "Mark not set.\n" );
	  return cont_more();
	}
      fname = mark[n-1][0];
      top_line = mark[n-1][1];
      lines = mark[n-1][2];
      break;
			
    case 'n':			/* Search for last r.e */
      if( rem_expr ) str = rem_expr;
      else str = "";

    case '/':			/* Search for a regular expresssion */
      if( ! str  || str == "" ) 
	{
	  write( "\nNo previous regular expression.\n\n" );
	  return cont_more();
	}
			
      rem_expr = str;
      rem_line = top_line;
      top_line = search_string( str );
      if( top_line == rem_line )
	{
	  write( "\nNo match.\n\n" );
	  return cont_more();
	}
      break;



    default:
      write( "Unknown command.\n" );
      return cont_more();
    }
  eof = 0;
  if( top_line < 1 ) top_line = 1;
  if( top_line > lines ) top_line = lines;
  display_page();
  cont_more();
}
 

int more_file( string str )
{
  string data;

  data = read_file( str );
  swap_file = SAVEROOT+"/tmp/m" + get_oid();
  if( ! data ) return 0;
  fname = str;
  top_line = 1;
  rem_expr = "";
  lines = sizeof( explode( data, "\n" ) );
  if( ! mark ) mark = allocate( 5 );
  data = (string) this_player() -> getenv( "LINES" );
  if( data && sscanf( data, "%d", page_size ) )
    {
      if( page_size < 1 ) page_size = 1;
      if( page_size > 40 ) page_size = 40;
    }
  else page_size = 20;
  eof = 0;
  display_page();
  cont_more();
  return 1;
}


varargs void more_pipe( string str, string fstr )
{
  fname = SAVEROOT+"/tmp/"+
    ( fstr ? fstr : (string) this_player() -> query_name() ) +
      "." + get_oid() + ".o";
  if( file_size( fname ) > 0 ) rm( fname );
  write_file( fname, str );
  temp_file = 1;
  more_file( fname );
}


void pager( string str )
{
  more_file( str );
}

 
int cmd_more( string arg )
{
  if ( ! arg || arg == "" )
    return help();
  arg = resolv_path( (string) this_player() -> get_path(), arg );
  if ( file_size( arg ) < 0 ) {
    notify_fail( arg + ": file not found.\n" );
    return 0;
  }
  more_file( arg );
  return 1;
}


int help()
{
  write(
"Command: more\nSyntax: more <filename>\n" +
"This command lets you use more to read a file.  This means\n" +
"that the file will be displayed one screenful at a time. \n" +
"You may call up the nest screenful by hitting <ENTER>.  If\n" +
"you want to goto a specific line then type that in and hit\n" +
"<ENTER>.  You can get further help from within more my using\n" +
"the ? command.\n" );
	return 1;
}
