#include <GL/freeglut.h>
#include<GL/glut.h>
#include <GL/gl.h>
GLfloat r,g,b;
GLint xstart=50,ystart=50;
GLint xend=450,yend=450;
void Init()
{
	glClearColor(1.0,1.0,1.0,1.0);
  	glMatrixMode(GL_PROJECTION);
  	gluOrtho2D(0,500,0,500);
	glClear(GL_COLOR_BUFFER_BIT);
}

void flood_fill(int x ,int y, pixel oldColor, pixel fillColor)
{
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE, &c);
	if(c.red== oldColor.red && c.green== oldColor.green && c.blue==       
               oldColor.blue)
	{
		glColor3ub(fillColor.red, fillColor.green, fillColor.blue);
		glBegin(GL_POINTS);
  		      glVertex2i(x, y);
		glEnd();
		glFlush();
		flood_fill(x+1,y, oldColor, fillColor);
		flood_fill(x-1,y, oldColor, fillColor);
		flood_fill(x,y+1, oldColor, fillColor);
		flood_fill(x,y-1, oldColor, fillColor);		
	}
}

void BresenhamLine(int x1,int y1,int x2,int y2){
	int dy=abs(y2-y1),dx=abs(x2-x1);
	int p,flag=0;
	if(dy>dx){
		flag=1;
		dy=dx+dy;
		dx=dy-dx;
		dy=(dy-dx);
		y1=x1+y1;
		x1=y1-x1;
		y1=(y1-x1);
		y2=x2+y2;
		x2=y2-x2;
		y2=(y2-x2);
	}
	int x=x1,y=y1;
	p=2*dy-dx;
	int inx,iny;
	if(x2>=x1)
		inx=1;
	else
		inx=-1;
	if(y2>=y1)
		iny=1;
	else
		iny=-1;					
	glBegin(GL_POINTS);
	while(x!=x2 || y!=y2){
		if(p<=0){
			p=p+2*dy;
			x=x+inx;	
		}else{
			p=p+2*(dy-dx);
			y=y+iny;
			x=x+inx;
				
		}
		glVertex2d((flag==0)?x:y,(flag==0)?y:x);
	}
	glEnd();	
	glFlush();

}

void render()
{
	r = 1.0;
	g=b=0.0;
	glColor3f(r,g,b);	//Color to use for for drawing objects - (R,G,B) values
	BresenhamLine(50,50,450,50);
	BresenhamLine(50,150,450,150);
	BresenhamLine(50,250,450,250);
	BresenhamLine(50,350,450,350);
	BresenhamLine(50,450,450,450);
	BresenhamLine(50,50,50,450);
	BresenhamLine(150,50,150,450);
	BresenhamLine(250,50,250,450);
	BresenhamLine(350,50,350,450);
	BresenhamLine(450,50,450,450);
	
	flood_fill(51,51);
	
}


int main(int argc, char **argv)
{glutInit(&argc,argv); // Initialise GLUT library 

  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   	// Set the initial display mode
  	Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to d
  	glutInitWindowSize(500,500);
  	
  	glutInitWindowPosition(250,250); // Set the initial window position
  	
  	glutCreateWindow("Assignment 4"); // Create window with title Assignment4
	Init();


	glutDisplayFunc(render);
	glutMainLoop();
}
