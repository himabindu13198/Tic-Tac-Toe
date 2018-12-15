#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int board[3][3];	// board for gameplay
int turn;			// current move
int result;			// Result of the game
bool over;			// Is the game Over?

void bresen_line(int x1, int x2, int y1, int y2);
void bresenham_circle(int cx, int cy, int r);

/*
	Sets the board for Tic Tac Toe
*/
void Intialize()
{
	turn=1;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			board[i][j]=0;
	}
}
/*
	Called when any key from keyboard is pressed
*/
void OnKeyPress(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'y':
		if(over==true)
		{
			over=false;
			Intialize();
		}
		break;
		case 'n':
		if(over==true)
		{
			exit(0);
		}
		break;
		default:
			exit(0);
	}
}

/*
	Called when Mouse is clicked 
*/
void OnMouseClick(int button,int state,int x,int y)	
{
	if(over==false && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		if(turn==1)
		{
			if(board[(y-50)/100][x/100]==0)
			{
				board[(y-50)/100][x/100]=1;
				turn=2;
			}
		}
		else if(turn==2)
		{
			if(board[(y-50)/100][x/100]==0)
			{
				board[(y-50)/100][x/100]=2;
				turn=1;
			}
		}
	}	
}

/*
	Utility function to draw string 	
*/
void DrawString(void *font,const char s[],float x,float y)
{
	int i;
	glRasterPos2f(x,y);
	for(i=0;i<strlen(s);i++)
	{
		glutBitmapCharacter(font,s[i]);
	}
}

/*
	Function to draw up the horizontal and vertical lines
*/
void draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void DrawLines()
{
	glBegin(GL_LINES);
	glColor3f(0,0,0);
	
	bresen_line(100,100,50,340);
	bresen_line(200,200,340,50);
	bresen_line(0,300,150,150);
	bresen_line(0,300,250,250);
	
	glEnd();		
}
void bresen_line(int x1, int x2, int y1, int y2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = x2-x1;
	dy = y2-y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy) {
		draw_pixel(x, y);
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}

	} else {
		draw_pixel(x, y);
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}


/*
	Utility function to draw the circle
*/
void DrawCircle(float cx, float cy, float r) 
{
    bresenham_circle(cx,cy,r);
    glEnd();
}

void plot_point(int cx,int cy, int x, int y)
{
  int xc = cx, yc = cy;
  glBegin(GL_POINTS);
  glVertex2i(xc+x, yc+y);
  glVertex2i(xc+x, yc-y);
  glVertex2i(xc+y, yc+x);
  glVertex2i(xc+y, yc-x);
  glVertex2i(xc-x, yc-y);
  glVertex2i(xc-y, yc-x);
  glVertex2i(xc-x, yc+y);
  glVertex2i(xc-y, yc+x);
  glEnd();
} 		

void bresenham_circle(int cx, int cy, int r)
{
  int x=0,y=r;
  float pk=(5.0/4.0)-r;

  /* Plot the points */
  /* Plot the first point */
  plot_point(cx,cy,x,y);
  int k;
  /* Find all vertices till x=y */
  while(x < y)
  {
    x = x + 1;
    if(pk < 0)
      pk = pk + 2*x+1;
    else
    {
      y = y - 1;
      pk = pk + 2*(x - y) + 1;
    }
    plot_point(cx,cy,x,y);
  }
  glFlush();
}



/*
	Function to draw the cross and circle of Tic Tac Toe
*/
void DrawXO()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(board[i][j]==1)
			{
				glBegin(GL_LINES);
				bresen_line(50 + j * 100 - 25, 50 + j * 100 + 25,100 + i * 100 - 25,100 + i * 100 + 25);
				bresen_line(50 + j * 100 - 25, 50 + j * 100 + 25,100 + i * 100 + 25,100 + i * 100 - 25);
				glEnd();
			}
			else if(board[i][j]==2)
			{
				
				DrawCircle(50 + j*100 , 100 + i*100 , 25);
			}
		}
	}
}

/*
	Function to check if there is any winner 
*/
bool CheckWinner()
{
	int i, j;
	// horizontal check
	for(i=0;i<3;i++)
	{
		for(j=1;j<3;j++)
		{
			if(board[i][0]!=0 && board[i][0]==board[i][j])
			{
				if(j==2)
				{
					return true;
				}
			}
			else
				break;
		}
	}
	// vertical check
	for(i=0;i<3;i++)
	{
		for(j=1;j<3;j++)
		{
			if(board[0][i]!=0 && board[0][i]==board[j][i])
			{
				if(j==2)
					return true;
			}
			else
				break;
		}
	}
	// Diagonal check
	if((board[0][0]!=0 && board[0][0]==board[1][1] && board[0][0]==board[2][2]) 
	|| (board[2][0]!=0 && board[2][0]==board[1][1] && board[2][0]==board[0][2]))
		return true;
	return false;
}

/*
	function to check if there is draw
*/
bool CheckIfDraw()
{
	int i, j;
	bool draw;
	for(i=0;i<3;i++)
	{ 
		for(j=0;j<3;j++)
		{ 
			if(board[i][j]==0)
				return false;
		}
	}
	return true;	
}

/*
	Function to display up everything
*/
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);
	if(turn == 1)
		DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's turn", 100, 30);	
	else
		DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's turn", 100, 30);	
	
	DrawLines();
	DrawXO();
	
	if(CheckWinner() == true)
	{
		if(turn == 1)
		{
			over = true;
			result = 2;
		}
		else
		{
			over = true;
			result = 1; 
		}
	}
	else if(CheckIfDraw() == true)
	{
		over = true;
		result = 0;
	}
	if(over == true)
	{
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 100, 160);
		if(result == 0)
			DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 110, 185);
		if(result == 1)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 95, 185);
		if(result == 2)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 95, 185);
		DrawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue (y/n)", 40, 210);
	}
	glutSwapBuffers();
}

/*
	Function to reshape
*/
void Reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

/*
	Driver Function
*/
int main(int argc, char **argv)
{
	Intialize();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(550,200);
	glutInitWindowSize(300,350);
	glutCreateWindow("Tic Tac Toe");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(OnKeyPress);
	glutMouseFunc(OnMouseClick);
	glutIdleFunc(Display);
    glutMainLoop();
    return 0;
}
