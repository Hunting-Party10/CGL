#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

GLsizei winHeight=500,winWidth=500;
int c = 0;
GLfloat red=1.0,green=0.0,blue=0.0;

struct scrPt{
	GLint x,y;
};
scrPt polypts[10];

void drawLine(int x1,int y1,int x2,int y2)//Draws Lines between 2 points
{
	float dx=x2-x1;
	float dy=y2-y1;
	float steps;
	if(abs(dx)>abs(dy))
		steps=abs(dx);
	else
		steps=abs(dy);
	float xinc=dx/steps;
	float yinc=dy/steps;
	float x=x1;
	float y=y1;
	glBegin(GL_POINTS);
			glVertex2f(abs(x1), abs(y1));
		glEnd();
	int i;
	for(i=0;i<steps;i++)
	{
		x=x+xinc;
		y=y+yinc;
		glBegin(GL_POINTS);
			glVertex2f(abs(x), abs(y));
		glEnd();
		glFlush();
	}
		
}

void Init()
{
  	/* Set clear color to white */
  	glClearColor(1.0,1.0,1.0,1.0);
  	glMatrixMode(GL_PROJECTION);
  	gluOrtho2D(0,500,0,500);
	glClear(GL_COLOR_BUFFER_BIT);
}

void displayFunc(){
  	glColor3f(red,green,blue);	//Color to use for for drawing objects - (R,G,B) values
  	glPointSize(2.0);
}

void plotpoint(GLint x, GLint y){
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void mousePoint(GLint button, GLint action, GLint xMouse, GLint yMouse){
	if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		plotpoint(xMouse,500-yMouse);
		polypts[c].x = xMouse;
		polypts[c].y = 500-yMouse;
		c++;
	}
	glFlush();
}

void ColorSelect(GLint ch)
{
	int i;
	switch(ch){
		case 1:
			red=1.0;green=0,blue=0;
			break;
		case 2:
			red=0;green=0,blue=1.0;
			break;
		case 3:
			if(c <= 1)
				break;
				for(i = 0; i<c-1;i++)
				{	
					scrPt p1 = polypts[i];
					scrPt p2 = polypts[i+1];
					drawLine(p1.x,p1.y,p2.x,p2.y);	
				}
				drawLine(polypts[0].x,polypts[0].y,polypts[c-1].x,polypts[c-1].y);
				c = 0;
				break;			
		case 4:
			glClear(GL_COLOR_BUFFER_BIT);
			break;
		default:
			red=1.0;green=0,blue=0;
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
  
  	glutInit(&argc,argv); // Initialise GLUT library 

  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   	// Set the initial display mode
  	
  	glutInitWindowSize(500,500);
  	
  	glutInitWindowPosition(100,100); // Set the initial window position and size
  	
  	glutCreateWindow("Assignment 3"); // Create window with title DDA_Line
  	
  	Init(); // Initialize drawing colors

  	glutDisplayFunc(displayFunc);  	// Call the displaying function
	glutMouseFunc(mousePoint);
  	
  	
  	glutCreateMenu(ColorSelect);
  		glutAddMenuEntry("Red",1);
  		glutAddMenuEntry("Blue",2);
  		glutAddMenuEntry("Draw Polygon",3);
  		glutAddMenuEntry("Clear Screen",4);
  	glutAttachMenu(GLUT_RIGHT_BUTTON);
  	
  	glutMainLoop();// Keep displaying until the program is closed
	return 0;
}
