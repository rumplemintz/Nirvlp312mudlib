int xrooms,yrooms,totcol,ncol;
string box,room,color,roomcolor,boxcolor;
int xoud,youd,x,y;
int ff;
int push,err;
reset(arg) {
    roomcolor = allocate (25);
    boxcolor = allocate (25);
    room = allocate (5);
    box=allocate(5);
    for(ff=0;ff<5;ff++)
    {   room[ff]=allocate(5);
        box[ff]=allocate(5);
    }
xrooms = 4;yrooms = 4;
ncol = 15;
    totcol=22;
    color = ({
       "green","blue","red","black","white",
        "yellow","grey","purple","purper",
        "bordeaux","gold","silver","orange",
        "navy","mangaan","crimson","grass",
        "marine","magenta",
      "rose","indigo",
       "brown"});
    makeroomcolor();
    makeboxcolor();
    makerooms();
    x=2;y=1;
    youd=1;xoud=2;
}
push (arg)
{   xoud=x;youd=y;
    if(arg=="left") {x=x-1;}
    else
    {   if(arg=="right") {x=x+1;}
    else
    {   if(arg=="forward") {y=y+1;}
    else
    {   if(arg=="back") {y=y-1;}
    else
    {   write("Hmm... What way you wanted to push the block??\n");
        return 1;
    }}}}
    push = 1;
        allowed();
        if(push==1)
        {   movebox();
        }
    return 1;
}
movebox()
{   string otherbox;
    int a;
    otherbox=allocate(5);
    for(a=0;a<5;a++)
    {   otherbox[a]=allocate(5);
    }
    if(box[x][y]=="no")
    {   otherbox[x][y]=box[x][y];
        box[x][y]=box[xoud][youd];
        box[xoud][youd]=otherbox[x][y];
        write("You push the "+box[x][y]+" box to the "+
           room[x][y]+" room.\n");
        x=xoud;y=youd;
    }
    else
    {   if(room[x][y]=="hole")
        {
        write("WHOESSSHHHHHH!!!!!!!!!!!\n"+
            "You just pushed the box into the hole. It fell\n"+
            "a long way down, and i guess you have to start\n"+
            "this game all over again!\n");
        }
        else
    {   write("Hey man.. there is another box!\n");
        write("There is not room for two boxes in one room.\n");
        write("You fail to push....\n");
        x=xoud;y=youd;
    }
    }
    return 1;
}
allowed()
{
    if((y<0)||(x<0)||(y>3)||(x>3))
    {   y=youd;
        x=xoud;
    push = 0;
        write("Not that way, there is nothing..\n");
        return 1;
    }
    if(room[x][y]=="rock")
    {   write("You see a large rock. You can't go there..\n");
        x=xoud;y=youd;
    push = 0;
    err=1;
        return 1;
    }
    if(room[x][y]=="hole")
    {   write("Oh boy, this is the hole....\n");
        if(box[x][y]=="xx") {control();}
    }
    return 1;
}
init () 
{
   add_action("show","show");
   add_action("left","left");
   add_action("push","push");
   add_action("right","right");
   add_action("forward","forward");
   add_action("back","back");
   add_action("stop","stop");
    add_action("look","look");
}
look()
{   if(box[x][y]=="xx")
    {   return 0;
    }
    else
   {   if(box[x][y]=="no")
        {   write("You are in the empty "+room[x][y]+" room.\n");
        }
        else
        {   write("You see the "+box[x][y]+" box in the "+
                     room[x][y]+" room\n");
        }
    }
    return 1;
}
left()
{   xoud=x;youd=y;err=0;push=0;
    x=x-1;
   allowed();
    write("You see the "+box[x][y]+" box in the "+room[x][y]+" room.\n");
   return 1;
}
right()
{   xoud=x;youd=y;err=0;push=0;
    x=x+1;
    allowed();
    write("You see the "+box[x][y]+" box in the "+room[x][y]+" room.\n");
   return 1;
}
forward()
{   xoud=x;youd=y;err=0;push=0;
    y=y+1;
   allowed();
    write("You see the "+box[x][y]+" box in the "+room[x][y]+" room.\n");
   return 1;
}
back()
{   xoud=x;youd=y;err=0;push=0;
    y=y-1;
   allowed();
    write("You see the "+box[x][y]+" box in the "+room[x][y]+" room.\n");
   return 1;
}
show()
{   int xff,yff;
    string a;
    for(yff=yrooms-1;yff>-1;yff--)
    {   for(xff=0;xff<xrooms;xff++)
        {   if(box[xff][yff]=="no"||box[xff][yff]=="xx")
            {   write("           "); }
            else
            {   write(box[xff][yff]+"   "); }
        }
        write("\n");
    }
    return 1;
}
makeroomcolor() 
{
    int whatcolor, whichone;
    int k,l,m,n;
    int oldarray;
    int colnumber, newarray;
    int o;
    oldarray = allocate (25);
    newarray = allocate (25);
   colnumber = allocate (25);
    for(n=0;n<totcol;n++)
    {   oldarray[n]=n;
    }
    for(n=0;n<ncol;n++)
    {   k=0;
        whichone=random(totcol-n);
        whatcolor=oldarray[whichone];
        colnumber[n]=whatcolor;
        for(m=0;m<totcol;m++)
        {
            if(oldarray[m]==whatcolor) {m=m+1; }
            newarray[k] = oldarray[m];
            k=k+1;
        }
        roomcolor[n]=color[whatcolor];
        for(l=0;l<totcol;l++)
        {   oldarray[l] = newarray[l];
        }
    }
    return 1;
}
makeboxcolor()
{
    int whatcolor, whichone;
    int k,l,m,n;
    int oldarray;
    int colnumber, newarray;
    int o;
    oldarray = allocate (16);
    newarray = allocate (16);
    colnumber = allocate (16);
    for(n=0;n<ncol;n++)
    {   oldarray[n]=n;
    }
    for(n=0;n<ncol;n++)
    {   k=0;
        whichone=random(ncol-n);
        whatcolor=oldarray[whichone];
        colnumber[n]=whatcolor;
        for(m=0;m<ncol;m++)
        {
            if(oldarray[m]==whatcolor) {m=m+1; }
            newarray[k] = oldarray[m];
            k=k+1;
        }
        boxcolor[n]=roomcolor[whatcolor];
        for(l=0;l<ncol;l++)
        {   oldarray[l] = newarray[l];
        }
    }
    return 1;
}
makerooms()
{
    int n,x,y;
    n=0;
    for(y=0;y<yrooms;y++)
    {   for(x=0;x<xrooms;x++)
        {   if(((x==1)&&(y==2))||((x==3)&&(y==1)))
            {
            if(x==1) {room[x][y]="rock";}
             else {room[x][y]="hole";}
             box[x][y]="xx";
            }
        else {
        room[x][y]=roomcolor[n];
        box[x][y]=boxcolor[n];
        n=n+1;
        }
        }
    }
    box[0][0]="no";
    box[3][3]="no";
return 1;
}
control()
{   int xff,yff,ok;
    write("Hmm.. I wander if you pushed the right boxes into the"+
           "\n"+
          "right rooms. I'll have to check this, before i'm going"+
           "\n"+
          "to give you a reward for finishing this game correctly."+
           "\n");
    ok=1;
    for(yff=0;yff<yrooms;yff++)
    {   for(xff=0;xff<xrooms;xff++)
        {   if(box[xff][yff]!=room[xff][yff])
            {   ok=0;
            }
        }
    }
    if(ok==1)
    {   write("Yoho!! This is incredible...\n"+
              "You made it!!! Congrats.\n");
    }
    else
    {   write("Nope, you were wrong. (Like I thought).\n"+
              "the game is a little harder than you thought before, huh?\n"+
              "Anyway, you have to start all over again.\n");
    }
    destruct(this_object());
}
