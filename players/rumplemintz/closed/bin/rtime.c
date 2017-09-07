status
rtime()
{
  int min, hr, sec;

  write("The current ctime time is "+ ctime(time()) +".\n");
  write("The current ctime it "+ ctime() +".\n");
  write("The current time is "+time()+".\n");
  write("\nCtime 4..15 : "+ ctime(time())[4..15] +".\n");
  write("Ctime 4..15 and 20..23 : "+ ctime(time())[4..15] +" "+
                                     ctime(time())[20..23] +".\n");
  write("Ctime no args : " + ctime() + " .\n");
  min = atoi(ctime()[14..15]);
  hr = atoi(ctime()[11..12]);
  write("After to_int, min = " + min + ", and hr = " + hr + ".\n");
  return 1;
}
