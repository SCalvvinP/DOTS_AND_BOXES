/* IMPLEMENTATION OF DOTS AND BOXES
   Submitted by Sunjay Calvvin P(260)
			Anush Kumar(216)
			Roja S Rajan(251)
			Vishnu G(263)*/


 #include<stdio.h>
 #include<string.h>
 #include<stdio.h>
 #include <GL/glut.h>
 #include<time.h>
 #include<math.h>
 #include<string.h>
  int ww = 400, wh = 400;
  float fillCol[3] = {0.4,0.0,0.0};
  float borderCol[3] = {0.0,0.0,0.0};    // black colour for the border
  int point_size = 0;
  int line_size = 0;
  int vert_line_size = 0;
  int square_filled = 0;                // till sqquare_filled < ((total_row_no - 1) * (total_col_no - 1))
  int total_squares = 16;              //  (total row -1) * (total col -1)

  int compliment = 0;          // initially 0 changes to 1 on every iteration of j loop
  int cur_player = 0;          // current player 0 represent player1 and 1 represent player2
  int cur_user_flag = 1;       // to know whether the current user has scored a point
  int user_points[3];
  int cur_player_color =0;
                                // user_points[1] for user1 and user_points[2] for user2
  int winner;
  char str4[] = " Player 1 wins .";
  char str5[] = " Player 2 wins .";
  char draw[] = "Draw.";
  int c_x,c_y;

  struct POINTe
  {
        int X;
        int Y;
  };

  struct line
  {
      struct POINTe p1;          // point 1
      struct POINTe p2;          // point 2
      struct POINTe p3;
      struct POINTe p4;
      int flag;                 // flag whether the line exists or not
      int filled;               // flag initially equal to zero
      int horrizontal;          // horizontal =1, vertical = 0
  }L[100];

  struct vertical_line
  {
    int line_no;
    int value;              // either 0 or 1
}VL[50];

  int X1 = 40,Y1 = 360,X2 = 50,Y2 = 350;
  void setPixel(int pointx, int pointy, float f[3])
  {
      if(cur_player == 0)
      {
       glBegin(GL_POINTS);
            //glColor3fv(f);
            glColor3f(1.0f, 0.0f, 0.0f);   //red
            glVertex2i(pointx,pointy);
           // glLineWidth(200);                 //test line
       glEnd();
       glFlush();
       glColor3f(0.0f, 0.0f, 0.0f);
      }
      else if(cur_player == 1)
      {
          glBegin(GL_POINTS);
          //glColor3fv(f);
           glColor3f(0.0f, 1.0f, 0.0f);    //green
            glVertex2i(pointx,pointy);
           // glLineWidth(200);                 //test line
       glEnd();
       glFlush();
       glColor3f(0.0f, 0.0f, 0.0f);

      }
  }
  void getPixel(int x, int y, float pixels[3])
  {
       glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,pixels);
  }
  void drawPolygon(int x1, int y1, int x2, int y2)
  {
       glColor3f(0.0,0.0,0.0);
       glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x1, y2);
       glEnd();
       glBegin(GL_LINES);
            glVertex2i(x2, y1);
            glVertex2i(x2, y2);
       glEnd();
       glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
       glEnd();
       glBegin(GL_LINES);
            glVertex2i(x1, y2);
            glVertex2i(x2, y2);
       glEnd();
       glFlush();
  }
  void boundaryFill4(int ,int ,float [],float []);
  void output();
  void print_score(int player,int score);
  void horrizontal(int line_number);
  void infinite_wait();
  void print_chance();
  void myinit();
  void mouse(int,int,int,int);

  void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius)
 {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
    //GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * (22/7);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for(i = 0; i <= triangleAmount;i++) {
        glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}
  void display()
  {
       int i = 0,j = 0;//,count = 0;
       int X1 = 40,Y1 = 360,X2 = 50,Y2 = 350;
       glClearColor(0.4,0.3,0.1,1.0);
                                                //glClearColor(1.0,1.0,1.0,1.0);glClearColor(0.6,0.8,0.1, 1.0);
       glClear(GL_COLOR_BUFFER_BIT);
                                                                        // to initailise user points to 0
       user_points[0] = 0;
       user_points[1] = 0;
       user_points[2] = 0;

       for(i=0;i<5;i++)
       {
       	for(j=0;j<5;j++)
       	{
       	//	drawPolygon(X1,Y1,X2,Y2);     //150,250,200,300
       	 //printf("\nbox points :%d %d",X1,Y1);
            glFlush();
            if(j<4)                    //     j < col_length,   horizontal line
            {
            glColor3f(0.0,0.0,0.0);
            glBegin(GL_LINES);
                glVertex2i(X1, Y1);
                glVertex2i(X1+50, Y1);
            glEnd();

            glColor3f(0.0,0.0,0.0);
            glBegin(GL_LINES);
            glVertex2i(X1, Y1-10);
            glVertex2i(X1+50, Y1-10);
            glEnd();

            //printf("\n HL %d\n",line_size);

            L[line_size].flag = 1;          // line exists
            L[line_size].filled = 0;        // to initialise the line to not filled
            L[line_size].horrizontal = 1;   // horrizontal line
            L[line_size].p1.X = X1;
            L[line_size].p1.Y = Y1;

            L[line_size].p2.X = X1+50;
            L[line_size].p2.Y = Y1;

            L[line_size].p3.X = X1;
            L[line_size].p3.Y = Y1-10;

            L[line_size].p4.X = X1+50;
            L[line_size].p4.Y = Y1-10;
            //line_size++;
            if(line_size>=36)
                {line_size+=2;}
            else
                {line_size++;}


          }

          if(i<4)                     // if not first row,  vertical line
          {
            glColor3f(0.0,0.0,0.0);
            glBegin(GL_LINES);
                glVertex2i(X1, Y1);
                glVertex2i(X1, Y1-50);
            glEnd();
                                                                   // to fill squares 1.000, 0.894, 0.710
            glColor3f(0.0,0.0,0.0);
            glBegin(GL_LINES);
                glVertex2i(X1+10, Y1);
                glVertex2i(X1+10, Y1-50);
            glEnd();

            //printf("\n VL %d\n",line_size);

            L[line_size].flag = 1;          // line exists
            L[line_size].filled = 0;        // initialise the line to not filled
            L[line_size].horrizontal = 0;   // vertical line
            L[line_size].p1.X = X1;
            L[line_size].p1.Y = Y1;

            L[line_size].p2.X = X1;
            L[line_size].p2.Y = Y1-50;

            L[line_size].p3.X = X1+10;
            L[line_size].p3.Y = Y1;

            L[line_size].p4.X = X1+10;
            L[line_size].p4.Y = Y1-50;

            VL[vert_line_size].line_no = line_size;
            VL[vert_line_size].value = compliment;
                                                                // printf("line no is %d \n",VL[vert_line_size].line_no);     // check
                                                                // printf("value is %d \n ",VL[vert_line_size].value);
            vert_line_size++;
            compliment = compliment ^ 1;  // to take the compliment take the xor
                                            // line_size++;
           if(line_size>36)
                {line_size+=2;}
            else
                {line_size++;}
          }
            point_size++;
            //glFlush();
       		X1 += 50;
       		X2 += 50;
       		glFlush();
       	}                           // end of j loop (inner loop)
       	X1 = 40;
       	X2 = 50;
       	Y1 -= 50;
       	Y2 -= 50;
       }

      //----CIRCLE PRINTING---
        glColor3f(1.0f, 0.0f, 0.8f);
        X1=40;X2=50;Y1=350;Y2=360;
        c_x=(X1+X2)/2;
        c_y=(Y1+Y2)/2;
        for(i=0;i<5;i++)
        {   for(j=0;j<5;j++)
            {
               // printf("\ncircle points :%d %d",c_x,c_y);
            drawFilledCircle(c_x,c_y,6);
            c_x += 50;
           // c_y += 50;
            }
            c_x =(X1+X2)/2;
            Y1 -= 50;
            Y2 -= 50;
            c_y =(Y1+Y2)/2;
            //glFlush();
        }
        glColor3f( 0.0, 0.0, 0.0 );
        glRasterPos2f(150,150);              // 75
                                                //print_vertical_line();           // end of i loop (outer loop)
        printf("\n\n");
        glFlush();

  }
void boundaryFill4(int x,int y,float fillColor[3],float borderColor[3])
  {
      //if(x>=40 && x<=240 && y>=161 && y<=361 )
      {
       float interiorColor[3];
       getPixel(x,y,interiorColor);
       if((interiorColor[0]!=borderColor[0] && (interiorColor[1])!=borderColor[1] && (interiorColor[2])!=borderColor[2]) && (interiorColor[0]!=fillColor[0] && (interiorColor[1])!=fillColor[1] && (interiorColor[2])!=fillColor[2]))
       {
            setPixel(x,y,fillColor);
            boundaryFill4(x+1,y,fillColor,borderColor);  //delay(0.1);
            boundaryFill4(x-1,y,fillColor,borderColor);  //delay(0.1);
            boundaryFill4(x,y+1,fillColor,borderColor);  //delay(0.1);
            boundaryFill4(x,y-1,fillColor,borderColor);  //delay(0.1);
       }
      }
  }
void horrizontal(int line_number)
{

    int fillx=0,filly=0;
    float Colour[3] = {0.6,0.8,0.1};
    int flag1 = 0,flag2 = 0, i;
    cur_user_flag = 0;                                               // no points
    i = line_number;
    L[i].filled = 1;                                                     // the line is filled
    if((i-9)>=0 && L[i-9].filled == 1)                                  // filled == 1 means the line is filled
    {
        if((i-8)>=0 && L[i-8].filled == 1)
        {
            if(i==15||i==24||i==33||i==42)
            {
             if(((i-8)+1)<=42 && L[i-7].filled == 1) //39
            {
                //printf("\n 2 upper half forms  a square \n");
                 fillx=(L[i].p1.X+L[i].p2.X)/2;;
                 filly=L[i].p1.Y+25;
                 flag1 = 1;           // upper half forms a square
                 total_squares--;
                 user_points[cur_player + 1]++;
                 boundaryFill4(fillx,filly,Colour,borderCol);
                 printf("\n");
                 printf("\nplayer %d  point  %d  \n",cur_player+1,user_points[cur_player+1]);

            }

            }
            else
            {
            if(((i-8)+2)<=42 && L[i-6].filled == 1) //39
                {
                fillx=(L[i].p1.X+L[i].p2.X)/2;;
                filly=L[i].p1.Y+25;
                                                                    //printf(" point is %d %d \n",fillx,filly);
                flag1 = 1;                                           // upper half forms a square
                total_squares--;
                user_points[cur_player + 1]++;
                boundaryFill4(fillx,filly,Colour,borderCol);
                printf("\nplayer %d  point  %d  \n",cur_player+1,user_points[cur_player+1]);
                }
            }
        }
    }

    if((i+9)<= 42 && L[i+9].filled == 1)                    //to check lower half
    {
        if((i+1)>=0 && L[i+1].filled == 1)
        {
            if(i==6||i==15||i==24||i==33)
            {
                if((i+2)<=42 && L[i+2].filled == 1)//39
            {
                                                                        //printf("\n2 lower half forms  a square \n");
                fillx=(L[i].p3.X+L[i].p4.X)/2;;
                filly=L[i].p1.Y-20;
                                                                        //printf(" point is %d %d \n",fillx,filly);
                flag2 = 1;
                total_squares--;
                user_points[cur_player + 1]++;
                boundaryFill4(fillx,filly,Colour,borderCol);
                printf("\nplayer %d  point  %d  \n",cur_player+1,user_points[cur_player+1]);
            }

            }
            else
            {
            if(((i+1)+2)<=42 && L[i+3].filled == 1)//39
            {
                                                                        //printf("\n1 lower half forms  a square \n");
                fillx=(L[i].p3.X+L[i].p4.X)/2;;
                filly=L[i].p1.Y-20;
                                                                        //printf(" point is %d %d \n",fillx,filly);
                flag2 = 1;
                total_squares--;
                user_points[cur_player + 1]++;
                boundaryFill4(fillx,filly,Colour,borderCol);
                printf("\nplayer %d  point  %d  \n",cur_player+1,user_points[cur_player+1]);
            }
            }
        }
    }
    if(flag1 == 1 || flag2 == 1)    // if the user gets the point
    {
        cur_user_flag = 1;          // to indicate that the current user secured a point
    }
}

void vertical(int line_number)
{
    int fillx=0,filly=0;
    float Colour[3] = {0.6,0.8,0.1};
    int flag1 = 0,flag2 = 0,i,x,val;
    cur_user_flag = 0;
    L[line_number].filled = 1;
//search for the vertical line
    for(i=0;i<vert_line_size;i++)
    {
        if(VL[i].line_no == line_number)
        {
            val = VL[i].value;
            break;
        }
    }
    if(val == 0)
    {x = 2;}
    if(val == 1)
    {x = 1;}
    i = line_number;
    if(i==8||i==17||i==26||i==35)                           //for checking left half of the vertical line
    {
        if((i-1)>=0 && L[i-1].filled == 1)
        {
        if((i-2)>=0 && L[i-2].filled == 1)
        {
            if((i+7)<=42 && L[i+7].filled == 1)//39
            {
                                                            //printf("\n2 left half forms  a square \n");
                filly=(L[i].p1.Y+L[i].p2.Y)/2;;
                fillx=L[i].p1.X-25;
                                                            //printf(" point is %d %d \n",fillx,filly);
                flag1 = 1;
                total_squares--;
                user_points[cur_player + 1]++;
                boundaryFill4(fillx,filly,Colour,borderCol);
                printf("\nplayer %d  point  %d  \n",cur_player+1,user_points[cur_player+1]);
            }
        }
    }

    }
    else
    {
    if((i-2)>=0 && L[i-2].filled == 1)
    {
        if(((i-1)-2)>=0 && L[i-3].filled == 1)
        {
            if((i+6)<=42 && L[i+6].filled == 1)
            {
                                                            //printf("\n1 left half forms  a square \n");
                filly=(L[i].p1.Y+L[i].p2.Y)/2;;
                fillx=L[i].p1.X-25;
                                                            //printf(" point is %d %d \n",fillx,filly);
                flag1 = 1;
                total_squares--;
                user_points[cur_player + 1]++;
                boundaryFill4(fillx,filly,Colour,borderCol);
                printf("\nplayer %d  point  %d  \n",cur_player+1,user_points[cur_player+1]);
            }
        }
    }
    }


    if((i-1)>=0 && L[i-1].filled == 1)                      // for checking right half of the vertical line
    {
        if((i+8)<=42 && L[i+8].filled == 1)
        {
            if(i==7||i==16||i==25||i==34)
            {
            if((i+1)<=42 && L[i+1].filled == 1)
            {
                                                            //printf("\n2right half forms  a square \n");
                filly=(L[i].p1.Y+L[i].p2.Y)/2;;
                fillx=L[i].p1.X+25;
                                                            //printf(" point is %d %d \n",fillx,filly);
                flag2 = 1;
                total_squares--;
                user_points[cur_player + 1]++;
                boundaryFill4(fillx,filly,Colour,borderCol);
                printf("\nplayer %d  point  %d  \n",cur_player+1,user_points[cur_player+1]);
            }
            }
            else
            {
                 if((i+2)<=42 && L[i+2].filled == 1)
                {
                                                        //printf("\n1right half forms  a square \n");
                filly=(L[i].p1.Y+L[i].p2.Y)/2;;
                fillx=L[i].p1.X+25;
                                                        //printf(" point is %d %d \n",fillx,filly);
                flag2 = 1;
                total_squares--;
                user_points[cur_player + 1]++;
                boundaryFill4(fillx,filly,Colour,borderCol);
                printf("\nplayer %d  point  %d  \n",cur_player+1,user_points[cur_player+1]);
                }
            }
        }
    }
   // boundaryFill4(fillx,filly,Colour,borderCol);
    if(flag1 == 1 || flag2 == 1)        // if the user gets a point
    {
        cur_user_flag = 1;          // to indicate that the current user secured a point
    }
}

void get_line_pos(int x1,int y1)
{
    int i=0;
    for(i=0;i<line_size;i++)
    {
        if(L[i].horrizontal == 1 && L[i].flag == 1)
        {
            if((x1 > L[i].p1.X) && (x1 < L[i].p2.X))
            {
                if((y1 < L[i].p1.Y) && (y1 > L[i].p3.Y))
                {
                                                            //printf("\nThe horrizontal box is %d \n",i);
                    horrizontal(i);                         // for the horrizontal line
                    break;
                }
            }
        }
        if(L[i].horrizontal == 0 && L[i].flag == 1)
        {
            if((x1 > L[i].p1.X) && (x1 < L[i].p3.X))
            {
                if((y1 < L[i].p1.Y) && (y1 > L[i].p2.Y))
                {
                                                            //printf("\nThe vertical box is %d \n ",i);
                    vertical(i);                            // for the vertical line
                    break;
                }
            }
        }
    }
}

  void infinite_wait()
  {
      //while(1);
      //exit(1);
       int result = MessageBox(NULL, "RESTART", "DOTS AND BOXES",  MB_YESNOCANCEL);
      switch (result)
        {
            case IDYES:
            glutDisplayFunc(display);
            myinit();
            glutMouseFunc(mouse);
            glutMainLoop();// Do something
            break;
            case IDNO:
            // Do something
            break;
            case IDCANCEL:
            // Do something
            break;
}
  }

  void printwinner()
  {
      int len,i,point_print;
      char text[128];
      if(user_points[1]>user_points[2])
      {
            printf("\nWinner is Player 1 with point %d \n,",user_points[1]);
            winner = 1;
            glColor3f( 0.0, 0.0, 0.0 );
            glRasterPos2f(150,150);            // 75
            len = (int)strlen(str4);
            for (i = 0; i < len; i++) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str4[i]);
            }

            sprintf(text, "Player 1 wins. Points: %d", user_points[1]);
            MessageBox(NULL, text, "GAME OVER !!!", MB_OK);
            //MessageBox(0,"Player one wins.","Game Over!!",1);
      }
      else if(user_points[1]<user_points[2])
      {
            printf("\nWinner is Player 2 with point %d \n",user_points[2]);
            winner = 2;
            glColor3f( 1.0, 1.0, 1.0 );
            glRasterPos2f(150,150);            // 75
            len = (int)strlen(str5);
            for (i = 0; i < len; i++) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str5[i]);
            }
            sprintf(text, "Player 2 wins. Points: %d", user_points[2]);
            MessageBox(NULL, text, "GAME OVER !!!", MB_OK);
      }
      else{
            printf("\ndraw\n");
            glColor3f( 1.0, 1.0, 1.0 );
            glRasterPos2f(150,150);            // 75
            len = (int)strlen(draw);
            for (i = 0; i < len; i++) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, draw[i]);}
            MessageBox(0,"DRAW","GAME OVER !!!!",1);
      }
  }

  void mouse(int btn, int state, int x, int y)
  {
       if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
       {
            int xi = x;
            int yi = (wh-y);
            float interiorColor[3];                 // to get the colour of the interior point
            float Colour[3] = {0.6,0.8,0.1};        // 0.6,0.8,0.1, 1.0
            getPixel(x,y,interiorColor);
                                                   // printf("\nwhen mouse %d %d",xi,yi);
            get_line_pos(xi,yi);                    //cur_player + 1 as parameter
            printf("\ncurrent player is %d \n",cur_player+1);
            boundaryFill4(xi,yi,Colour,borderCol);
            if(cur_user_flag == 0)                  // no points for the current user
            {
                cur_player = cur_player ^ 1;        // to switch the players
            }

            if(total_squares == 0 || ((user_points[1]+user_points[2])==16))   // game completed
            {   printwinner();
                printf("\nGame Over");
                infinite_wait();
            }

        }
  }
  void print_chance()
{
        int val;
        val = cur_player + 1;
        printf("\ncurrent player is %d \n",val);     // test
}

  void myinit()
  {
       glViewport(0,0,ww,wh);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
       glMatrixMode(GL_MODELVIEW);
       glLineWidth(3);
  }
  int main(int argc, char** argv)
  {

        if( MessageBox(NULL,"\t     START GAME","DOTS AND BOXES",1) == IDOK    )
        {
       glutInit(&argc,argv);
       glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
       glutInitWindowSize(ww,wh);
       glutCreateWindow("Dot-and-Boxes");
       glutDisplayFunc(display);
       myinit();
       glutMouseFunc(mouse);
       glutMainLoop();
       return 0;
        }

  }
